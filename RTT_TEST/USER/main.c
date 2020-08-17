#include "stm32f10x.h"
#include "rtthread.h"
#include "board.h"
#include "USART.h"
#include "DAC.h"

const unsigned int SIN[63]={
2048 ,2252 ,2455 ,2653 ,2846 ,3030 ,3204 ,3367 ,3517 ,3652 ,3771 ,3873 ,3957 ,4021 ,4066 ,4091 ,4095 ,4079 ,4042 ,
3986 ,3910 ,3816 ,3704 ,3575 ,3431 ,3274 ,3104 ,2923 ,2734 ,2538 ,2337 ,2133 ,1928 ,1725 ,1525 ,1330 ,1142 ,963 ,
795 ,639 ,498 ,372 ,263 ,172 ,99 ,46 ,13 ,0 ,8 ,36 ,84 ,152 ,239 ,344 ,465 ,603 ,755 ,920 ,1096 ,1282 ,1476 ,1675 ,
1878 
};

void ledinit(void)
{
	RCC->APB2ENR|=(1<<3)|(1<<6);
	
	GPIOB->CRL&=0XFF0FFFFF;
	GPIOB->CRL|=0X00300000;
	GPIOB->BSRR|=(1<<5);	
	GPIOE->CRL&=0XFF0FFFFF;
	GPIOE->CRL|=0X00300000;
	GPIOE->BSRR|=(1<<5);	
}

unsigned int Re=0;

unsigned char i=0;
#define  LED1_ON    GPIOB->BRR|=(1<<5);
#define  LED1_OFF   GPIOB->BSRR|=(1<<5);

#define  LED2_ON    GPIOE->BRR|=(1<<5);
#define  LED2_OFF   GPIOE->BSRR|=(1<<5);
void task1(void *p)
{
	while(1)
	{
		if(Re==4000)
		{LED2_OFF; Re=0;
			for(i=0;i<4;i++)
			{
			 Receive1BUFF[i]=48;
			}
		}
		if(Re==5000)
		{LED2_ON; Re=0;
     for(i=0;i<4;i++)
			{
			 Receive1BUFF[i]=48;
			} 
		}
	}
}

void task2(void *p)
{
	while(1)
	{
//		LED2_ON;
//		rt_thread_delay(500);
//		LED2_OFF;
//		rt_thread_delay(500000);
	//	USART1_PrintNumber(7000);
	//	rt_thread_delay(500);
	 Re=( Receive1BUFF[0]-48)*1000+(Receive1BUFF[1]-48)*100+(Receive1BUFF[2]-48)*10+(Receive1BUFF[3]-48);	
//		 USART1_PrintNumber(Re);
//		 USART1_PrintString(Receive1BUFF);
//		 USART1_PrintString("\n");
	}
}


int main(void)
{	
	rt_thread_t TE,Th;
	ledinit();
	USART1_Init();
	DAC1_Init();
  LED1_ON;
	LED2_ON;
	for(i=0;i<4;i++)
			{
			 Receive1BUFF[i]=48;
			}
	Th=rt_thread_create("test2",task2,NULL,200,10,5); 
	TE=rt_thread_create("test1",task1,NULL,200,10,5); 
	rt_thread_startup(Th);
	rt_thread_startup(TE);
	while(1)
	{
		 rt_thread_delay(5000000);
		 for(i=0;i<63;i++)
		  {
				DAC1_DATE[i]=SIN[i]/10;
			}
		 rt_thread_delay(5000000);
     	for(i=0;i<63;i++)
		  {
				DAC1_DATE[i]=SIN[i];
			}		
	}
}


