#include "delay.h"
////////////////////////////////////////////////////////////////////////////////// 	 
//如果需要使用OS,则包括下面的头文件即可.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos 使用	  
#endif
//////////////////////////////////////////////////////////////////////////////////	 


//延时nus
//nus为要延时的us数.		    								   
void delay_us(u32 nus)
{		
	u8 j;
	while(nus--) for(j=0;j<10;j++);
}
//延时nms
//注意nms的范围

void delay_ms(u16 nms)
{	 		  	  
	while(nms--) delay_us(1000);
} 









































