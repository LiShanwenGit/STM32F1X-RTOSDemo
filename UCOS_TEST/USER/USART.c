/**************************************************************************
* 文件名：USART.c                                                         *
* 编写人：离逝的风                                                        *
* 更新时间：2018.10.6                                                     *
* 说明：此文件属于开源，所有权对任何人开放					                    	*
* 如有问题请联系邮箱：1477153217@qq.com                                   *
*                                                                         *
* USART配置步骤如下：                                                     *
* 1.使能USART时钟                                                         *
* 2.配置USART寄存器(CR1:[13],[2],[3];BRR:[15:4],[4:0]                     *
* 3.配置USART优先级分组                                                   *
* 4.写入字节到数据寄存器(DR)中，一次只能发送一个字节                      *
*                                                                         *
* ！注意：每次发送一个字节必须要延时，不能不间断的发送，否则导致数据乱码  *
***************************************************************************/
//Example:  USART1   bit rate: 9600,CRC: none ,stop bit: n bit

#include  "USART.h"
#if(USART1_EN==1)
		char Receive1BUFF[100]={0};
		unsigned char USART1_ReCoun=0;
#endif
#if(USART2_EN==1)	 
		char Receive2BUFF[40]={0};
		unsigned char USART2_ReCoun=0;
#endif
#if(USART3_EN==1)		
		char Receive3BUFF[40]={0};
		unsigned char USART3_ReCoun=0;
#endif
#if(UART4_EN==1)			
		char Receive4BUFF[40]={0};
		unsigned char UART4_ReCoun=0;
#endif
#if(UART5_EN==1)		
		char Receive5BUFF[40]={0};
		unsigned char UART5_ReCoun=0;
#endif


/*##############################下面为USART1函数部分#################################################*/
#if(USART1_EN==1)
void USART1_Init(void)
{   
   unsigned int integer;                   //定义一个变量，存储整数部分
   float   decimal;                        //定义一个变量，存储小数部分
   RCC->APB2ENR|=(1<<14)|(1<<2);           //开启USART1时钟和GPIOA时钟
	 RCC->APB2RSTR|=(1<<14);                 //复位外设USART1
	 RCC->APB2RSTR&=(~(1<<14));              //停止复位
	
	 GPIOA->CRH&=0XFFFFF00F;                 //清除之前配置PA10和PA9
	 GPIOA->CRH|=0X000008B0;                 //配置PA10为上拉输入，配置PA9为复用推挽输出
	
	
   USART1->CR1|=(1<<13);                   //使能USART模块
   USART1->CR1|=(1<<2);                    //使能接收
	 USART1->CR1|=(1<<5);                    //开中断
   USART1->CR1|=(1<<3);                    //使能发送	
	 
	
   integer=72*1000*1000/(USART1_BaudRate*16);         //取出整数部分
   decimal=(float)(72*1000*1000/(USART1_BaudRate*16))-integer;   //取出小数部分
   USART1->BRR=(integer<<4)|((unsigned int)decimal*16);  //将转换后的值赋给BRR寄存器
   
//   NVIC_SetPriorityGrouping(6);            //设置优先级分组1
//   NVIC_SetPriority(USART1_IRQn, NVIC_EncodePriority(6,6,6));     //设置抢占优先级为1，子优先级为1
//   NVIC_EnableIRQ(USART1_IRQn);            //使能USART中断
   
}

void USART1_PrintNumber(unsigned long number)
{
      unsigned char usart_save[16]={0};
			unsigned char *usart_p;
			unsigned char i=1;
			unsigned int num=0;
			num=number;
				
			while(num/10)
			{
				num/=10;
				i++;
			}
			usart_p=usart_save;
			for(;i>0;i--)
			{
				usart_save[i-1]=number%10+48;
				number/=10;
			}
      while(*usart_p)
      {
      USART1->DR=*usart_p;                        
      while(!(USART1->SR&(1<<6)));
      usart_p++;
      }
	
}
   
void USART1_PrintString( char *String)
{
   char *p;                            
   p=String;
   while(*p)
   {
      USART1->DR=*p;                        
      while(!(USART1->SR&(1<<6)));
      p++;
    }
}

void USART1_PrintChar(char ch)
{
		USART1->DR=ch;                        
		while(!(USART1->SR&(1<<6)));
}


