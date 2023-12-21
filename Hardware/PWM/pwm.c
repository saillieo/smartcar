#include "pwm.h"

void PWM_Init_TIM2(u16 per, u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_OCInitTypeDef TIM_OCInitStruct;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); 
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;		//initialize GPIO PA2, PA3
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct); 
	
	
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;	//initialize timer2
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period=per;
	TIM_TimeBaseInitStruct.TIM_Prescaler=psc;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
	
	TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM1;			//initialize compare output
	TIM_OCInitStruct.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_Pulse=0;
	TIM_OC3Init(TIM2, &TIM_OCInitStruct);
	TIM_OC4Init(TIM2, &TIM_OCInitStruct);
	
	TIM_CtrlPWMOutputs(TIM2,ENABLE);

	TIM_OC3PreloadConfig(TIM2,TIM_OCPreload_Enable);						//enable oc3 preload
	TIM_OC4PreloadConfig(TIM2,TIM_OCPreload_Enable);						//enable oc4 preload
	TIM_ARRPreloadConfig(TIM2,ENABLE);										//enable TIM2 arr preload

	TIM_Cmd(TIM2,ENABLE);
}



//test function
void PWM_Change_Test(int ccr3,int ccr4)
{
	TIM_SetCompare3(TIM2,ccr3);
	TIM_SetCompare4(TIM2,ccr4);
}
