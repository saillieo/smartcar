#include "delay.h"
////////////////////////////////////////////////////////////////////////////////// 	 
//�����Ҫʹ��OS,����������ͷ�ļ�����.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos ʹ��	  
#endif
//////////////////////////////////////////////////////////////////////////////////	 


//��ʱnus
//nusΪҪ��ʱ��us��.		    								   
void delay_us(u32 nus)
{		
	u8 j;
	while(nus--) for(j=0;j<10;j++);
}
//��ʱnms
//ע��nms�ķ�Χ

void delay_ms(u16 nms)
{	 		  	  
	while(nms--) delay_us(1000);
} 









































