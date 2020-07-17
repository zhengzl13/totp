#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "totp.h"
#include <hmac/hmac.h>

const char *DEFAULT_TIMESTEP = "6";
const int TOTP_STEP = 300;
const int TOTP_RANGE_CURRENT = 0;
const int TOTP_RANGE_PREV = -1;
const int TOTP_RANGE_NEXT = -2;
const int TOTP_RANGE_PREV2 = 1;
const int TOTP_RANGE_NEXT2 = 2;

const int ONLINE_RANGE_OFFSET[3] = { 0, -1, -2 };

const int OFFLINE_RANGE_OFFSET[5] = { 0, -1, -2, 1, 2 };

const int DIGITS_POWER[9] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 10000000};


void genTotp(char sec[], unsigned long time, unsigned long timeStep, unsigned short dig, int *token)
{
    uint32_t endianness;
    uint64_t t; /* number of steps */

    t = time/(timeStep*1000);
    endianness = 0xdeadbeef;
    if ((*(const uint8_t *) & endianness) == 0xef)
    {
        t = ((t & 0x00000000ffffffff) << 32) | ((t & 0xffffffff00000000) >> 32);
        t = ((t & 0x0000ffff0000ffff) << 16) | ((t & 0xffff0000ffff0000) >> 16);
        t = ((t & 0x00ff00ff00ff00ff) << 8) | ((t & 0xff00ff00ff00ff00) >> 8);
    };

    char hash[256] = {0};
    int len = (int)sizeof(hash);

    hmac_sha1(sec, strlen(sec), (const unsigned char *)&t, sizeof(t), hash, &len);

    int offset = hash[len - 1] & 0xf;
    int binary = ((hash[offset] & 0x7f) << 24) 
                | ((hash[offset + 1] & 0xff) << 16) 
                | ((hash[offset + 2] & 0xff) << 8) 
                | (hash[offset + 3] & 0xff);

    *token = binary % DIGITS_POWER[dig];
}