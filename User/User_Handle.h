#ifndef __USER_HANDLE_H__
#define __USER_HANDLE_H__

#undef EXTERN

#ifdef __USER_HANDLE_C__
#define EXTERN
#else
#define EXTERN extern
#endif


#include "typedef.h"
#include "stm32f10x.h"

#define KEY_STATE_IDLE      0
#define KEY_STATE_DOWN      1
#define KEY_STATE_WAIT_UP   2
#define KEY_STATE_UP        3
#define KEY_STATE_DEBOUCE   4      
#define KEY_STATE_LONG      5

#define KEY_AD_RANGE        50

#define KEY_TRIGGER_VALUE	3548


#if 0
#define KEY_AD_RANGE        1500
#define KEY_TRIGGER_VALUE	3548
#endif

//#define KEY_AD_RANGE        50

#define KEY1_AD         1089//620
#define KEY1_AD_MAX     (KEY1_AD + KEY_AD_RANGE)
#define KEY1_AD_MIN     (KEY1_AD - KEY_AD_RANGE)
#define KEY2_AD         2114//1427
#define KEY2_AD_MAX     (KEY2_AD + KEY_AD_RANGE)
#define KEY2_AD_MIN     (KEY2_AD - KEY_AD_RANGE)
#define KEY3_AD         2718//2045
#define KEY3_AD_MAX     (KEY3_AD + KEY_AD_RANGE)
#define KEY3_AD_MIN     (KEY3_AD - KEY_AD_RANGE)
#define KEY4_AD         3083//2500
#define KEY4_AD_MAX     (KEY4_AD + KEY_AD_RANGE)
#define KEY4_AD_MIN     (KEY4_AD - KEY_AD_RANGE )
#define KEY5_AD         3320//2831
#define KEY5_AD_MAX     (KEY5_AD + KEY_AD_RANGE)
#define KEY5_AD_MIN     (KEY5_AD - KEY_AD_RANGE )
#define KEY6_AD         3488//3080
#define KEY6_AD_MAX     (KEY6_AD + KEY_AD_RANGE)
#define KEY6_AD_MIN     (KEY6_AD - KEY_AD_RANGE )
#define KEY7_AD         3612//3280
#define KEY7_AD_MAX     (KEY7_AD + KEY_AD_RANGE)
#define KEY7_AD_MIN     (KEY7_AD - KEY_AD_RANGE )
#define KEY8_AD         3754//3530
#define KEY8_AD_MAX     (KEY8_AD + KEY_AD_RANGE)
#define KEY8_AD_MIN     (KEY8_AD - KEY_AD_RANGE )


#define MSG_HEADER		0
#define MSG_LENGTH_H	1
#define MSG_LENGTH_L	2
#define MSG_CMD			3
#define MSG_DA1			4
#define MSG_DA2			5
#define MSG_DA3			6
#define MSG_DA4			7
#define MSG_DA5			8
#define MSG_DA6			9
#define MSG_DA7			10
#define MSG_DA8			11


#define SIGNAL_PACKEY	0x00
#define START_PACKEY	0x01
#define CONTINUE_PACKEY	0x02
#define END_PACKEY		0x03


#define BTM_MSG_CMD_ACK 				0x00
#define BTM_MSG_BTM_STATUS 				0x01
#define BTM_MSG_BATTERY_STATUS 			0x0C

#define MCU_TO_BTM_CMD_SEND_APP_DATA	0x12



#define CMD_ACK_PARAM_DESC_TRUE			0x00
#define CMD_ACK_PARAM_DESC_FAIL			0x01
#define CMD_ACK_PARAM_DESC_UNKNOW		0x02
#define CMD_ACK_PARAM_DESC_ERROE		0x03
#define CMD_ACK_PARAM_DESC_BUSY			0x04
#define CMD_ACK_PARAM_DESC_FULL			0x05
#define CMD_ACK_PARAM_DESC_RFD			0x06


#define QUEUE_ELEM_0	0x01
#define QUEUE_ELEM_1	0x02
#define QUEUE_ELEM_2	0x04
#define QUEUE_ELEM_3	0x08
#define QUEUE_ELEM_4	0x10



EXTERN U8 KeyScan(void);

EXTERN void Turn_On_LED(U8 LED_NUM);
EXTERN void SendMSGHandle(U8 Idx);
EXTERN void enQueue(void);
EXTERN void SendPackage(void);

EXTERN void Btm_stateMsgProcess(U8 state, U8 ucDat);
EXTERN void KeyProcess(U8 KeyValue);
EXTERN void BTMCMDHandler(void);
EXTERN U8 CheckSum(U8 *Str, WORD ucLength);
EXTERN void ClearArray(U8 *ucClearArray ,WORD ucLength);
EXTERN void ADS1299Process(void);

#if 0
EXTERN U8 KeyScan(U8 ucMode);
EXTERN void KeyHandle(U8 ucKeyIdx);
EXTERN void Digital_Display(U8 ucPolling);
EXTERN void BeepCtrl(U8 ucFlg);
EXTERN void AlarmpCtrl(U8 ucFlg);
#endif
#endif

