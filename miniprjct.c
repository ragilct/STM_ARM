#include "stm32l1xx.h"
#include "stm32l1xx_rcc.h"
#include "stm32l1xx_gpio.h"
#include "stm32l1xx_tim.h"
#include "stm32l1xx_usart.h"
#include "misc.h"
 char a=20;
 char package[7]={0x02,0x06,0x90,0x00,0x00,0x00,0x03};
 char ther[7];
 int i=0,j=0;
 
 static void usartInterrupt_Config()
{
NVIC_InitTypeDef usartintr;
usartintr.NVIC_IRQChannel = USART3_IRQn;
usartintr.NVIC_IRQChannelPreemptionPriority = 0;
usartintr.NVIC_IRQChannelSubPriority = 0;
usartintr.NVIC_IRQChannelCmd = ENABLE;
NVIC_Init(&usartintr);
}

 static void Interrupt_Config()
{
NVIC_InitTypeDef NVIC_Str;
NVIC_Str.NVIC_IRQChannel = TIM2_IRQn;
NVIC_Str.NVIC_IRQChannelPreemptionPriority = 1;
NVIC_Str.NVIC_IRQChannelSubPriority = 1;
NVIC_Str.NVIC_IRQChannelCmd = ENABLE;
NVIC_Init(&NVIC_Str);
}

static void Timer2_Config()
{
TIM_TimeBaseInitTypeDef TIM2_init; 	// declaring timer structure
RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //function to enable timer clock
TIM_DeInit(TIM2); 		//initializing timer3 to default values
TIM2_init.TIM_Period =0x9C3F;		//ARR VALUE of the structure
TIM2_init.TIM_Prescaler = 0X0031;		//prescale value 49 of the structure
TIM2_init.TIM_CounterMode = TIM_CounterMode_Up;		// structure mode to up counter
TIM_TimeBaseInit(TIM2,&TIM2_init); 		// confiduring timer3 with structure
TIM_Cmd(TIM2,ENABLE); 		// Enabling timer3 CR1 bit0
TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
}

 
 void USART_Config()
 {
	 GPIO_InitTypeDef port;
USART_InitTypeDef usart3;
/* USART IOs configuration ***********************************/
/* Enable GPIOC clock */
RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
/* Connect PC10 to USART3_Tx */
GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_USART3);
/* Connect PC11 to USART3_Rx*/
GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_USART3);
/* Configure USART3_Tx and USART3_Rx as alternate function */
port.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
port.GPIO_Mode = GPIO_Mode_AF;
port.GPIO_Speed = GPIO_Speed_2MHz;
port.GPIO_OType = GPIO_OType_PP;
port.GPIO_PuPd = GPIO_PuPd_UP;
GPIO_Init(GPIOC, &port);
/* USART configuration ***************************************/

/* Enable USART3 clock */
RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
usart3.USART_BaudRate = 9600;

usart3.USART_WordLength = USART_WordLength_8b;
usart3.USART_StopBits = USART_StopBits_1;
usart3.USART_Parity = USART_Parity_No;
usart3.USART_HardwareFlowControl =USART_HardwareFlowControl_None;
usart3.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

USART_Init(USART3, &usart3);
/* Enable USART3 */
USART_Cmd(USART3, ENABLE);
USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);
 }
 
 static void LED_Config()
 {
 GPIO_InitTypeDef blink;
RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
blink.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7;
	blink.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_Init(GPIOB,&blink);
 }
 
 //Interrupt Routine
void TIM2_IRQHandler(void)
{
if(TIM_GetITStatus(TIM2, TIM_FLAG_Update) != RESET)
{

	GPIO_ToggleBits(GPIOB,GPIO_Pin_6);
	a++;
	if(a>100)
	{
	a=20;
	}
	package[5]=a;
	
TIM_ClearITPendingBit(TIM2,TIM_FLAG_Update);
	
}
	
for(i=0;i<7;i++)
	{
	USART_SendData(USART3,(char) package[i]);
	 while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==RESET);
	}
 }

 void USART3_IRQHandler(void)
{
if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
{
	
	//GPIO_ToggleBits(GPIOB,GPIO_Pin_7);	
ther[j] = USART_ReceiveData(USART3);
	//USART_SendData(USART3,ther);
   j++;
	if(j>6)
		j=0;
}
 }
 int main()
 {

LED_Config();
USART_Config();
Timer2_Config();
Interrupt_Config();
usartInterrupt_Config();

while (1)
{
	if(package[5]>ther[5]){
		GPIO_SetBits(GPIOB,GPIO_Pin_7);
}
			else{
		GPIO_ResetBits(GPIOB,GPIO_Pin_7);
	
			}
}
}

 
