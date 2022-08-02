#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

unsigned __int128 tab[32];

double rand_gen(){
    double rndDouble = (double)rand() / RAND_MAX;
    printf("rndDouble = %f\n",rndDouble);
    return rndDouble;
}

double normalRandom() {
   // return a normally distributed random value
   double v1=rand_gen();
   double v2=rand_gen();
   return cos(2*3.14*v2)*sqrt(-2.*log(v1));
}

int main(){
    printf("Test random generator\n");

    srand(time(NULL));
    double sigma = pow(2,30);
    double Mi = pow(2,31);
    double moye = 0;
    for(int i=0;i<32;i++) {
        double x = normalRandom()*sigma+Mi;
        tab[i] = (unsigned __int128)x;
        printf("x = %f\n",round(x));
        printf("x = %f\n",(x));
        printf("x = %llx\n",tab[i]);
        moye += x;
    }
    printf("Mo = %f\n",moye/32);
    printf("Mi = %f\n",Mi);
    return 0;
}