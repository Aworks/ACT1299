#define __GLOBAL_C__


#include "GLOBAL.h"
#include "stm32f10x.h"
#include "ADS1299.h"
#include "delay.h"
__IO uint16_t ADCConvertedValue;

#if 0
U8 gucTask5msFlg = RESET;

U8 GetTask5msFlg(void)
{
	if(gucTask5msFlg == SET)
	{
		gucTask5msFlg = RESET;
		return SET;
	}
	return RESET;
}

void SetTask5msFlg(U8 ucTmp)
{
	gucTask5msFlg = ucTmp;
}
#endif

U8 TimeSlice[5] = {0, 0, 0, 0, 0};

FlagStatus GetSysClkFlg(U8 ucTmp)
{
	if(TimeSlice[ucTmp] == SET)
	{
		TimeSlice[ucTmp] = RESET;
		return SET;
	}
	
	return RESET;
}

U8 ChangeName[37] 		= {0xAA, 0x00, 0x21, 0x05,'A','c','t','r','o','n','t','e','k', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x2F};
U8 PowerOFF[7]	  		= {0xAA, 0x00, 0x03, 0x02, 0x00, 0x5E, 0x9D};
U8 MusicPlay[7]	  		= {0xAA, 0x00, 0x03, 0x04, 0x00, 0x05, 0xF4};
U8 MusicPause[7]		= {0xAA, 0x00, 0x03, 0x04, 0x00, 0x06, 0xF3};
U8 MusicPlayPause[7]	= {0xAA, 0x00, 0x03, 0x04, 0x00, 0x07, 0xF2};
U8 MusicStop[7]	  		= {0xAA, 0x00, 0x03, 0x04, 0x00, 0x08, 0xF1};

BTM_STATUS Btm_state = {RESET,RESET,RESET,RESET,
						RESET,RESET,RESET,RESET,
						RESET,RESET,RESET,0};

BTM_STATUS GetBtm_state(void)
{
	return Btm_state;
}

void SetBtm_state(BTM_STATUS ucBtm_state)
{
	Btm_state = ucBtm_state;
}

U8 gucChangeNameTimeout = 0;

U8 GetChangeNameTimeout(void)
{
	return gucChangeNameTimeout;
}

void SetChangeNameTimeout(U8 ucTmp)
{
	gucChangeNameTimeout = ucTmp;
}

U8 gucSendAppDataFlg = 0;

U8 GetSendAppDataFlg(void)
{
	return gucSendAppDataFlg;
}

void SetSendAppDataFlg(U8 ucTmp)
{
	gucSendAppDataFlg = ucTmp;
}


SEND_APP_DATA_FLAG SysSendAppData = {OFF, 0};




U8 Header[10] = {0xAA, 0x00, APP_PACKAGE_LENGTH, 0x12, 0x00, 0x00, 0x00, APP_DATA_LENGTH, 0x00, APP_DATA_LENGTH};
U8 buffer[5][256];
U8 gucRcvQueueLocate = 0;
U8 RecCMDQueue[5][100];
U8 Data[1000] = {0xAA, 0x00, APP_PACKAGE_LENGTH, 0x12, 0x00, 0x00, 0x00, APP_DATA_LENGTH, 0x00, APP_DATA_LENGTH, };
//AA 00 0A 12 00 00 00 03 00 03 31 32 33 48
U8 gucRCVFlg = 0;
U8 ReceiveMBBuff[100] ={0, 0, 0, 0, 0, 0, 0};


void delayUS(unsigned int x)
{ 

	 volatile unsigned int _dcnt;
	 _dcnt=(x*4);
	 while(_dcnt-- > 0)
	 { continue; }
}

__IO ADS1x9x_Status_Flags_type ADS1x9x_Status_Flags ;
signed char ADS1x9x_Data [ADS1298_DATA_LENGTH];


signed char buf[EnqueueLen];
unsigned int buf_length=0;


WORD gucSendPackageTimeout = 0;

WORD GetSendPackageTimeout(void)
{
	return gucSendPackageTimeout;
}

void SetSendPackageTimeout(WORD SendPackageTimeout)
{
	gucSendPackageTimeout = SendPackageTimeout;
}

