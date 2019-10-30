#include "stm32l1xx.h"
#include "stm32l1xx_rcc.h"
#include "stm32l1xx_gpio.h"
#include "stm32l1xx_usart.h"


int main(){
	
char str;
GPIO_InitTypeDef rx,led; // declaring port structure
	
USART_InitTypeDef usart3; //declaring usart structure

RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE); //function to enable GPIO clocks
RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE); //function to enable usart3 clock

	led.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7; //configuring gpio pins to structure
	led.GPIO_Mode=GPIO_Mode_OUT;  //configuring pin modes to structure
	rx.GPIO_Pin=GPIO_Pin_10|GPIO_Pin_11;
	rx.GPIO_Mode=GPIO_Mode_AF;

	GPIO_Init(GPIOB, &rx); 
	GPIO_Init(GPIOB, &led);
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_USART3); // configuring af mode rx
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_USART3); // configuring af mode tx

	
	USART_StructInit(&usart3); // initialing values to structure
	USART_Init(USART3,&usart3);// USART3 initialised with usart3 strucutre
	USART_Cmd(USART3,ENABLE); //Enabling USART3
	GPIO_SetBits(GPIOB,GPIO_Pin_6);
	while(1)
	{
	while(USART_GetFlagStatus(USART3,USART_FLAG_RXNE))
	{
	str=USART_ReceiveData(USART3);
	USART_SendData(USART3,str);
	GPIO_ToggleBits(GPIOB,GPIO_Pin_7);	
	}
	}
}
