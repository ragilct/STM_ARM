typedef unsigned int uint32_t;
typedef unsigned short uint16_t;

#define RCC_AHBENR (uint32_t*) (0x40023800 + 0x00001C)
//#define RCC_APB2ENR (uint32_t*) (0x40023800 + 0x20)
#define RCC_APB1ENR (uint32_t*) (0x40023800 + 0x24)
#define USART_SR	(uint32_t*)		(0x40004400 + 0x00)
#define USART_DR	(uint32_t*)		(0x40004400 + 0x04)
#define USART_BRR	(uint32_t*)		(0x40004400 + 0x08)
#define USART_CR1	(uint32_t*)		(0x40004400 + 0x0C)
#define USART_CR2	(uint32_t*)		(0x40004400 + 0x10)

/*for configuring alternate functions*/
#define GPIOA_MODER (uint32_t*) (0x40020000 + 0x00)
#define GPIOA_OTYPER (uint32_t*) (0x40020000 + 0x04)
#define GPIOA_OSPEEDR (uint32_t*) (0x40020000 + 0x08)
#define GPIOA_PUPDR (uint32_t*) (0x40020000 + 0x0C)
#define GPIOA_AFRL (uint32_t*) (0x40020000 + 0x20)

#define GPIOB_MODER (uint32_t*) 		(0x40020400+0x00)
#define GPIOB_OTYPER (uint32_t*)    (0x40020400+0x04)
#define GPIOB_OSPEEDR (uint32_t*)   (0x40020400+0x08)
#define GPIOB_PUPDR (uint32_t*)     (0x40020400+0x0C)
#define GPIOB_BSRRL (uint32_t*)    (0x40020400+0x18)
#define GPIOB_ODR (uint32_t*)    (0x40020400+0x14)

void delay (void)
{
  long int  d;
  for (d = 0; d < 200000; d++)  
  ;	/* only to delay for LED flashes */
}

int i;
char a[50]={"Programming with ARM Cortex-USART2"};

int main(void)
{
	//*RCC_APB2ENR =0x0004000;	/*enable clock for usart*/
	*RCC_APB1ENR =(0x00020000); //Clock for USART2
	*RCC_AHBENR = (0x00000003); /* Enable GPIOB clock */
	
	*USART_BRR = (0x000000D0);
	*USART_CR1 = (0x00002008);
	*USART_CR2 = (0x00000800);
	//*RCC_APB2ENR =(0x0004000);
	//*USART_SR=(0x00000040);
	
	
	*GPIOA_MODER &= ~(0x000000F0);
	*GPIOA_MODER |= 0x000000A0; 			//Alternate function
	*GPIOA_OTYPER = (0x00000000);				/* Output push-pull */
	*GPIOA_OSPEEDR &= ~(0x000000F0);
	*GPIOA_OSPEEDR |= (0x000000F0);			/* 2 MHz Low speed */
	*GPIOA_PUPDR =(0x00000050);
	*GPIOA_AFRL = (0x00000700);  			//Setting to USART alternate function AF7
	
	//For LED	
*GPIOB_MODER &=~(0x0000F000);
*GPIOB_MODER |=(0x00005000);
*GPIOB_OTYPER &=~(0x000000C0);
*GPIOB_OSPEEDR &=~(0x0000F000);
*GPIOB_OSPEEDR |=(0x00005000);
*GPIOB_PUPDR &=~(0x0000F000);
	//*USART_DR=a[i];
	
	while(1)
	{
			
		for(i=0;a[i]!='\0';i++)
		{
			*USART_DR=a[i];
		while(*USART_SR!=0x000000C0);
		}
			*GPIOB_ODR^=(1UL<<6);
			//delay();
		}
}

