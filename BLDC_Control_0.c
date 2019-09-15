#include "misc.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_syscfg.h"
void Configure_PINS(void) {
	    GPIO_InitTypeDef H1,H2,H3,G;
	    EXTI_InitTypeDef E1,E2,E3;
	    NVIC_InitTypeDef N1,N2,N3;

	    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	    H1.GPIO_Mode = GPIO_Mode_IN;
	    H1.GPIO_OType = GPIO_OType_PP;
	    H1.GPIO_Pin = GPIO_Pin_0;
	    H1.GPIO_PuPd = GPIO_PuPd_UP;
	    H1.GPIO_Speed = GPIO_Speed_100MHz;
	    GPIO_Init(GPIOA, & H1);

	    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);

	    E1.EXTI_Line = EXTI_Line0;
	    E1.EXTI_LineCmd = ENABLE;
	    E1.EXTI_Mode = EXTI_Mode_Interrupt;
	    E1.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	    EXTI_Init(&E1);

	    N1.NVIC_IRQChannel = EXTI0_IRQn;
	    N1.NVIC_IRQChannelPreemptionPriority = 0x00;
	    N1.NVIC_IRQChannelSubPriority = 0x00;
	    N1.NVIC_IRQChannelCmd = ENABLE;
	    NVIC_Init(&N1);

	    H2.GPIO_Mode = GPIO_Mode_IN;
	   	    H2.GPIO_OType = GPIO_OType_PP;
	   	    H2.GPIO_Pin = GPIO_Pin_1;
	   	    H2.GPIO_PuPd = GPIO_PuPd_UP;
	   	    H2.GPIO_Speed = GPIO_Speed_100MHz;
	   	    GPIO_Init(GPIOA, &H2);

	   	    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource1);

	   	    E2.EXTI_Line = EXTI_Line1;
	   	    E2.EXTI_LineCmd = ENABLE;
	   	    E2.EXTI_Mode = EXTI_Mode_Interrupt;
	   	    E2.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	   	    EXTI_Init(&E2);

	   	    N2.NVIC_IRQChannel = EXTI1_IRQn;
	   	    N2.NVIC_IRQChannelPreemptionPriority = 0x00;
	   	    N2.NVIC_IRQChannelSubPriority = 0x00;
	   	    N2.NVIC_IRQChannelCmd = ENABLE;
	   	    NVIC_Init(&N2);

	   	 H3.GPIO_Mode = GPIO_Mode_IN;
	   		    H3.GPIO_OType = GPIO_OType_PP;
	   		    H3.GPIO_Pin = GPIO_Pin_2;
	   		    H3.GPIO_PuPd = GPIO_PuPd_UP;
	   		    H3.GPIO_Speed = GPIO_Speed_100MHz;
	   		    GPIO_Init(GPIOA, &H3);

	   		    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource2);

	   		    E3.EXTI_Line = EXTI_Line2;
	   		    E3.EXTI_LineCmd = ENABLE;
	   		    E3.EXTI_Mode = EXTI_Mode_Interrupt;
	   		    E3.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	   		    EXTI_Init(&E3);

	   		    N3.NVIC_IRQChannel = EXTI2_IRQn;
	   		    N3.NVIC_IRQChannelPreemptionPriority = 0x00;
	   		    N3.NVIC_IRQChannelSubPriority = 0x00;
	   		    N3.NVIC_IRQChannelCmd = ENABLE;
	   		    NVIC_Init(&N3);

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

    G.GPIO_Mode = GPIO_Mode_OUT;
    G.GPIO_OType = GPIO_OType_PP;
    G.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
    G.GPIO_PuPd = GPIO_PuPd_UP;
    G.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOB, &G);
}
void EXTI0_IRQHandler(void) {
	Configure_PINS();

    if (EXTI_GetITStatus(EXTI_Line0) != RESET) {

    	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0))
    	{
    		GPIO_SetBits(GPIOB,GPIO_Pin_0|GPIO_Pin_5);
    		GPIO_ResetBits(GPIOB, GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4);
    	}
    	else
    	{
    		GPIO_SetBits(GPIOB,GPIO_Pin_4|GPIO_Pin_1);
    		GPIO_ResetBits(GPIOB,GPIO_Pin_0|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_5);

    	}
        EXTI_ClearITPendingBit(EXTI_Line0);
    }
}
void EXTI1_IRQHandler(void) {
	Configure_PINS();

    if (EXTI_GetITStatus(EXTI_Line1) != RESET) {

    	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1))
    	{
    		GPIO_SetBits(GPIOB,GPIO_Pin_4|GPIO_Pin_3);
    		GPIO_ResetBits(GPIOB,GPIO_Pin_0|GPIO_Pin_2|GPIO_Pin_5|GPIO_Pin_1);
    	}
    	else
    	{
    		GPIO_SetBits(GPIOB,GPIO_Pin_2|GPIO_Pin_5);
    		GPIO_ResetBits(GPIOB,GPIO_Pin_1|GPIO_Pin_0|GPIO_Pin_3|GPIO_Pin_4);

    	}
        EXTI_ClearITPendingBit(EXTI_Line1);
    }
}
void EXTI2_IRQHandler(void) {
	Configure_PINS();

    if (EXTI_GetITStatus(EXTI_Line2) != RESET) {

    	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2))
    	{
    		GPIO_SetBits(GPIOB,GPIO_Pin_1|GPIO_Pin_2);
    		GPIO_ResetBits(GPIOB,GPIO_Pin_0|GPIO_Pin_3|GPIO_Pin_5|GPIO_Pin_4);
    	}
    	else
    	{
    		GPIO_SetBits(GPIOB,GPIO_Pin_0|GPIO_Pin_3);
    		GPIO_ResetBits(GPIOB,GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_4|GPIO_Pin_5);
    	}
        EXTI_ClearITPendingBit(EXTI_Line2);
    }
}
int main(void)
{
	Configure_PINS();
    while(1)
    {
    	 EXTI0_IRQHandler();
    	 EXTI1_IRQHandler();
    	 EXTI2_IRQHandler();
    }
}
 