unsigned char USART1_ReceiveByte(void)
{
	unsigned char Receive=0;                  //定义一个接受变量
	 Receive=USART1->DR;                     //将数据寄存器中的值赋给接受变量
	return Receive;
}


void USART1_IRQHandler(void)
{
	while((USART1->SR&(1<<5))==0x20)
	  Receive1BUFF[USART1_ReCoun++]=USART1->DR; 
	if(Receive1BUFF[USART1_ReCoun-1]=='\n')
	{Receive1BUFF[USART1_ReCoun-1]=0;USART1_ReCoun=0;}
}
#endif
 
/*###############################下面为USART2函数部分#################################################*/
#if(USART2_EN==1)	
void USART2_Init(void)
{   
   unsigned int integer;                   //定义一个变量，存储整数部分
   float   decimal;                        //定义一个变量，存储小数部分
   RCC->APB2ENR|=(1<<2);                   //开启GPIOA时钟
	 RCC->APB1ENR|=(1<<17);                  //开启USART2时钟
	 RCC->APB1RSTR|=(1<<17);                 //复位外设USART2
	 RCC->APB1RSTR&=(~(1<<17));              //停止复位
	
	

	
	 GPIOA->CRL&=0XFFFFF00F;                 //清除之前配置PA3和PA2
	 GPIOA->CRL|=0X000008B0;                 //配置PA3为上拉输入，配置PA2为复用推挽输出
	
	
   USART2->CR1|=(1<<13);                   //使能USART模块
   USART2->CR1|=(1<<2);                    //使能接收
	 USART2->CR1|=(1<<5);                    //开中断
   USART2->CR1|=(1<<3);                    //使能发送	
	 
	
   integer=72*1000*1000/(USART2_BaudRate*16);         //取出整数部分
   decimal=(float)(72*1000*1000/(USART2_BaudRate*16))-integer;   //取出小数部分
   USART2->BRR=(integer<<4)|((unsigned int)decimal*16);  //将转换后的值赋给BRR寄存器
   
   NVIC_SetPriorityGrouping(1);            //设置优先级分组1
   NVIC_SetPriority(USART2_IRQn, NVIC_EncodePriority(1,2,2));     //设置抢占优先级为1，子优先级为2
   NVIC_EnableIRQ(USART2_IRQn);            //使能USART中断
   
}

void USART2_PrintNumber(unsigned long number)
{
      unsigned char usart_save[16]={0};
			unsigned char *usart_p;
			unsigned char i=1;
			unsigned int num=0;
			num=number;
				
			while(num/10)
			{
				num/=10;
				i++;
			}
			usart_p=usart_save;
			for(;i>0;i--)
			{
				usart_save[i-1]=number%10+48;
				number/=10;
			}
      while(*usart_p)
      {
      USART2->DR=*usart_p;                        
      while(!(USART2->SR&(1<<6)));
      usart_p++;
      }
	
}
   
void USART2_PrintString( char *String)
{
   char *p;                            
   p=String;
   while(*p)
   {
      USART2->DR=*p;                        
      while(!(USART2->SR&(1<<6)));
      p++;
    }
}

unsigned char USART2_ReceiveByte(void)
{
	unsigned char Receive=0;                  //定义一个接受变量
	 Receive=USART2->DR;                     //将数据寄存器中的值赋给接受变量
	return Receive;
}


void USART2_IRQHandler(void)
{
	while((USART2->SR&(1<<5))==0x20)
	  Receive2BUFF[USART2_ReCoun++]=USART2->DR; 
	if(USART2_ReCoun==40)
		USART2_ReCoun=0;
}
#endif

