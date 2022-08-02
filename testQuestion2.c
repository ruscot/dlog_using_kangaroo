#include "mul11585.h"
#include <string.h>
#include <stdio.h>
int main() {
    printf("\nResult for x = 257\n");
    num128 res = gexp(257);
    print_num128(res);

    printf("\n\nResult for x = 112123123412345\n");
    res = gexp(112123123412345);
    print_num128(res);

    printf("\n\nResult for x = 18014398509482143\n");
    res = gexp(18014398509482143);
    print_num128(res);
    printf("\n");
    return 0;
}