/**************************************************************************
* 文件名：USART.h                                                         *
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
#ifndef   __USART_H
#define   __USART_H

#include  "stm32f10x.h"

/**###########################文件配置，用户根据自己情况配置#########################*/
//需要使用则设置为1，否则为0
#define   USART1_EN                      1
#define   USART2_EN                      0   
#define   USART3_EN                      0
#define   UART4_EN                       0
#define   UART5_EN                       0
/**###########################参数定义部分，按用户要求修改#########################*/

#define  USART1_BaudRate       9600        //波特率设置，默认9600
#define  USART2_BaudRate       9600        //波特率设置，默认9600
#define  USART3_BaudRate       9600        //波特率设置，默认9600
#define  UART4_BaudRate        9600        //波特率设置，默认9600
#define  UART5_BaudRate        9600        //波特率设置，默认9600

/*#############################下面为USRAT1接口函数############################################*/
//备注：USART1引脚为PA9和PA10，使用USART1则这两个引脚无法用做别的
#if(USART1_EN==1)
void USART1_Init(void);                                
void USART1_PrintString( char *String);
unsigned char USART1_ReceiveByte(void);
void USART1_PrintNumber(unsigned long number);
extern char Receive1BUFF[4];   
#endif
/*#############################下面为USRAT2接口函数############################################*/
//备注：USART1引脚为PA3和PA2，使用USART2则这两个引脚无法用做别的
#if(USART2_EN==1)	 
void USART2_Init(void);
void USART2_PrintString( char *String);
unsigned char USART2_ReceiveByte(void);
void USART2_PrintNumber(unsigned long number);
extern char Receive2BUFF[40];
#endif
/*#############################下面为USRAT3接口函数############################################*/
//备注：USART3引脚为PB11和PB10，使用USART3则这两个引脚无法用做别的
#if(USART3_EN==1)	
void USART3_Init(void);
void USART3_PrintString( char *String);
unsigned char USART3_ReceiveByte(void);
void USART3_PrintNumber(unsigned long number);
extern char Receive3BUFF[40];
#endif
/*#############################下面为URAT4接口函数############################################*/
//备注：UART4引脚为PC11和PC10，使用UART4则这两个引脚无法用做别的
#if(UART4_EN==1)
void UART4_Init(void);
void UART4_PrintString( char *String);
unsigned char UART4_ReceiveByte(void);
void UART4_PrintNumber(unsigned long number);
extern char Receive4BUFF[40];
#endif

/*#############################下面为URAT5接口函数############################################*/
//备注：UART5引脚为PC12和PD2，使用UART5则这两个引脚无法用做别的
#if(UART5_EN==1)	
void UART5_Init(void);
void UART5_PrintString( char *String);
unsigned char UART5_ReceiveByte(void);
void UART5_PrintNumber(unsigned long number);
extern char Receive5BUFF[40];
#endif

#endif


