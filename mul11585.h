// multiplication in GF(2**115 - 85)
// PK - 2019/12

#ifndef __MUL11585_H
#define __MUL11585_H
#include "hashtable.c"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include <time.h>
#include <stdlib.h>
#include <math.h>

typedef union
{
    unsigned __int128 s;
    uint64_t t[2];
} num128;

static const num128 mod  = {.t = {18446744073709551531ULL, 2251799813685247ULL}};
static const num128 m115 = {.t = {18446744073709551615ULL, 2251799813685247ULL}};

static const int k = 32;
//Store all ej values
unsigned __int128 ej[32];
//Store the preconputation of the g^ej values
num128 gExponentEJ[32];

// inputs must be reduced, actually with some margin (about 6 bits)
num128 mul11585(num128 a, num128 b)
{
    num128 a0 = {.t = {0,0}};
    num128 a1 = {.t = {0,0}};
    num128 b0 = {.t = {0,0}};
    num128 b1 = {.t = {0,0}};

    unsigned __int128 a1b1, a0b1, a1b0, a0b0;

    num128 mid;
    num128 mid_q = {.t = {0,0}};
    num128 mid_r = {.t = {0,0}};

    num128 res;
 
    a0.t[0] = a.t[0];
    a1.t[0] = a.t[1];

    b0.t[0] = b.t[0]; 
    b1.t[0] = b.t[1];

    a1b1 = a1.s * b1.s * 696320;
    a0b1 = a0.s * b1.s;
    a1b0 = a1.s * b0.s;
    a0b0 = a0.s * b0.s;

    a0b0 = ((a0b0 >> 115) * 85) + (a0b0 & m115.s);
    mid.s = a0b1 + a1b0;

    mid_q.t[0] = mid.t[1];
    mid_q.s   *= 696320;

    mid_r.t[1] = mid.t[0];
    mid_r.s    = ((mid_r.s >> 115) * 85) + (mid_r.s & m115.s);

    res.s = a1b1 + a0b0 + mid_q.s + mid_r.s;
    res.s = (res.s >> 115) * 85 + (res.s & m115.s);

    res.s = res.s > mod.s ? res.s - mod.s : res.s;
    return res;
}

void print_num128(num128 a)
{
    printf("%llX%016llX\n", a.t[1], a.t[0]);
}

num128 gexp(unsigned __int128 x) {
    // g value 4398046511104   
    num128 g = {.t =  {4398046511104ULL, 0ULL}} ;
    num128 res = {.t =  {1, 0}};
    while(x){
        if(x&1) {
            res = mul11585(res, g);
        } 
        x>>=1;
        g = mul11585(g,g);
    }
    return res;
}

/*int distinguishablePoint(unsigned __int128 s) {
    //We perform s modulo 2^26 to know if it's a distinguishable value or not 
    if(s %  modulo == 0){
        return 1;
    } else {
        return 0;
    }
}*/

void genEJ(){
    //Function to generate all ej values
    for(int i=0;i<32;i++) {
        ej[i] = (unsigned __int128)pow(2,i+4);
    }
}

void initGexponentEJ(){
    //Since we have 32 value for ej we can already compute g^ej.
    for(int i = 0; i < 32; i++){
        gExponentEJ[i] = gexp(ej[i]);
    }
}

num128 dlog64(num128 target){
    uint32_t maskForModulo = (1<<26) - 1;
    uint32_t maskForEj = (1<<5) - 1;
    //Mask for distinguishable value
    unsigned __int128 maskPower26 = (unsigned __int128)pow(2,26);
    //x for the tame Kangaroo
    num128 tame = gexp(pow(2,63));
    unsigned __int128 tameExponent = pow(2,63);
    //y for the wild Kangaroo
    num128 wild = target;
    unsigned __int128 wildExponent = 0;
    int index = 0;
    unsigned __int128 trapExponent = 0;
    num128 result = {.t = {0,0}};
    //int counter = 0;
    while(1){
        //For the tame kangaroo
        index = (tame.s & maskForEj);
        tame = mul11585(tame, gExponentEJ[index]);
        tameExponent += ej[index];
        if((tame.s & maskForModulo) == 0){
            printf("Distinguishable element for tame ");
            print_num128(tame);
            //counter++;
            if(searchTameKangarooTable(tame.s, &trapExponent)){
                if(trapExponent > tameExponent) {
                    result.s = trapExponent - tameExponent;
                } else {
                    result.s = tameExponent - trapExponent;
                }
                break;
            } else {
                //Put a trap for the wild kangaroo
                insertWildKangarooTable(tame.s, tameExponent);
            }
        }

        //For the wild kangaroo
        index = (wild.s & maskForEj);
        wild = mul11585(wild,gExponentEJ[index]);
        wildExponent += ej[index];
        if((wild.s & maskForModulo) == 0){
            printf("Distinguishable element for wild ");
            print_num128(wild);
            //counter++;
            if(searchWildKangarooTable(wild.s, &trapExponent)){
                if(trapExponent > wildExponent) {
                    result.s = trapExponent - wildExponent;
                } else {
                    result.s = wildExponent - trapExponent;
                }
                break;
            } else {
                //Put a trap for the wild kangaroo
                insertTameKangarooTable(wild.s, wildExponent);
            }
        }
    }
    
    freeWildKangarooTable();
    freeTameKangarooTable();
    return result;
}

#endif // __MUL11585_H
