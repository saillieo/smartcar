#ifndef _PWM_H
#define _PWM_H

#include "sys.h"

void PWM_Init_TIM2(u16 per, u16 psc);
void PWM_Change_Test(int ccr3,int ccr4);

#endif
