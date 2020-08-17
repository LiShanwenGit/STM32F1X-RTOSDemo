#include "stm32f10x.h"
#include "includes.h"
#include "SysTick.h"
#include "USART.h"

static unsigned int  MyTask1[256];
static unsigned int  MyTask2[256];

void ledTask1(void *p);
void ledTask2(void *p);

OS_EVENT  * semaphore;

INT8U err;

int main(void)
{  
	
  Systick_Init();
	USART1_Init();
	USART1_PrintString("This is the TEST\r\n");
	RCC->APB2ENR |= (1<<2)|(1<<5);
	GPIOA->CRH &= ~0xf;
	GPIOA->CRH |= 0X03;
	GPIOA->ODR |= ((1<<8));
	GPIOD->CRL &= ~(0XF<<8);
	GPIOD->CRL |= 0X3<<8;
	GPIOD->ODR |= ((1<<2));
	OSInit();
	OSTaskCreate((void(*)(void *))&ledTask1,NULL,(OS_STK *)&MyTask1[255],1);
	OSTaskCreate((void(*)(void *))&ledTask2,NULL,(OS_STK *)&MyTask2[255],2);
	semaphore=OSSemCreate(1);
	OSStart();
	GPIOA->ODR |= (1<<8);
	
	while(1)
	{	
	}
}


void ledTask1(void *p)
{
	
	while(1)
	{	
		OSSemPend(semaphore,0,&err);
		USART1_PrintString("This is the Task1\r\n");
		OSTimeDlyHMSM(0,0,2,0);
		GPIOA->ODR &= ~(1<<8);
		OSTimeDlyHMSM(0,0,2,0);
		GPIOA->ODR |= (1<<8);
		OSSemPost(semaphore);
	}
}

void ledTask2(void *p)
{
	while(1)
	{	
		OSSemPend(semaphore,0,&err);
		USART1_PrintString("This is the Task2\r\n");
		OSTimeDlyHMSM(0,0,0,500);
		GPIOD->ODR &= ~(1<<2);
		OSTimeDlyHMSM(0,0,0,500);
		GPIOD->ODR |= (1<<2);
		OSSemPost(semaphore);
	}
}


