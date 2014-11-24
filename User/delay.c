/**
  ******************************************************************************
  * @file    delay.c 
  * @author  
  * @version V0.2.0
  * @date    
  * @brief   
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

#include "stm32f10x.h"
#include "delay.h"
#include "printf.h"
#include "global.h"

static u8  fac_us=0;//us��ʱ������
static u16 fac_ms=0;//ms��ʱ������

//��ʼ���ӳٺ���
//SYSTICK��ʱ�ӹ̶�ΪHCLKʱ�ӵ�1/8
//SYSCLK:ϵͳʱ��
void Delay_init(u8 SYSCLK)
{
	SysTick->CTRL&=0xfffffffb;//bit2���,ѡ���ⲿʱ��  HCLK/8
	fac_us=SYSCLK/8;		    
	fac_ms=(u16)fac_us*1000;
}	

//��ʱnms
//ע��nms�ķ�Χ
//SysTick->LOADΪ24λ�Ĵ���,����,�����ʱΪ:
//nms<=0xffffff*8*1000/SYSCLK
//SYSCLK��λΪHz,nms��λΪms
//��72M������,nms<=1864 
void Delay_1ms(u16 nms)
{	 		  	  
	u32 temp;
	//Puts("\r\n Delay_1ms");
	SysTick->LOAD=(u32)nms*fac_ms;//ʱ�����(SysTick->LOADΪ24bit)
	SysTick->VAL =0x00;           //��ռ�����
	SysTick->CTRL=0x01 ;          //��ʼ����  
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));//�ȴ�ʱ�䵽��   
	SysTick->CTRL=0x00;       //�رռ�����
	SysTick->VAL =0X00;       //��ռ�����	  
	//Puts("\r\n Delay_1ms end");
}

//��ʱnus
//nusΪҪ��ʱ��us��.		    								   
void Delay_1us(u32 nus)
{	
	//delayUS(nus);
	#if 1
	
	u32 temp;	
	//Puts("\r\n Delay_1us");
	//printf("\r\n delay_us%d",nus);
	SysTick->LOAD=nus*fac_us; //ʱ�����	  		 
	SysTick->VAL=0x00;        //��ռ�����
	SysTick->CTRL=0x01 ;      //��ʼ���� 	 
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));//�ȴ�ʱ�䵽��   
	SysTick->CTRL=0x00;       //�رռ�����
	SysTick->VAL =0X00;       //��ռ�����	
	#endif
	//Puts("\r\n Delay_1us end");
}
