#include "mul11585.h"
#include "time.h"
int main() {
    printf("\nJust for me\n");
    srand(time(0));
    gexp(64);
    printf("Setup the distinguisher elements\n");
    genEJ();
    initGexponentEJ();
    printf("Start the attack \n");
    //Attack with kangaroo
    //num128 h = 0x71AC72AF7B138B6263BF2908A7B09; is equal to the following
    num128 h = {.t =  {13125244077011008265ULL, 1999767558664504ULL}} ;
    printf("With the number : ");   
    print_num128(h);
    printf("\n");
    num128 toFind = gexp(pow(2,34));
    printf("With the number : ");   
    print_num128(toFind);
    printf("\n");
    clock_t t;
    t = clock();
    num128 result = dlog64(toFind);
    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
  
    printf("fun() took %f seconds to execute \n", time_taken);
    print_num128(result);
    return 0;
}   