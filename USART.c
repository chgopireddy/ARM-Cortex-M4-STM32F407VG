
#include "stm32f4xx.h"
#include "misc.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_conf.h"
#include "stm32f4xx_exti.h"
void GPIOA_Init(void);
void USART1_Init(void);
void led_toggle(void);

int main(void)
{

    GPIOA_Init();

    USART1_Init();

    while(1)
    {

    }
}


void GPIOA_Init(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef g;
    g.GPIO_Pin=GPIO_Pin_8;
   	 g.GPIO_Mode=  GPIO_Mode_OUT ;
   	 g.GPIO_Speed = GPIO_Speed_50MHz;
   	 g.GPIO_PuPd=GPIO_PuPd_UP;
   	 g.GPIO_OType=GPIO_OType_PP;

    GPIO_Init(GPIOA, &g);
    GPIO_SetBits(GPIOA, GPIO_Pin_8);//on led
}
void USART1_Init(void)
{

    USART_InitTypeDef usart1_init_struct;
    /* Bit configuration structure for GPIOA PIN9 and PIN10 */
    GPIO_InitTypeDef gpioa_init_struct;

    /* Enalbe clock for USART1, AFIO and GPIOA */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO_, ENABLE);

    /* GPIOA PIN9 alternative function Tx */
    gpioa_init_struct.GPIO_Pin = GPIO_Pin_9;
    gpioa_init_struct.GPIO_Speed = GPIO_Speed_50MHz;
    gpioa_init_struct.GPIO_Mode = GPIO_Mode_AF;
    gpioa_init_struct.GPIO_PuPd= GPIO_PuPd_UP ;
    gpioa_init_struct.GPIO_OType=GPIO_OType_PP;
    GPIO_Init(GPIOA, &gpioa_init_struct);
    /* GPIOA PIN9 alternative function Rx */
    gpioa_init_struct.GPIO_Pin = GPIO_Pin_10;
    gpioa_init_struct.GPIO_Speed = GPIO_Speed_50MHz;
    gpioa_init_struct.GPIO_Mode = GPIO_Mode_IN;
    gpioa_init_struct.GPIO_PuPd= GPIO_PuPd_UP ;
    gpioa_init_struct.GPIO_OType=GPIO_OType_PP;
    GPIO_Init(GPIOA, &gpioa_init_struct);

    /* Enable USART1 */
    USART_Cmd(USART1, ENABLE);
    /* Baud rate 9600, 8-bit data, One stop bit
     * No parity, Do both Rx and Tx, No HW flow control
     */
    usart1_init_struct.USART_BaudRate = 9600;
    usart1_init_struct.USART_WordLength = USART_WordLength_8b;
    usart1_init_struct.USART_StopBits = USART_StopBits_1;
    usart1_init_struct.USART_Parity = USART_Parity_No ;
    usart1_init_struct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    usart1_init_struct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    /* Configure USART1 */
    USART_Init(USART1, &usart1_init_struct);
    /* Enable RXNE interrupt */
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    /* Enable USART1 global interrupt */
    NVIC_EnableIRQ(USART1_IRQn);
}


void led_toggle(void)
{
    /* Read LED output (GPIOA PIN8) status */
    uint8_t led_bit = GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_8);

    /* If LED output set, clear it */
    if(led_bit == (uint8_t)Bit_SET)
    {
        GPIO_ResetBits(GPIOA, GPIO_Pin_8);
    }
    /* If LED output clear, set it */
    else
    {
        GPIO_SetBits(GPIOA, GPIO_Pin_8);
    }
}

void USART1_IRQHandler(void)
{
    /* RXNE handler */
    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
    {
        /* If received 'g', toggle LED and transmit 'G' */
        if((char)USART_ReceiveData(USART1) == 'g')
        {
            led_toggle();
            USART_SendData(USART1, 'G');
            // Wait until Tx data register is empty
            while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
            {
            }
        }
    }


}
