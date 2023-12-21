#ifndef _ENCODER_H
#define _ENCODER_H


#include "sys.h"

void Encoder_TIM3_Init(void);
void Encoder_TIM4_Init(void);
int Read_Speed(int TIMx);
void TIM3_IRQHandler(void);
void TIM4_IRQHandler(void);

#endif

