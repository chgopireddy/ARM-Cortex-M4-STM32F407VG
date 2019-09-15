#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
int main(void)
{
	 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	   GPIO_InitTypeDef g;
	   g.GPIO_Pin=GPIO_Pin_12;
	   g.GPIO_Mode= GPIO_Mode_OUT;
	   g.GPIO_Speed=GPIO_Speed_25MHz;
	   g.GPIO_OType= GPIO_OType_PP;
	   g.GPIO_PuPd=GPIO_PuPd_UP ;

	GPIO_Init(GPIOD, &g);
    while(1)
    {
 	GPIO_SetBits(GPIOD,GPIO_Pin_12);
    }
}
