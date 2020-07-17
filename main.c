#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "totp.h"

int main()
{
    char sec[] = "helloworld"; 
    unsigned long time = 1594108878000;

    printf("sec: %s\n", sec);

    int token;
    genTotp(sec, time, TIME_STEP, DIGITS, &token);
    printf("token: %d\n", token);
    return 0;
}
