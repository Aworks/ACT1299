#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#undef EXTERN

#ifdef __GLOBAL_C__
#define EXTERN
#else
#define EXTERN extern
#endif


#include "typedef.h"
#include "ADS1299.h"


EXTERN __IO uint16_t ADCConvertedValue;
EXTERN U8 TimeSlice[5];
EXTERN FlagStatus GetSysClkFlg(U8 ucTmp);
#if 0
EXTERN U8 GetTask5msFlg(void);
EXTERN void SetTask5msFlg(U8 ucTmp);
#endif

#define SEND_MSG_CHANGENAME 		0x01
#define SEND_MSG_MUSIC_PLAY 		0x02
#define SEND_MSG_MUSIC_PAUSE 		0x03
#define SEND_MSG_MUSIC_PLAY_PAUSE	0x04
#define SEND_MSG_MUSIC_STOP 		0x05
#define SEND_MSG_POWEROFF 			0x06

EXTERN U8 ChangeName[37];
EXTERN U8 PowerOFF[7];	
EXTERN U8 MusicPlay[7];	
EXTERN U8 MusicPause[7];
EXTERN U8 MusicPlayPause[7];
EXTERN U8 MusicStop[7];	

EXTERN U8 Header[10];
EXTERN U8 buffer[5][256];
EXTERN U8 gucRcvQueueLocate;
EXTERN U8 RecCMDQueue[5][100];
EXTERN U8 Data[1000];
EXTERN U8 gucRCVFlg;
EXTERN U8 ReceiveMBBuff[100];

EXTERN BTM_STATUS GetBtm_state(void);
EXTERN void SetBtm_state(BTM_STATUS ucBtm_state);
EXTERN U8 GetChangeNameTimeout(void);
EXTERN void SetChangeNameTimeout(U8 ucTmp);
EXTERN U8 GetSendAppDataFlg(void);
EXTERN void SetSendAppDataFlg(U8 ucTmp);

EXTERN SEND_APP_DATA_FLAG SysSendAppData;

#define OFF 	0
#define ON  	1


#define APP_DATA_LENGTH	   	240
#define APP_PACKAGE_LENGTH	(APP_DATA_LENGTH+7)

#define ADS1298_DATA_LENGTH 27

//环形队列长度
#define EnqueueLen  2048*2
//每发送一次62字节
#define SendData_Length 27

EXTERN void delayUS(unsigned int x);
EXTERN __IO ADS1x9x_Status_Flags_type ADS1x9x_Status_Flags ;
EXTERN signed char ADS1x9x_Data [ADS1298_DATA_LENGTH];
EXTERN signed char buf[EnqueueLen];
EXTERN unsigned int buf_length;
EXTERN WORD GetSendPackageTimeout(void);
EXTERN void SetSendPackageTimeout(WORD SendPackageTimeout);

#endif

