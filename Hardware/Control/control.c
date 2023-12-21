#include "control.h"


float Med_Angle=-2;		//mechanical angle for car balance
float Target_Speed=0;	//target speed setting

float Vertical_Kp=700,Vertical_Kd=2;
float Velocity_Kp=0.2,Velocity_Ki=0.001;
float Turn_Kp=1;
int Vertical_out,Velocity_out,Turn_out;//for saving the output data


/************
vertical loop (PD): Kp*Ek+Kd*Ek_D
input: expected angle: Med, real angle: Angle, real gyro: gyro_Y
output: vertical loop output: PWM_out
***********/
int Vertical(float Med, float Angle, float gyro_X)
{
	int PWM_out;

	
	PWM_out=Vertical_Kp*(Angle-Med)+Vertical_Kd*(gyro_X-0);
	return PWM_out;
}

/*************
velocity loop (PI): Kp*Ek+Ki*Ek_S
**************/
int Velocity(int Target,int encoder_left, int encoder_right)
{
	static int PWM_out,Encoder_Err,Encoder_S,EnC_Err_Lowout,EnC_Err_Lowout_last=0;
	
	float a=0.7;
	

	//1.calculate velocity error
	Encoder_Err=(encoder_left+encoder_right)-Target;
	//2.low pass filter for velocity error
	EnC_Err_Lowout=(1-a)*Encoder_Err+a*EnC_Err_Lowout_last;
	EnC_Err_Lowout_last=EnC_Err_Lowout;
	//3.integer for velocity error
	Encoder_S+=EnC_Err_Lowout;
	if(Encoder_S>10000) Encoder_S=10000;
	if(Encoder_S<-10000) Encoder_S=-10000;		//limit Encoder_S
	//4.clculate output
	PWM_out=Velocity_Kp*EnC_Err_Lowout+Velocity_Ki*Encoder_S;

	return PWM_out;
}

/************************
turn loop:
************************/
int Turn(int gyro_Z)
{
	int PWM_out;
	
	PWM_out=Turn_Kp*gyro_Z;
	return PWM_out;
}
