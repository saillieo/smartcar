#include "stm32f10x.h"
#include "delay.h"
#include "pwm.h"
#include "motor.h"
#include "encoder.h"
#include "sys.h"
#include "usart.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "timer.h"
#include "ultrasonic.h"

int PWM_MAX=7200,PWM_MIN=-7200;
int MOTO1,MOTO2;					//motor loading parameters

u16 per=7199,psc=0;
int Encoder_Left, Encoder_Right;	//encoder data (speed)
float Pitch,Roll,Yaw;
short aacx,aacy,aacz;	//accerlation raw data
short gyrox,gyroy,gyroz;//gyro raw data


//short temp;				//temperature



/***********test parameters***********/
int ccr3=6000,ccr4=4000;
//u16 t, len;
u16 times=0;
u8 t=0;
u8 test1,test2;
/***********test parameters***********/

int main(void)
{
	SystemInit();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		//set NVIC group
	
	PWM_Init_TIM2(per,psc);
	Motor_Init();
//	delay_init();								//no need to initialize delay when not use systick for delay purpose
	Encoder_TIM3_Init();
	Encoder_TIM4_Init();

//	Timer1_Init(5000,7199);						//for calculation of ultrasonic waive time
//	Ultrasonic_Init();
	
	uart1_init(115200);							//usart1 is only used for testing reason.
	
	MPU_Init();	
	while(mpu_dmp_init())
	{
		printf("MPU DMP Init Error\r\n");delay_ms(200);
	}
	printf("MPU ready\r\n");
	
	SysTick_Init();								//set systick interruption period to 10ms
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;		//enable systick function

	while(1)
	{
//		printf("Pitch:%f,Roll:%f,Yaw:%f \r\n",Pitch, Roll, Yaw);
//		printf("Moto1:%d,Moto2:%d \r\n",MOTO1,MOTO2);
		delay_ms(100);
	}
/************Ultrosonic Test***************/
//	while(1)
//	{
//		Ultrasonic_Start();
//		delay_ms(1000);
//		

//	}
/************Ultrasonic Test end***********/	
	
	
	
/***********PWM test  ***********/	
//	PWM_Change_Test(ccr3,ccr4);
/***********PWM test end***********/
	
/************MPU6050 test***********/
//	while(mpu_dmp_init())
//	{
//		printf("MPU DMP Init Error");delay_ms(200);
//	}
//	printf("MPU6050 OK\r\n");
//	
//	while(1)
//	{
//		if(mpu_dmp_get_data(&pitch,&roll,&yaw)==0)
//		{
//			temp=MPU_Get_Temperature();//get temperature data
//			MPU_Get_Accelerometer(&aacx,&aacy,&aacz);	//accerlerater raw data
//			MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);	//gyro raw data
//			
//			if(t%100==0)
//			{
//				printf("temperature: %d, pitch: %f, roll: %f, yaw: %f.\r\n",temp/100, pitch*10, roll*10, yaw*10);
//				t=0;
//			}
//		}
//		t++;
/****************MPU6050 test end*****************************/
		
/*************** Encoder test******************************
		times++;
		if(times%400==0)
		{
			printf("TIM3 Count:%d, TIM4 Count:%d\r\n",Read_Speed(3),Read_Speed(4));
			times=0;
		}
		delay_ms(50);
****************Encoder test end**************************/
		
/**************** USART1 test***********************
		if(USART_RX_STA&0x8000)
		{
			len=USART_RX_STA&0x3f;
			printf("\r\nyour messages are:\r\n\r\n");
			for(t=0;t<len;t++)
			{
				USART_SendData(USART1,USART_RX_BUF[t]);
				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);	//wait for byte send end
			}
			printf("\r\n\r\n");
			USART_RX_STA=0;
		}else
		{
			times++;
			if(times%5000==0)
			{
				printf("\r\n testing\r\n");
				printf("sail\r\n\r\n");
			}
			if(times%200==0) printf("please input data\n");
			delay_ms(10);
		}
	}
***************USART1 test end **********************/

}
