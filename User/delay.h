/**
  ******************************************************************************
  * @file    delay.h
  * @author  
  * @version V0.2.0
  * @date    
  * @brief   
  ******************************************************************************
  * @attention
  *
  * 
  *
  ******************************************************************************
  */
#ifndef __DELAY_H
#define __DELAY_H 			   
#include "stm32f10x.h"
//#include "old_def.h"

//V1.2修改说明
//修正了中断中调用出现死循环的错误
//防止延时不准确,采用do while结构!
////////////////////////////////////////////////////////////////////////////////// 
void Delay_init(u8 SYSCLK);
void Delay_1ms(u16 nms);
void Delay_1us(u32 nus);

#endif





























