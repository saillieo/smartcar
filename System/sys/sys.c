#include "sys.h"

//////////////////////////////////////////////////////////////////////////////////	 

void WFI_SET(void)
{
	__ASM volatile("wfi");		  
}
//关闭所有中断
void INTX_DISABLE(void)
{		  
	__ASM volatile("cpsid i");
}
//开启所有中断
void INTX_ENABLE(void)
{
	__ASM volatile("cpsie i");		  
}
//设置栈顶地址
//addr:栈顶地址
__asm void MSR_MSP(u32 addr) 
{
    MSR MSP, r0 			//set Main Stack value
    BX r14
}

//system tick initialization
void SysTick_Init(void)
{
	if(SysTick_Config(SystemCoreClock/100))		//10ms
	{
		/*capture error*/
		while(1);
	}
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//disable systick first, enable it in main() function. 
}
