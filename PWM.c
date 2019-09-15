#include"stm32f4xx.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"

void TIM_init()
{

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

	 TIM_TimeBaseInitTypeDef a;

	 a.TIM_Prescaler=0;
	 a.TIM_Period=10000;
	 a.TIM_ClockDivision=TIM_CKD_DIV1;
	 a.TIM_CounterMode= TIM_CounterMode_Up;
	 a.TIM_RepetitionCounter=0;
	 TIM_OC1PreloadConfig(TIM4,TIM_OCPreload_Enable);
	 TIM_TimeBaseInit(TIM4,&a);


}
//function to intialize the PWM TIM4 on channel 1(TIM4_CH1)
void PWM_init()
{
	// page 529 register description
	 TIM_OCInitTypeDef p;
	 p.TIM_OCMode=TIM_OCMode_PWM2 ;//from tim.h file
	 p.TIM_OutputState=TIM_OutputState_Enable ;//from tim.h file
	 p.TIM_OCPolarity=TIM_OCPolarity_Low ;
	 p.TIM_Pulse=0;
	 TIM_OC1Init(TIM4,&p);
	 TIM_CCxCmd(TIM4,TIM_Channel_1,TIM_CCx_Enable);
}
int main(void)
{

		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
		   GPIO_InitTypeDef g;
	g.GPIO_Pin=GPIO_Pin_12;
	g.GPIO_Mode= GPIO_Mode_AF;
	g.GPIO_Speed=GPIO_Speed_100MHz;
	g.GPIO_OType= GPIO_OType_PP;
	g.GPIO_PuPd=GPIO_PuPd_NOPULL ;
	GPIO_Init(GPIOD,&g);
	TIM_init();
	PWM_init();
int x=0,i=0;
TIM_Cmd(TIM4,ENABLE);
	while(1)
	{
		for(i=0;i<10000;i++){
		    	TIM_SetCompare1(TIM4,i);
		    	while(x<100000)x++;
		    	}
		    	x=0;
		    	for(i=10000;i>0;i--){
		    	TIM_SetCompare1(TIM4,i);
		    	while(x<100000)x++;
		    	}
	}
}
