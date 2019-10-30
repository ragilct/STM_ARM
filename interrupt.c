#include "stm32l1xx.h"
#include "stm32l1xx_gpio.h"
#include "stm32l1xx_exti.h"
#include "stm32l1xx_rcc.h"
#include "stm32l1xx_syscfg.h"
#include "misc.h"


void EXTI0_IRQHandler()
{
if(EXTI_GetFlagStatus(EXTI_Line0)!=RESET)
{
EXTI_ClearFlag(EXTI_Line0);
GPIO_ToggleBits(GPIOB, GPIO_Pin_6);
}
}

int main()
{
	//int i;
GPIO_InitTypeDef gpioa,gpiob;
EXTI_InitTypeDef ext1;
NVIC_InitTypeDef ext_config;
	
RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE); //function to enable GPIO clocks
RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE); //function to enable GPIO clocks
RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE); //function to enable External interrupt clocks
	
GPIO_StructInit(&gpioa);	
gpiob.GPIO_Mode = GPIO_Mode_OUT;
gpiob.GPIO_Pin = GPIO_Pin_6;
	
GPIO_Init(GPIOB,&gpiob);
	
gpioa.GPIO_Pin = GPIO_Pin_0;
gpioa.GPIO_Mode = GPIO_Mode_IN;
gpioa.GPIO_PuPd = GPIO_PuPd_NOPULL;
GPIO_Init(GPIOA,&gpioa);
	
EXTI_GenerateSWInterrupt(EXTI_Line0);
	
SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA,EXTI_PinSource0);	
	
ext1.EXTI_Line = EXTI_Line0;
ext1.EXTI_Mode = EXTI_Mode_Interrupt;
ext1.EXTI_Trigger = EXTI_Trigger_Falling;
ext1.EXTI_LineCmd = ENABLE;
EXTI_Init(&ext1);

ext_config.NVIC_IRQChannel = EXTI0_IRQn;
ext_config.NVIC_IRQChannelPreemptionPriority = 0;
ext_config.NVIC_IRQChannelSubPriority = 0;
ext_config.NVIC_IRQChannelCmd = ENABLE;
NVIC_Init(&ext_config);
EXTI->IMR |=0X00000001; 
while(1);
}
