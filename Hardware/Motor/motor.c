#include "motor.h"

//motor initialize
void Motor_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); 
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;		//initialize GPIO PB12, PB13, PB14, PB15
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct); 
	
	
	
}


//limit PWM function
void Limit(int *motoA, int *motoB)
{
	if (*motoA>PWM_MAX) *motoA=PWM_MAX;
	if (*motoA<PWM_MIN) *motoA=PWM_MIN;
	
	if (*motoB>PWM_MAX) *motoB=PWM_MAX;
	if (*motoB<PWM_MIN) *motoB=PWM_MIN;
}

//absorlute number
int Num_abs(int p)
{
	int q;
	q=p>0?p:(-p);
	return q;
}

//load PID result
//inlet parameter: PWM value after PID calculation
void Load(int moto1, int moto2)
{
	//check if clockwise or unclockwise
	if (moto1>0) Ain1=1, Ain2=0;
	else Ain1=0, Ain2=1;
	//set PWM
	TIM_SetCompare3(TIM2,Num_abs(moto1));
	
	if (moto2>0) Bin1=1, Bin2=0;
	else Bin1=0, Bin2=1;
	TIM_SetCompare4(TIM2,Num_abs(moto2));
}
