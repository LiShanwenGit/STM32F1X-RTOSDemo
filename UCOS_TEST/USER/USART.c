/**************************************************************************
* �ļ�����USART.c                                                         *
* ��д�ˣ����ŵķ�                                                        *
* ����ʱ�䣺2018.10.6                                                     *
* ˵�������ļ����ڿ�Դ������Ȩ���κ��˿���					                    	*
* ������������ϵ���䣺1477153217@qq.com                                   *
*                                                                         *
* USART���ò������£�                                                     *
* 1.ʹ��USARTʱ��                                                         *
* 2.����USART�Ĵ���(CR1:[13],[2],[3];BRR:[15:4],[4:0]                     *
* 3.����USART���ȼ�����                                                   *
* 4.д���ֽڵ����ݼĴ���(DR)�У�һ��ֻ�ܷ���һ���ֽ�                      *
*                                                                         *
* ��ע�⣺ÿ�η���һ���ֽڱ���Ҫ��ʱ�����ܲ���ϵķ��ͣ���������������  *
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


/*##############################����ΪUSART1��������#################################################*/
#if(USART1_EN==1)
void USART1_Init(void)
{   
   unsigned int integer;                   //����һ���������洢��������
   float   decimal;                        //����һ���������洢С������
   RCC->APB2ENR|=(1<<14)|(1<<2);           //����USART1ʱ�Ӻ�GPIOAʱ��
	 RCC->APB2RSTR|=(1<<14);                 //��λ����USART1
	 RCC->APB2RSTR&=(~(1<<14));              //ֹͣ��λ
	
	 GPIOA->CRH&=0XFFFFF00F;                 //���֮ǰ����PA10��PA9
	 GPIOA->CRH|=0X000008B0;                 //����PA10Ϊ�������룬����PA9Ϊ�����������
	
	
   USART1->CR1|=(1<<13);                   //ʹ��USARTģ��
   USART1->CR1|=(1<<2);                    //ʹ�ܽ���
	 USART1->CR1|=(1<<5);                    //���ж�
   USART1->CR1|=(1<<3);                    //ʹ�ܷ���	
	 
	
   integer=72*1000*1000/(USART1_BaudRate*16);         //ȡ����������
   decimal=(float)(72*1000*1000/(USART1_BaudRate*16))-integer;   //ȡ��С������
   USART1->BRR=(integer<<4)|((unsigned int)decimal*16);  //��ת�����ֵ����BRR�Ĵ���
   
//   NVIC_SetPriorityGrouping(6);            //�������ȼ�����1
//   NVIC_SetPriority(USART1_IRQn, NVIC_EncodePriority(6,6,6));     //������ռ���ȼ�Ϊ1�������ȼ�Ϊ1
//   NVIC_EnableIRQ(USART1_IRQn);            //ʹ��USART�ж�
   
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
	unsigned char Receive=0;                  //����һ�����ܱ���
	 Receive=USART1->DR;                     //�����ݼĴ����е�ֵ�������ܱ���
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
 
/*###############################����ΪUSART2��������#################################################*/
#if(USART2_EN==1)	
void USART2_Init(void)
{   
   unsigned int integer;                   //����һ���������洢��������
   float   decimal;                        //����һ���������洢С������
   RCC->APB2ENR|=(1<<2);                   //����GPIOAʱ��
	 RCC->APB1ENR|=(1<<17);                  //����USART2ʱ��
	 RCC->APB1RSTR|=(1<<17);                 //��λ����USART2
	 RCC->APB1RSTR&=(~(1<<17));              //ֹͣ��λ
	
	

	
	 GPIOA->CRL&=0XFFFFF00F;                 //���֮ǰ����PA3��PA2
	 GPIOA->CRL|=0X000008B0;                 //����PA3Ϊ�������룬����PA2Ϊ�����������
	
	
   USART2->CR1|=(1<<13);                   //ʹ��USARTģ��
   USART2->CR1|=(1<<2);                    //ʹ�ܽ���
	 USART2->CR1|=(1<<5);                    //���ж�
   USART2->CR1|=(1<<3);                    //ʹ�ܷ���	
	 
	
   integer=72*1000*1000/(USART2_BaudRate*16);         //ȡ����������
   decimal=(float)(72*1000*1000/(USART2_BaudRate*16))-integer;   //ȡ��С������
   USART2->BRR=(integer<<4)|((unsigned int)decimal*16);  //��ת�����ֵ����BRR�Ĵ���
   
   NVIC_SetPriorityGrouping(1);            //�������ȼ�����1
   NVIC_SetPriority(USART2_IRQn, NVIC_EncodePriority(1,2,2));     //������ռ���ȼ�Ϊ1�������ȼ�Ϊ2
   NVIC_EnableIRQ(USART2_IRQn);            //ʹ��USART�ж�
   
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
	unsigned char Receive=0;                  //����һ�����ܱ���
	 Receive=USART2->DR;                     //�����ݼĴ����е�ֵ�������ܱ���
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

/*##############################����ΪUSART3��������#################################################*/
#if(USART3_EN==1)		
void USART3_Init(void)
{   
   unsigned int integer;                   //����һ���������洢��������
   float   decimal;                        //����һ���������洢С������
   RCC->APB2ENR|=(1<<3);                   //����GPIOBʱ��
	 RCC->APB1ENR|=(1<<18);                  //����USART3ʱ��
	 RCC->APB1RSTR|=(1<<18);                 //��λ����USART3
	 RCC->APB1RSTR&=(~(1<<18));              //ֹͣ��λ
	
	 GPIOB->CRH&=0XFFFF00FF;                 //���֮ǰ����PB11��PB10
	 GPIOB->CRH|=0X00008B00;                 //����PB11Ϊ�������룬����PB10Ϊ�����������
	
	
   USART3->CR1|=(1<<13);                   //ʹ��USARTģ��
   USART3->CR1|=(1<<2);                    //ʹ�ܽ���
	 USART3->CR1|=(1<<5);                    //���ж�
   USART3->CR1|=(1<<3);                    //ʹ�ܷ���	
	 
	
   integer=72*1000*1000/(USART3_BaudRate*16);         //ȡ����������
   decimal=(float)(72*1000*1000/(USART3_BaudRate*16))-integer;   //ȡ��С������
   USART3->BRR=(integer<<4)|((unsigned int)decimal*16);  //��ת�����ֵ����BRR�Ĵ���
   
   NVIC_SetPriorityGrouping(1);            //�������ȼ�����1
   NVIC_SetPriority(USART3_IRQn, NVIC_EncodePriority(1,2,3));     //������ռ���ȼ�Ϊ1�������ȼ�Ϊ3
   NVIC_EnableIRQ(USART3_IRQn);            //ʹ��USART�ж�
   
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
	unsigned char Receive=0;                  //����һ�����ܱ���
	 Receive=USART3->DR;                     //�����ݼĴ����е�ֵ�������ܱ���
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

/*##############################����ΪUART4��������#################################################*/
#if(UART4_EN==1)	
void UART4_Init(void)
{   
   unsigned int integer;                   //����һ���������洢��������
   float   decimal;                        //����һ���������洢С������
   RCC->APB2ENR|=(1<<4);                   //����GPIOCʱ��
	 RCC->APB1ENR|=(1<<19);                  //����USART4ʱ��
	 RCC->APB1RSTR|=(1<<19);                 //��λ����USART4
	 RCC->APB1RSTR&=(~(1<<19));              //ֹͣ��λ
	
	 GPIOC->CRH&=0XFFFF00FF;                 //���֮ǰ����PC11��PC10
	 GPIOC->CRH|=0X00008B00;                 //����PC11Ϊ�������룬����PC10Ϊ�����������
	
	
   UART4->CR1|=(1<<13);                   //ʹ��USARTģ��
   UART4->CR1|=(1<<2);                    //ʹ�ܽ���
	 UART4->CR1|=(1<<5);                    //���ж�
   UART4->CR1|=(1<<3);                    //ʹ�ܷ���	
	 
	
   integer=72*1000*1000/(UART4_BaudRate*16);         //ȡ����������
   decimal=(float)(72*1000*1000/(UART4_BaudRate*16))-integer;   //ȡ��С������
   UART4->BRR=(integer<<4)|((unsigned int)decimal*16);  //��ת�����ֵ����BRR�Ĵ���
   
   NVIC_SetPriorityGrouping(1);            //�������ȼ�����1
   NVIC_SetPriority(UART4_IRQn, NVIC_EncodePriority(1,2,4));     //������ռ���ȼ�Ϊ1�������ȼ�Ϊ3
   NVIC_EnableIRQ(UART4_IRQn);            //ʹ��USART�ж�
   
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
	unsigned char Receive=0;                  //����һ�����ܱ���
	 Receive=UART4->DR;                     //�����ݼĴ����е�ֵ�������ܱ���
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

/*##############################����ΪUART5��������#################################################*/
#if(UART5_EN==1)	
void UART5_Init(void)
{   
   unsigned int integer;                   //����һ���������洢��������
   float   decimal;                        //����һ���������洢С������
   RCC->APB2ENR|=(1<<4);                   //����GPIOCʱ��
	 RCC->APB2ENR|=(1<<5);                   //����GPIODʱ��
	 RCC->APB1ENR|=(1<<20);                  //����USART4ʱ��
	 RCC->APB1RSTR|=(1<<20);                 //��λ����USART4
	 RCC->APB1RSTR&=(~(1<<20));              //ֹͣ��λ
	
	 GPIOC->CRH&=0XFFF0FFFF;                 //���֮ǰ����PC12
	 GPIOC->CRH|=0X000B0000;                 //����PC1Ϊ�������룬����PC12Ϊ�����������
	 GPIOD->CRL&=0XFFFFF0FF;                 //���֮ǰ����PD2
	 GPIOD->CRL|=0X00000800;                 //����PD2Ϊ��������
	
	
   UART5->CR1|=(1<<13);                   //ʹ��USARTģ��
   UART5->CR1|=(1<<2);                    //ʹ�ܽ���
	 UART5->CR1|=(1<<5);                    //���ж�
   UART5->CR1|=(1<<3);                    //ʹ�ܷ���	
	 
	
   integer=72*1000*1000/(UART5_BaudRate*16);         //ȡ����������
   decimal=(float)(72*1000*1000/(UART5_BaudRate*16))-integer;   //ȡ��С������
   UART5->BRR=(integer<<4)|((unsigned int)decimal*16);  //��ת�����ֵ����BRR�Ĵ���
   
   NVIC_SetPriorityGrouping(1);            //�������ȼ�����1
   NVIC_SetPriority(UART5_IRQn, NVIC_EncodePriority(1,2,5));     //������ռ���ȼ�Ϊ1�������ȼ�Ϊ3
   NVIC_EnableIRQ(UART5_IRQn);            //ʹ��USART�ж�
   
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
	unsigned char Receive=0;                  //����һ�����ܱ���
	 Receive=UART5->DR;                     //�����ݼĴ����е�ֵ�������ܱ���
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

