/********************************************************************************************************
* 文件名：SysTick.c                                                                                     *
* 编写人: 离逝的风 										                                                                  *
* 更新时间:2018.9.22										                                                                *
* 地点：xx									                                                                            *
* 说明：此文件属于开源，所有权对任何人开放					                                                  	*
*													                                                                              *
* 系统时钟定时配置步骤如下:										                                                          *
* 1.调用core_m3.h文件中的SysTick_Config()函数,此函数参数为(LOAD)装载值,默认失踪为AHB时钟(72M),          *
*  [注意：此值不宜太小]此函数返回1表示失败,返回0表示成功					                                      *
* 2.添加中断服务函数											                                                              *
* 备注:若搭载了操作系统，那系统定时器谨慎使用，建议不使用				                                        *
*********************************************************************************************************/
//Example:  SysTick
#include "SysTick.h"
#include "includes.h"					//ucos 使用	  

void Systick_Init(void)
{
   while(SysTick_Config(72000000/100));     //每秒切换100次
}
   
void SysTick_Handler(void)
{
   /*insert your interrupt progarm*/
	  OSIntEnter();		    //进入中断
    OSTimeTick();       //调用ucos的时钟服务程序               
    OSIntExit();        //触发任务切换软中断
}
    
void SysDelay_10us(void)                      //此函数为10us
{ 
   unsigned char flag=1;              //定义一个标志变量
   while(flag)                        //当标志位为0时结束
   {
      if((SysTick->CTRL&(1<<16))>>16==1)     //读取CTRL的第16位值,如果为1,表示时间已到
	    {
	     flag=0;                     //将标志位置0,结束循环
	    }
			 
   }
}
   
void SysDelay_ms(unsigned int ms)        //定义一个ms函数
{
   unsigned char counter;
   while(ms--)
   {
     for(counter=0;counter<100;counter++)
     SysDelay_10us();
    }
}

void SysDelay_s(unsigned int s)          //定义一个s函数
{
    while(s--)
    SysDelay_ms(1000);
}
      

