#ifndef __I2C_H__
#define __I2C_H__

#undef EXTERN

#ifdef __I2C_C__
#define EXTERN
#else
#define EXTERN extern
#endif


#include "typedef.h"
#include "stm32f10x.h"

#define IIC_SCL_PORT              GPIOB
#define IIC_SCL_CLK               RCC_APB2Periph_GPIOB  
#define IIC_SCL_PIN               GPIO_Pin_6

#define IIC_SDA_PORT              GPIOB
#define IIC_SDA_CLK               RCC_APB2Periph_GPIOB  
#define IIC_SDA_PIN               GPIO_Pin_7

#define SDA_IN()  {GPIOB->CRH&=0X0FFFFFFF;GPIOB->CRL|=8<<7;}
#define SDA_OUT() {GPIOB->CRH&=0X0FFFFFFF;GPIOB->CRL|=3<<7;}


#define Set_IIC_SCL  {GPIO_SetBits(IIC_SCL_PORT,	IIC_SCL_PIN);}
#define Clr_IIC_SCL  {GPIO_ResetBits(IIC_SCL_PORT,	IIC_SCL_PIN);} 
#define Set_IIC_SDA  {GPIO_SetBits(IIC_SDA_PORT,	IIC_SDA_PIN);}
#define Clr_IIC_SDA  {GPIO_ResetBits(IIC_SDA_PORT,	IIC_SDA_PIN);} 
#define READ_SDA    (GPIO_ReadInputDataBit(IIC_SDA_PORT, IIC_SDA_PIN))

EXTERN void IIC_Init(void);
EXTERN void IIC_Send_Byte(u8 txd);
EXTERN u8 IIC_Read_Byte(unsigned char ack);
EXTERN void IIC_Start(void);
EXTERN U8 IRcvStr(U8 sla, U8 suba, U8 *s, U8 no);
EXTERN U8 ISendStr(U8 sla, U8 suba, U8 *s, U8 no);
EXTERN u8 AT24CXX_ReadOneByte(u16 ReadAddr);
EXTERN void AT24CXX_WriteOneByte(u16 WriteAddr,u8 DataToWrite);
EXTERN U8 Read(U8 addr);
EXTERN U8  Write(U8 addr, U8 dat);

#endif

