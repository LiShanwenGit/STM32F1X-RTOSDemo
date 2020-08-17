/********************************************************************************************************
* �ļ�����SysTick.c                                                                                     *
* ��д��: ���ŵķ� 										                                                                  *
* ����ʱ��:2018.9.22										                                                                *
* �ص㣺xx									                                                                            *
* ˵�������ļ����ڿ�Դ������Ȩ���κ��˿���					                                                  	*
*													                                                                              *
* ϵͳʱ�Ӷ�ʱ���ò�������:										                                                          *
* 1.����core_m3.h�ļ��е�SysTick_Config()����,�˺�������Ϊ(LOAD)װ��ֵ,Ĭ��ʧ��ΪAHBʱ��(72M),          *
*  [ע�⣺��ֵ����̫С]�˺�������1��ʾʧ��,����0��ʾ�ɹ�					                                      *
* 2.����жϷ�����											                                                              *
* ��ע:�������˲���ϵͳ����ϵͳ��ʱ������ʹ�ã����鲻ʹ��				                                        *
*********************************************************************************************************/
//Example:  SysTick
#include "SysTick.h"
#include "includes.h"					//ucos ʹ��	  

void Systick_Init(void)
{
   while(SysTick_Config(72000000/100));     //ÿ���л�100��
}
   
void SysTick_Handler(void)
{
   /*insert your interrupt progarm*/
	  OSIntEnter();		    //�����ж�
    OSTimeTick();       //����ucos��ʱ�ӷ������               
    OSIntExit();        //���������л����ж�
}
    
void SysDelay_10us(void)                      //�˺���Ϊ10us
{ 
   unsigned char flag=1;              //����һ����־����
   while(flag)                        //����־λΪ0ʱ����
   {
      if((SysTick->CTRL&(1<<16))>>16==1)     //��ȡCTRL�ĵ�16λֵ,���Ϊ1,��ʾʱ���ѵ�
	    {
	     flag=0;                     //����־λ��0,����ѭ��
	    }
			 
   }
}
   
void SysDelay_ms(unsigned int ms)        //����һ��ms����
{
   unsigned char counter;
   while(ms--)
   {
     for(counter=0;counter<100;counter++)
     SysDelay_10us();
    }
}

void SysDelay_s(unsigned int s)          //����һ��s����
{
    while(s--)
    SysDelay_ms(1000);
}
      

