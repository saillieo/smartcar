#include "exti.h"

#define TRIG_PORT 		GPIOB
#define ECHO_PORT 		GPIOB
#define TRIG_PIN 		GPIO_Pin_0
#define ECHO_PIN       	GPIO_Pin_1

int count;
float UltrasonicWave_Distance;

/* Ultrasonic calculation for distance
*/
void EXTI1_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line1) != RESET)
	{
		TIM_SetCounter(TIM1,0);
		TIM_Cmd(TIM1,ENABLE);
		
		while(GPIO_ReadInputDataBit(ECHO_PORT,ECHO_PIN));
		
		TIM_Cmd(TIM1, DISABLE);
		UltrasonicWave_Distance=TIM_GetCounter(TIM1)*340/200.0;	//every count 0.1ms, measure in cm
		
//		printf("distance:%f cm\r\n",UltrasonicWave_Distance);	//for test only
		
		EXTI_ClearITPendingBit(EXTI_Line1); 
	}
}
