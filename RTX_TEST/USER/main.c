#include "stm32f10x.h"
#include "USART.h"
#include "cmsis_os.h"


void ledTask1(void const *p);
void ledTask2(void const *p);

osThreadId ledTaskLed1;
osThreadDef(ledTask1,osPriorityNormal, 1, 0); //优先级请使用枚举类型，具体查看osPriorityNormal定义部分
osThreadId ledTaskLed2;
osThreadDef(ledTask2,osPriorityNormal, 1, 0);//优先级请使用枚举类型，具体查看osPriorityNormal定义部分

int main(void)
{  
	USART1_Init();
	USART1_PrintString("This is the TEST\r\n");
	

	
	RCC->APB2ENR |= (1<<2)|(1<<5);
	GPIOA->CRH &= ~0xf;
	GPIOA->CRH |= 0X03;
	GPIOA->ODR |= ((1<<8));
	GPIOD->CRL &= ~(0XF<<8);
	GPIOD->CRL |= 0X3<<8;
	GPIOD->ODR |= ((1<<2));
	
	osKernelInitialize();
	ledTaskLed1=osThreadCreate(osThread(ledTask1), NULL);
	ledTaskLed2=osThreadCreate(osThread(ledTask2), NULL);
	osKernelStart();

	while(1);
}


void ledTask1(void const *p)
{
	while(1)
	{	
		osDelay(1000);
		GPIOA->ODR &= ~(1<<8);
		osDelay(1000);
		GPIOA->ODR |= (1<<8);
	}
}

void ledTask2(void const *p)
{
	while(1)
	{	
		osDelay(1000);
		GPIOD->ODR &= ~(1<<2);
		osDelay(1000);
		GPIOD->ODR |= (1<<2);
	}
}


