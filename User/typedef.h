/*****************************************************************************
Copyright (C), 2009-2012, ASZENO Tech.Co.,Ltd.
File name : typedef.h
Author : King          Version :                 Date : 
Description : data type definition
Ohters : 
Function List : 
History :
1.
  Data : 
  Author : King
  Modification : 
*****************************************************************************/
#ifndef __TYPEDEFS_H__
#define __TYPEDEFS_H__

#include "stm32f10x.h"


typedef signed   char       INT8S,  S8;
typedef unsigned char       BYTE,   INT8U,  U8;
typedef signed   short int  INT16S, S16;
typedef unsigned short int  WORD,   INT16U, U16;
typedef signed   long       LONG,   INT32S, S32;
typedef unsigned long       DWORD,  INT32U, U32;

#define USER_CMD_GET_ADC		1
#define USER_CMD_GET_DMA		2
#define USER_CMD_GET_DAC		3
#define USER_CMD_TEST_IIC		4
#define USER_CMD_TEST_IIC_ACK	5


typedef struct _BTM_STATUS_STRUCT_
{
	FlagStatus Power;
	FlagStatus Pairing;
	FlagStatus PairingState;
	FlagStatus HFLink;
	FlagStatus A2DpLink;
	FlagStatus SCOLink;
	FlagStatus AVRCPLink;
	FlagStatus SPPLink;
	FlagStatus StandbyState;
	FlagStatus IAPState;
	FlagStatus ACLState;
	U8 Description;	
} BTM_STATUS;


typedef struct __SEND_APP_DATA_FLAG_STRUCT_
{
    U8 SendFlag;
    U8 PacketCount;
} SEND_APP_DATA_FLAG;

#endif

/******************** (C) COPYRIGHT 2012ASZENO TECH ********END OF FILE********/
