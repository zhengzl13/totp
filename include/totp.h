#ifndef TOTP_H_
#define TOTP_H_

#define TIME_STEP 300
#define DIGITS 6

/**
 * sec: secret key
 * time: linux timestamp // 1594883057362
 * timeStep: 300 default
**/
void genTotp(char sec[], unsigned long time, unsigned long timeStep, unsigned short dig, int *token);

#endif