/*##############################下面为USART3函数定义#################################################*/
#if(USART3_EN==1)		
void USART3_Init(void)
{   
   unsigned int integer;                   //定义一个变量，存储整数部分
   float   decimal;                        //定义一个变量，存储小数部分
   RCC->APB2ENR|=(1<<3);                   //开启GPIOB时钟
	 RCC->APB1ENR|=(1<<18);                  //开启USART3时钟
	 RCC->APB1RSTR|=(1<<18);                 //复位外设USART3
	 RCC->APB1RSTR&=(~(1<<18));              //停止复位
	
	 GPIOB->CRH&=0XFFFF00FF;                 //清除之前配置PB11和PB10
	 GPIOB->CRH|=0X00008B00;                 //配置PB11为上拉输入，配置PB10为复用推挽输出
	
	
   USART3->CR1|=(1<<13);                   //使能USART模块
   USART3->CR1|=(1<<2);                    //使能接收
	 USART3->CR1|=(1<<5);                    //开中断
   USART3->CR1|=(1<<3);                    //使能发送	
	 
	
   integer=72*1000*1000/(USART3_BaudRate*16);         //取出整数部分
   decimal=(float)(72*1000*1000/(USART3_BaudRate*16))-integer;   //取出小数部分
   USART3->BRR=(integer<<4)|((unsigned int)decimal*16);  //将转换后的值赋给BRR寄存器
   
   NVIC_SetPriorityGrouping(1);            //设置优先级分组1
   NVIC_SetPriority(USART3_IRQn, NVIC_EncodePriority(1,2,3));     //设置抢占优先级为1，子优先级为3
   NVIC_EnableIRQ(USART3_IRQn);            //使能USART中断
   
}

void USART3_PrintNumber(unsigned long number)
{
      unsigned char usart_save[16]={0};
			unsigned char *usart_p;
			unsigned char i=1;
			unsigned int num=0;
			num=number;
				
			while(num/10)
			{
				num/=10;
				i++;
			}
			usart_p=usart_save;
			for(;i>0;i--)
			{
				usart_save[i-1]=number%10+48;
				number/=10;
			}
      while(*usart_p)
      {
      USART3->DR=*usart_p;                        
      while(!(USART3->SR&(1<<6)));
      usart_p++;
      }
	
}
   
void USART3_PrintString( char *String)
{
   char *p;                            
   p=String;
   while(*p)
   {
      USART3->DR=*p;                        
      while(!(USART3->SR&(1<<6)));
      p++;
    }
}

unsigned char USART3_ReceiveByte(void)
{
	unsigned char Receive=0;                  //定义一个接受变量
	 Receive=USART3->DR;                     //将数据寄存器中的值赋给接受变量
	return Receive;
}


void USART3_IRQHandler(void)
{
	while((USART3->SR&(1<<5))==0x20)
	  Receive3BUFF[USART3_ReCoun++]=USART3->DR; 
	if(USART3_ReCoun==40)
		USART3_ReCoun=0;
}

#endif

/*##############################下面为UART4函数定义#################################################*/
#if(UART4_EN==1)	
void UART4_Init(void)
{   
   unsigned int integer;                   //定义一个变量，存储整数部分
   float   decimal;                        //定义一个变量，存储小数部分
   RCC->APB2ENR|=(1<<4);                   //开启GPIOC时钟
	 RCC->APB1ENR|=(1<<19);                  //开启USART4时钟
	 RCC->APB1RSTR|=(1<<19);                 //复位外设USART4
	 RCC->APB1RSTR&=(~(1<<19));              //停止复位
	
	 GPIOC->CRH&=0XFFFF00FF;                 //清除之前配置PC11和PC10
	 GPIOC->CRH|=0X00008B00;                 //配置PC11为上拉输入，配置PC10为复用推挽输出
	
	
   UART4->CR1|=(1<<13);                   //使能USART模块
   UART4->CR1|=(1<<2);                    //使能接收
	 UART4->CR1|=(1<<5);                    //开中断
   UART4->CR1|=(1<<3);                    //使能发送	
	 
	
   integer=72*1000*1000/(UART4_BaudRate*16);         //取出整数部分
   decimal=(float)(72*1000*1000/(UART4_BaudRate*16))-integer;   //取出小数部分
   UART4->BRR=(integer<<4)|((unsigned int)decimal*16);  //将转换后的值赋给BRR寄存器
   
   NVIC_SetPriorityGrouping(1);            //设置优先级分组1
   NVIC_SetPriority(UART4_IRQn, NVIC_EncodePriority(1,2,4));     //设置抢占优先级为1，子优先级为3
   NVIC_EnableIRQ(UART4_IRQn);            //使能USART中断
   
}

