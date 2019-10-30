
#include <STM32L1XX.h>

typedef unsigned int unit32_t;
typedef unsigned short uint16_t;
#define RCC_AHBENR (uint16_t*)      (0x40023800+0x00001C)
#define GPIOB_MODER (uint32_t*)     (0x40020400+0x00)
#define GPIOB_OTYPER (uint32_t*)    (0x40020400+0x04)
#define GPIOB_OSPEEDR (uint32_t*)   (0x40020400+0x08)
#define GPIOB_PUPDR (uint32_t*)     (0x40020400+0x0C)
#define GPIOB_BSRRL (uint32_t*)    (0x40020400+0x18)

//uint32_t temp,temp1,temp2;


void delay (void)
{
  long int  d;
  for (d = 0; d < 200000; d++)  
  ;	/* only to delay for LED flashes */
}


int main(void)
{
*RCC_AHBENR=(1UL<<1);
*GPIOB_MODER &=~(0x0000F000);
*GPIOB_MODER |=(0x00005000);
*GPIOB_OTYPER &=~(0x00000C0);
*GPIOB_OSPEEDR &=~(0x0000F000);
*GPIOB_OSPEEDR |=~(0x00005000);
*GPIOB_PUPDR &=~(0x0000F000);
	while(1)
	{
//*GPIOB_BSRRL=1UL<<6;
*GPIOB_BSRRL=1UL<<7;
		delay();
//*GPIOB_BSRRL=1UL<<22;
	//	delay();
*GPIOB_BSRRL=1UL<<23;
	delay();
}

}
unit32_t temp,temp1,temp2;


void delay(void)
{
int i;
for(i=0;i<10000;i++)
for(i=0;i<10000;i++)
for(i=0;i<10000;i++)
for(i=0;i<10000;i++)
}


int main(void)
{
*RCC_AHBENR=(1UL<<1);
*GPIOB_MODER &=~(0x0000F000);
*GPIOB_MODER |=(0x00005000);
*GPIOB_OTYPER &=~(0x00000C0);
*GPIOB_OSPREEDR &=~(0x0000F000);
*GPIOB_OSPREEDR |=~(0x00005000);
*GPIOB_PUPDR &=~(0x0000F000);
	
*GPIOB_BSRRL=1UL<<6;
	delay();
*GPIOB_BSRRL=1UL<<22;
*GPIOB_BSRRL=1UL<<7;
	delay();
*GPIOB_BSRRL=1UL<<23;
}