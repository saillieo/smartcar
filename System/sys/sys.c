#include "sys.h"

//////////////////////////////////////////////////////////////////////////////////	 

void WFI_SET(void)
{
	__ASM volatile("wfi");		  
}
//�ر������ж�
void INTX_DISABLE(void)
{		  
	__ASM volatile("cpsid i");
}
//���������ж�
void INTX_ENABLE(void)
{
	__ASM volatile("cpsie i");		  
}
//����ջ����ַ
//addr:ջ����ַ
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