void UART4_PrintNumber(unsigned long number)
{
      unsigned char usart_save[16]={0};
			unsigned char *usart_p;
			unsigned char i=1;
			unsigned int num=0;
			num=number;
				
			while(num/10)
			{
				num/=10;
				i++;
			}
			usart_p=usart_save;
			for(;i>0;i--)
			{
				usart_save[i-1]=number%10+48;
				number/=10;
			}
      while(*usart_p)
      {
      UART4->DR=*usart_p;                        
      while(!(UART4->SR&(1<<6)));
      usart_p++;
      }
	
}
   
void UART4_PrintString( char *String)
{
   char *p;                            
   p=String;
   while(*p)
   {
      UART4->DR=*p;                        
      while(!(UART4->SR&(1<<6)));
      p++;
    }
}

unsigned char UART4_ReceiveByte(void)
{
	unsigned char Receive=0;                  //定义一个接受变量
	 Receive=UART4->DR;                     //将数据寄存器中的值赋给接受变量
	return Receive;
}


void UART4_IRQHandler(void)
{
	while((UART4->SR&(1<<5))==0x20)
	  Receive4BUFF[UART4_ReCoun++]=UART4->DR; 
	if(UART4_ReCoun==40)
		UART4_ReCoun=0;
}

#endif

/*##############################下面为UART5函数定义#################################################*/
#if(UART5_EN==1)	
void UART5_Init(void)
{   
   unsigned int integer;                   //定义一个变量，存储整数部分
   float   decimal;                        //定义一个变量，存储小数部分
   RCC->APB2ENR|=(1<<4);                   //开启GPIOC时钟
	 RCC->APB2ENR|=(1<<5);                   //开启GPIOD时钟
	 RCC->APB1ENR|=(1<<20);                  //开启USART4时钟
	 RCC->APB1RSTR|=(1<<20);                 //复位外设USART4
	 RCC->APB1RSTR&=(~(1<<20));              //停止复位
	
	 GPIOC->CRH&=0XFFF0FFFF;                 //清除之前配置PC12
	 GPIOC->CRH|=0X000B0000;                 //配置PC1为上拉输入，配置PC12为复用推挽输出
	 GPIOD->CRL&=0XFFFFF0FF;                 //清除之前配置PD2
	 GPIOD->CRL|=0X00000800;                 //配置PD2为上拉输入
	
	
   UART5->CR1|=(1<<13);                   //使能USART模块
   UART5->CR1|=(1<<2);                    //使能接收
	 UART5->CR1|=(1<<5);                    //开中断
   UART5->CR1|=(1<<3);                    //使能发送	
	 
	
   integer=72*1000*1000/(UART5_BaudRate*16);         //取出整数部分
   decimal=(float)(72*1000*1000/(UART5_BaudRate*16))-integer;   //取出小数部分
   UART5->BRR=(integer<<4)|((unsigned int)decimal*16);  //将转换后的值赋给BRR寄存器
   
   NVIC_SetPriorityGrouping(1);            //设置优先级分组1
   NVIC_SetPriority(UART5_IRQn, NVIC_EncodePriority(1,2,5));     //设置抢占优先级为1，子优先级为3
   NVIC_EnableIRQ(UART5_IRQn);            //使能USART中断
   
}

void UART5_PrintNumber(unsigned long number)
{
      unsigned char usart_save[16]={0};
			unsigned char *usart_p;
			unsigned char i=1;
			unsigned int num=0;
			num=number;
				
			while(num/10)
			{
				num/=10;
				i++;
			}
			usart_p=usart_save;
			for(;i>0;i--)
			{
				usart_save[i-1]=number%10+48;
				number/=10;
			}
      while(*usart_p)
      {
      UART5->DR=*usart_p;                        
      while(!(UART5->SR&(1<<6)));
      usart_p++;
      }
	
}
   
void UART5_PrintString( char *String)
{
   char *p;                            
   p=String;
   while(*p)
   {
      UART5->DR=*p;                        
      while(!(UART5->SR&(1<<6)));
      p++;
    }
}

unsigned char UART5_ReceiveByte(void)
{
	unsigned char Receive=0;                  //定义一个接受变量
	 Receive=UART5->DR;                     //将数据寄存器中的值赋给接受变量
	return Receive;
}


void UART5_IRQHandler(void)
{
	while((UART5->SR&(1<<5))==0x20)
	  Receive5BUFF[UART5_ReCoun++]=UART5->DR; 
	if(UART5_ReCoun==40)
		UART5_ReCoun=0;
}

#endif

