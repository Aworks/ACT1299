#define __USER_HANDLE_C__


#include "User_handle.h"
#include "stm32f10x.h"
#include "delay.h"
#include "printf.h"
#include "global.h"
#include "user_coreconfig.h"
#include "ADS1299.h"
#include "queue.h"




void Turn_On_LED(U8 LED_NUM)
{	
	switch (LED_NUM)
	{
        case 0:
          GPIO_SetBits(GPIOC, GPIO_Pin_6);
          break;
        case 1:
          GPIO_SetBits(GPIOC, GPIO_Pin_7);
          break;
        case 2:
          GPIO_SetBits(GPIOC, GPIO_Pin_8);
          break;
        case 3:
          GPIO_SetBits(GPIOC, GPIO_Pin_9);
          break;          
        default:
		GPIO_SetBits(GPIOC, GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9); 
	}
	
}

U8 MD_AACB_KeyBoardScan( __IO uint16_t *AD, U8 *KeyState, BYTE *KeyPressTime, U8 *KeyScanState)
{
   static U8 KeyId = 0xFE;//, ucKeyLongFlg = 0;
    
    switch(*KeyState)
    {
        case KEY_STATE_IDLE:
            if(*AD <= KEY8_AD_MAX)
            {
            	//printf("\r\n *AD=%d",*AD);
                *KeyState    = KEY_STATE_DOWN;
            }
            KeyId            = 0xFE;
            *KeyPressTime    = 0;
        break;

        case KEY_STATE_DOWN:
        	
            if(*AD <= KEY8_AD_MAX)
            {
				//printf("\r\n 28*AD=%d",*AD);
				
                *KeyPressTime    = *KeyPressTime + 1;
                
                if(*KeyPressTime >= 1)
                {
                    *KeyState      = KEY_STATE_WAIT_UP;
                    *KeyScanState  = KEY_STATE_DOWN; 
                    //Puts("\r\n -----");
                    
					if(*AD >= KEY8_AD_MIN)
					{
						KeyId = 7;
					}
					else if(*AD >= KEY7_AD_MIN)
					{
						KeyId = 6;
					}
					else if(*AD >= KEY6_AD_MIN)
					{
						KeyId = 5;
					}
					else if(*AD >= KEY5_AD_MIN)
					{
						KeyId = 4;
					}
					else if(*AD >= KEY4_AD_MIN)
					{
						KeyId = 3;
					}
					else if(*AD >= KEY3_AD_MIN)
					{
						KeyId = 2;
					}
					else if(*AD >= KEY2_AD_MIN)
					{
						KeyId = 1;
					}
					else if(*AD >= KEY1_AD_MIN)
					{
						KeyId = 0;
					}
                    //SetKeyLongFlg(RESET);
                    //ucKeyLongFlg = 0;
                    //Puts("\r\n 80");
                }
            }
            else
            {
                *KeyState        = KEY_STATE_IDLE;
                *KeyScanState    = KEY_STATE_UP; 
            }
        break;
        case KEY_STATE_WAIT_UP:  
        
            if(*AD <= KEY8_AD_MAX)
            {
				//printf("\r\n 84*AD=%d",*AD);
                *KeyPressTime    = *KeyPressTime + 1;
				#if 0
                if(*KeyPressTime == 10)
                {
                	if(*AD >= KEY8_AD_MIN)
					{
						KeyId = 7;
					}
					else if(*AD >= KEY7_AD_MIN)
					{
						KeyId = 6;
					}
					else if(*AD >= KEY6_AD_MIN)
					{
						KeyId = 5;
					}
					else if(*AD >= KEY5_AD_MIN)
					{
						KeyId = 4;
					}
					else if(*AD >= KEY4_AD_MIN)
					{
						KeyId = 3;
					}
					else if(*AD >= KEY3_AD_MIN)
					{
						KeyId = 2;
					}
					else if(*AD >= KEY2_AD_MIN)
					{
						KeyId = 1;
					}
					else if(*AD >= KEY1_AD_MIN)
					{
						KeyId = 0;
					}
					*KeyState     = KEY_STATE_WAIT_UP;
                    *KeyPressTime = 11;
                    *KeyScanState = KEY_STATE_UP;
                    
                    //SetKeyLongFlg(RESET);
                    //Puts("\r\n 135");
					return KeyId;
                	#if 0
                    if((*AD < KEY2_AD_MAX) && (*AD > KEY2_AD_MIN))//按键1支持长按
                    {   
                        KeyId = 2; 
                        *KeyState     = KEY_STATE_WAIT_UP;
                        *KeyPressTime = 8;
                        *KeyScanState = KEY_STATE_UP;
                    }
                    #endif
                }
                else if(*KeyPressTime >= (100/10+11)) //Support Long Press
            	{
            		if(*AD >= KEY8_AD_MIN)
					{
						KeyId = 7;
					}
					else if(*AD >= KEY7_AD_MIN)
					{
						KeyId = 6;
					}
					else if(*AD >= KEY6_AD_MIN)
					{
						KeyId = 5;
					}
					else if(*AD >= KEY5_AD_MIN)
					{
						KeyId = 4;
					}
					else if(*AD >= KEY4_AD_MIN)
					{
						KeyId = 3;
					}
					else if(*AD >= KEY3_AD_MIN)
					{
						KeyId = 2;
					}
					else if(*AD >= KEY2_AD_MIN)
					{
						KeyId = 1;
					}
					else if(*AD >= KEY1_AD_MIN)
					{
						KeyId = 0;
					}
					
					*KeyState     = KEY_STATE_WAIT_UP;
                    *KeyPressTime = (100/10+9);
                    *KeyScanState = KEY_STATE_UP;
                    
                    //SetKeyLongFlg(SET);
                    
                    return KeyId;
            	}
                else
                {
                    *KeyState     = KEY_STATE_WAIT_UP;
                    *KeyScanState = KEY_STATE_DOWN;
                }    
                #endif
            }
            else
            {
                //Puts("\r\n 198");
                //printf("\r\n KeyId = %d",KeyId);
                *KeyState       = KEY_STATE_IDLE;
                *KeyScanState   = KEY_STATE_UP;
                return KeyId;
            }
        break;

        default:
            *KeyState       = KEY_STATE_IDLE;
            *KeyScanState   = KEY_STATE_UP;
        break;
        
    }
    return 0xFE;
}
U8 KeyScan(void)
{
	static BYTE ucAD1KeyId = 0xFE, ucAD1KeyScanState = KEY_STATE_IDLE, 
				cntAD1Scan = 0, flgAD1Scan = 0;
//	U8 i = 0;
	ucAD1KeyId = MD_AACB_KeyBoardScan(&ADCConvertedValue, &ucAD1KeyScanState, 
									  &cntAD1Scan, &flgAD1Scan);


	if(ucAD1KeyId != 0xFE)
	{
		if(flgAD1Scan == KEY_STATE_UP)
		{
		}
	}

	return ucAD1KeyId;
}


void ClearArray(U8 *ucClearArray ,WORD ucLength)
{
    WORD i;
    for( i = 0; i< ucLength + 4; i++ )
    {
        *ucClearArray++ = 0;
    }
}

U8 CheckSum(U8 *Str, WORD ucLength)
{
	WORD i = 0;
	U8 Sum = 0;
	//printf("\r\n ucLength %d",ucLength);
	
	for(i = 1; i < ucLength + 3; i++)
	{
		//printf("\r\n *(Str+%d) %x",i, *(Str+i));
		Sum += *(Str+i);
	}

	Sum = 0 - Sum;

	//printf("\r\n Sum %x",Sum);
	
	return Sum;
}

void SendMSG(U8 *Str, WORD ucLength)
{
	WORD i = 0;
	for(i = 0; i < ucLength + 4; i++)
	{
		USART_SendData(USART1,*(Str + i));
    	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET); 
	}
	
}
DWORD SubArray(WORD *ucClearArray , WORD ucLength)
{
    U8 i;
    DWORD ulData = 0;
    for( i = 0; i < ucLength; i++)
    {
        ulData += *(ucClearArray + i);
    }
		return ulData;
}

void SendMSGQueue(U8 Idx)
{
	
}



//sizeof
void InitPackageHeader(U8 *str)
{
	U8 i = 0;
	for(i = 0; i < 10; i++)
	{
		*(str + i) = Header[i];
	}
}
void SendPackageProcess(U8 *str, WORD Length)
{
	U8 ucLengthH = 0, ucLengthL = 0, ucBufSel = 0;
	WORD i = 0 ;
	
	ucLengthH = Length/APP_DATA_LENGTH;
	ucLengthL = Length%APP_DATA_LENGTH;

	
	printf("\r\n ucLength %d %d", ucLengthH, ucLengthL);

	if(ucLengthH != 0)//数据长度大于251 -7，分包发送
	{
		Puts("\r\n ucLengthH != 0");

		for(; ucLengthH > 0; ucLengthH--)
		{
			Puts("\r\n ucLengthH --");
			printf(" APP_DATA_LENGTH %d", APP_DATA_LENGTH);
			printf(" ucBufSel %d", ucBufSel);

			InitPackageHeader(&buffer[ucBufSel][0]);

			
			printf(" ucBufSel*APP_DATA_LENGTH %d", ucBufSel*APP_DATA_LENGTH);

			for(i = 0; i < APP_DATA_LENGTH; i++)
			{
				buffer[ucBufSel][i + 10] = *(str + i + ucBufSel*APP_DATA_LENGTH);
			}
			
			printf("\r\n ucLengthH %d", ucLengthH);
			if(ucBufSel == 0)
			{
				buffer[ucBufSel][5] = START_PACKEY;
			}
			else
			{
				buffer[ucBufSel][5] = CONTINUE_PACKEY;
			}
			
			Puts("\r\n H END");
			buffer[ucBufSel][6] = Length>>8;
			buffer[ucBufSel][7] = Length&0x00FF;
			buffer[ucBufSel][APP_PACKAGE_LENGTH + 3] = CheckSum(&buffer[ucBufSel][0], APP_DATA_LENGTH+7);
			ucBufSel++;
		}
		
		if(ucLengthL == 0)
		{
			Puts("\r\n 112----");
			ucBufSel--;
			printf("\r\n ucBufSel %d", ucBufSel);
			buffer[ucBufSel][5] = END_PACKEY;
			buffer[ucBufSel][APP_PACKAGE_LENGTH + 3] = CheckSum(&buffer[ucBufSel][0], APP_DATA_LENGTH+7);
			ucBufSel++;
		}
	}

	if(ucLengthL != 0)
	{
		Puts("\r\n ucLengthL != 0");
		
		InitPackageHeader(&buffer[ucBufSel][0]);
		
		for(i = 0; i < ucLengthL; i++)
		{
			buffer[ucBufSel][i + 10] = *(str + i + ucBufSel*APP_DATA_LENGTH);
		}
		buffer[ucBufSel][5] = END_PACKEY;
		buffer[ucBufSel][6] = Length>>8;
		buffer[ucBufSel][7] = Length|0x00FF;
		buffer[ucBufSel][9] = ucLengthL;
		buffer[ucBufSel][ucLengthL + 3 + 7] = CheckSum(&buffer[ucBufSel][0], ucLengthL+7);
		Puts("\r\n L END");
		ucBufSel++;
	}
	
	//ucBufSel = 0;
	
	#if 0
	Puts("\r\n buffer0 \r\n");
	for(i = 0; i < 255; i++)
	{
		printf(" %x", buffer[0][i]);
	}
	SendMSG(&buffer[0][0], buffer[0][2]);
	Delay_1ms(500);
	Puts("\r\n buffer1 \r\n");
	for(i = 0; i < 255; i++)
	{
		printf(" %x", buffer[1][i]);
	}
	SendMSG(&buffer[1][0], buffer[1][2]);
	Delay_1ms(500);
	Puts("\r\n buffer2 \r\n");
	for(i = 0; i < 255; i++)
	{
		printf(" %x", buffer[2][i]);
	}
	SendMSG(&buffer[2][0], buffer[2][2]);

	Delay_1ms(500);
	Puts("\r\n buffer3 \r\n");
	for(i = 0; i < 255; i++)
	{
		printf(" %x", buffer[3][i]);
	}
	SendMSG(&buffer[3][0], buffer[3][2]);
	
	Delay_1ms(500);
	Puts("\r\n buffer4 \r\n");
	for(i = 0; i < 255; i++)
	{
		printf(" %x", buffer[4][i]);
	}
	SendMSG(&buffer[4][0], buffer[4][2]);
	Delay_1ms(5000);
	#else

	SysSendAppData.PacketCount = ucBufSel;
	SysSendAppData.SendFlag    = ON;
	SetSendAppDataFlg(CMD_ACK_PARAM_DESC_TRUE);
	#endif
	
}
void SendPackage(void)
{
	static U8 i = 0;
	if(SysSendAppData.SendFlag == ON)
	{
		//printf("\r\n SysSendAppData.PacketCount %d",SysSendAppData.PacketCount);
		printf("\r\n SysSendAppData.SendFlag %d",SysSendAppData.SendFlag);
		if(GetSendAppDataFlg() != CMD_ACK_PARAM_DESC_TRUE)
		{
			return;
		}
		SetSendPackageTimeout(0);
		
		SetSendAppDataFlg(CMD_ACK_PARAM_DESC_RFD);
		
		if(SysSendAppData.PacketCount != 0)
		{
			printf("\r\n PacketCount %d %d",SysSendAppData.PacketCount, i);
			SendMSG(&buffer[i][0], buffer[i][2]);
			SysSendAppData.PacketCount--;
			i++;
			SetSendPackageTimeout(500);
			//Delay_1ms(2);
		}
		else
		{
			//i = 0;
			SysSendAppData.SendFlag = OFF;
		}
	}
	else
	{
		i = 0;
	}
}

void SendMSGHandle(U8 Idx)
{
	WORD i = 0;
	WORD usLength = 0;
	U8 ucLengthH = 0, ucLengthL = 0;
	U8 *str;

	switch(Idx)
	{
		case SEND_MSG_CHANGENAME:
			Puts("\r\n SEND_MSG_CHANGENAME");
			str = ChangeName;
		break;
		case SEND_MSG_MUSIC_PLAY:
			Puts("\r\n SEND_MSG_MUSIC_PLAY");
			str = MusicPlay;
		break;
		case SEND_MSG_MUSIC_PAUSE:
			Puts("\r\n SEND_MSG_MUSIC_PAUSE");
			str = MusicPause;
		break;
		case SEND_MSG_MUSIC_PLAY_PAUSE:
			Puts("\r\n SEND_MSG_MUSIC_PLAY_PAUSE");
			str = MusicPlayPause;
		break;
		case SEND_MSG_MUSIC_STOP:
			Puts("\r\n SEND_MSG_MUSIC_STOP");
			str = MusicStop;
		break;
		case SEND_MSG_POWEROFF:
			Puts("\r\n SEND_MSG_POWEROFF");
			str = PowerOFF;
		break;
		case 7:
			Puts("\r\n SEND_MSG_DATA");
			
			InitPackageHeader(Data);
			
			for(i = 10; i < 265; i++)
			{
				Data[i] = i - 10;
				printf("\r\n Data %d",Data[i]);
			}
			for(i = 0; i < 265; i++)
			{
				printf("\r\n Data %d",Data[i]);
			}
			str = Data;
			//Data[0x109] = 
			//str = PowerOFF;
		break;
		
		default:
		
		break;
	}
	
	
	ucLengthH = *(str+1);
	ucLengthL = *(str+2);
	usLength  = ((WORD)ucLengthH<<8) | ucLengthL;

	*(str + usLength + 3) = CheckSum(str, usLength);
	printf("\r\n usLength %d", usLength+4);
	for(i = 0; i < usLength + 4; i++)
	{
		printf(" %x",*(str + i));
	}

	SendMSG(str, usLength);
	Delay_1ms(5);
}

void enQueue(void)
{
	U8 i = 0;
	WORD  usLength = 0;
	
	if(gucRCVFlg != RESET)
	{
		gucRCVFlg = RESET;
				
		if(ReceiveMBBuff[0] != 0xAA)
		{
			
			ClearArray(ReceiveMBBuff, ((WORD)ReceiveMBBuff[1]<<8) | ReceiveMBBuff[2]);
			return;
		}

		usLength = ((WORD)ReceiveMBBuff[1]<<8) | ReceiveMBBuff[2];
		
		if((gucRcvQueueLocate & QUEUE_ELEM_0) != QUEUE_ELEM_0)
		{
			//Puts("\r\n QUEUE_ELEM_0");
			gucRcvQueueLocate |= QUEUE_ELEM_0;
			for(i = 0; i < usLength + 4; i++)
			{
				RecCMDQueue[0][i] = ReceiveMBBuff[i];
			}
		}
		else if((gucRcvQueueLocate & QUEUE_ELEM_1) != QUEUE_ELEM_1)
		{
			//Puts("\r\n QUEUE_ELEM_1");
			gucRcvQueueLocate |= QUEUE_ELEM_1;
			for(i = 0; i < usLength + 4; i++)
			{
				RecCMDQueue[1][i] = ReceiveMBBuff[i];
			}
		}
		else if((gucRcvQueueLocate & QUEUE_ELEM_2) != QUEUE_ELEM_2)
		{
			//Puts("\r\n QUEUE_ELEM_2");
			gucRcvQueueLocate |= QUEUE_ELEM_2;
			for(i = 0; i < usLength + 4; i++)
			{
				RecCMDQueue[2][i] = ReceiveMBBuff[i];
			}
		}
		else if((gucRcvQueueLocate & QUEUE_ELEM_3) != QUEUE_ELEM_3)
		{
			//Puts("\r\n QUEUE_ELEM_3");
			gucRcvQueueLocate |= QUEUE_ELEM_3;
			for(i = 0; i < usLength + 4; i++)
			{
				RecCMDQueue[3][i] = ReceiveMBBuff[i];
			}
		}
		else if((gucRcvQueueLocate & QUEUE_ELEM_4) != QUEUE_ELEM_4)
		{
			//Puts("\r\n QUEUE_ELEM_4");
			gucRcvQueueLocate |= QUEUE_ELEM_4;
			for(i = 0; i < usLength + 4; i++)
			{
				RecCMDQueue[4][i] = ReceiveMBBuff[i];
			}
		}

		ClearArray(ReceiveMBBuff, usLength);
	}
}

U8 *OutQueue(void)
{
	U8 *str;
	U8 ucLengthH = 0, ucLengthL = 0, i = 0;
	WORD  ucLength = 0;
	
	if(gucRcvQueueLocate != 0)
	{
		//Puts("\r\n OutQueue");
		
		if((gucRcvQueueLocate & QUEUE_ELEM_0) == QUEUE_ELEM_0)
		{
			gucRcvQueueLocate &= ~QUEUE_ELEM_0;
			Puts("\r\n OutQueue0");
			str = &RecCMDQueue[0][0];
		}
		else if((gucRcvQueueLocate & QUEUE_ELEM_1) == QUEUE_ELEM_1)
		{
			gucRcvQueueLocate &= ~QUEUE_ELEM_1;
			Puts("\r\n OutQueue1");
			str = &RecCMDQueue[1][0];
		}
		else if((gucRcvQueueLocate & QUEUE_ELEM_2) == QUEUE_ELEM_2)
		{
			gucRcvQueueLocate &= ~QUEUE_ELEM_2;
			Puts("\r\n OutQueue2");
			str = &RecCMDQueue[2][0];
		}
		else if((gucRcvQueueLocate & QUEUE_ELEM_3) == QUEUE_ELEM_3)
		{
			gucRcvQueueLocate &= ~QUEUE_ELEM_3;
			Puts("\r\n OutQueue3");
			str = &RecCMDQueue[3][0];
		}
		else if((gucRcvQueueLocate & QUEUE_ELEM_4) == QUEUE_ELEM_4)
		{
			gucRcvQueueLocate &= ~QUEUE_ELEM_4;
			Puts("\r\n OutQueue4");
			str = &RecCMDQueue[4][0];
		}

		ucLengthH = *(str+1);
		ucLengthL = *(str+2);
		ucLength = ((WORD)ucLengthH<<8) | ucLengthL;
		//printf("\r\n ucLength %x",ucLength);

		for(i = 0; i < ucLength + 4; i++)
		{
			//printf(" %x",*(str + i));
		}
		
		return str;
	}

	*str = 0;
	
	return str;
}


void BTMCMDHandler(void)
{
	U8 i = 0;
	U8 ucLengthH = 0, ucLengthL = 0, ucCMD = 0;//, ucData1;
	WORD  ucLength = 0;
	U8 *str;

	str = OutQueue();

	if(*str != 0xAA)
	{
		//Puts("\r\n *************");
		//printf("\r\n *str %x",*str);
		//ClearArray(ReceiveMBBuff, ((WORD)ReceiveMBBuff[1]<<8) | ReceiveMBBuff[2]);
		return;
	}
	
	ucLengthH 	= *(str + MSG_LENGTH_H);
	ucLengthL 	= *(str + MSG_LENGTH_L);
	ucLength 	= ((WORD)ucLengthH<<8) | ucLengthL;
	//printf("\r\n ucLength %x",ucLength);
	ucCMD		= *(str + MSG_CMD);
	
	for(i = 0; i < ucLength+4; i++)
	{
		printf(" %x",*(str + i));
	}

	switch(ucCMD)
	{
		case BTM_MSG_BTM_STATUS:
			Btm_stateMsgProcess(*(str + MSG_DA1), *(str + MSG_DA2));
		break;
		
		case BTM_MSG_BATTERY_STATUS:
		
		break;
		case BTM_MSG_CMD_ACK:
			switch(*(str + MSG_DA1))
			{
				case MCU_TO_BTM_CMD_SEND_APP_DATA:
					Puts("\r\n CMD_ACK");
					SetSendAppDataFlg(*(str + MSG_DA2));
				break;
				default:
				break;
			}
		break;
		default:
		break;
	}
	
	if(0)
	{
		if(*(str + ucLength+3) == 0xFC)
		{
			*(str + ucLength+3) = CheckSum(ReceiveMBBuff, ucLength);

			SendMSG(ReceiveMBBuff, ucLength);			
		}
	}
}

void Btm_stateMsgProcess(U8 state, U8 ucDat)
{
	BTM_STATUS ucBtm_state;
	
	ucBtm_state = GetBtm_state();
	
	switch(state)
	{
		case 0x00:	ucBtm_state.Power 			= RESET;	break;
		case 0x01:	ucBtm_state.Pairing 		= SET;		break;
		case 0x02:	ucBtm_state.Power 			= SET;		break;
		case 0x03:	ucBtm_state.PairingState 	= SET;		break;
		case 0x04:	ucBtm_state.PairingState 	= RESET;	break;
		case 0x05:	ucBtm_state.HFLink 			= SET;		break;
		case 0x06:	ucBtm_state.A2DpLink 		= SET;		break;
		case 0x07:	ucBtm_state.HFLink 			= RESET;	break;
		case 0x08:	ucBtm_state.A2DpLink 		= RESET;	break;
		case 0x09:	ucBtm_state.SCOLink			= SET;		break;
		case 0x0A:	ucBtm_state.SCOLink			= RESET;	break;
		case 0x0B:	ucBtm_state.AVRCPLink		= SET;		break;
		case 0x0C:	ucBtm_state.AVRCPLink		= RESET;	break;
		case 0x0D:	ucBtm_state.SPPLink			= SET;		break;
		case 0x0E:	ucBtm_state.SPPLink			= RESET;	break;
		case 0x0F:	ucBtm_state.StandbyState	= SET;		break;
		case 0x10:	ucBtm_state.IAPState		= SET;		break;
		case 0x11:	ucBtm_state.ACLState		= SET;		break;
		default:
		break;
		
	}
	
	ucBtm_state.Description = ucDat;
	
	SetBtm_state(ucBtm_state);
}

void MusicProcess(U8 ucState)
{
	BTM_STATUS ucBtm_state;

	ucBtm_state = GetBtm_state();
	
	if(ucBtm_state.A2DpLink != SET) return;
	
	switch(ucState)
	{
		case SEND_MSG_MUSIC_PLAY:
			SendMSGHandle(SEND_MSG_MUSIC_PLAY);	
		break;
		case SEND_MSG_MUSIC_PAUSE:
			SendMSGHandle(SEND_MSG_MUSIC_PAUSE);
		break;
		case SEND_MSG_MUSIC_PLAY_PAUSE:
			SendMSGHandle(SEND_MSG_MUSIC_PLAY_PAUSE);
		break;
		case SEND_MSG_MUSIC_STOP:
			SendMSGHandle(SEND_MSG_MUSIC_STOP);	
		break;
	}
}

void KeyProcess(U8 KeyValue)
{
	WORD i = 0;
	U8 ADS1x9x_DEVICE_SLOT = 0;
	if(KeyValue != 0xFE) 
	printf("\r\n KeyValue %d",KeyValue);
	
	switch(KeyValue)
	{
		case 0:	MusicProcess(SEND_MSG_MUSIC_PLAY);			break;
		case 1:	MusicProcess(SEND_MSG_MUSIC_PAUSE);			break;
		case 2:	MusicProcess(SEND_MSG_MUSIC_PLAY_PAUSE);	break;
		case 3:	
			Puts("\r\n DISABLE ADS1299");
			//MusicProcess(SEND_MSG_MUSIC_STOP);			
			disable_ADS1x9x_Interrupt (ADS1x9x_DEVICE_SLOT);   //禁止DRDY产生中断
			Soft_Stop_ADS1x9x (ADS1x9x_DEVICE_SLOT);           //停止AD转换
			Stop_Read_Data_Continuous (ADS1x9x_DEVICE_SLOT);   //停止连续转换
			ADS1x9x_Status_Flags.ADC_Data_Ready = RESET;
	        
		break;
		case 4:	SendMSGHandle(SEND_MSG_POWEROFF);			break;
		case 5:	Bluetooth_PowerON();						break;
		//case 6:	BTMCMDHandler();							break;
		//case 7:	SendMSGHandle(SEND_MSG_MUSIC_PLAY);			break;
		case 6: 
		
			for(i = 0; i < 1000; i++)
			{
				Data[i] = i;

				if(i%APP_DATA_LENGTH == 0)
				{
					printf("\r\n ");
				}
				printf("\r\n Data %x", Data[i]);
				
			}
			SendPackageProcess(Data, 1000);						break;

		case 7:
			Puts("\r\n ENABLE ADS1299");
			Power_Up_ADS1x9x (ADS1x9x_DEVICE_SLOT);                 // Power up Digital portion of the ADS1x9x                                              
			POR_Reset_ADS1x9x (ADS1x9x_DEVICE_SLOT);

			//ADS1298软复位
			Soft_Reset_ADS1x9x(ADS1x9x_DEVICE_SLOT);

			//停止连续读数
			Stop_Read_Data_Continuous (ADS1x9x_DEVICE_SLOT);
			
			//从AT24C01空间读取配置参数
			//AT24CXX_Read(Parmnent_Addr,	buf,Parmnent_Length);
  			//Initialize_ADS1x9x_Registers (ADS1x9x_DEVICE_SLOT, buf);
			//Initialize_ADS1x9x_Registers(ADS1x9x_DEVICE_SLOT, ADS1x9x_Default_Register_Settings);
			
			enable_ADS1x9x_Conversion (ADS1x9x_DEVICE_SLOT);   //开始采样
		break;
		default:
		break;
	}
}


void Lead_off(unsigned char *dat)
{

	if(((dat[0]&0x0f)!=0x00)||((dat[1])!=0x00)||((dat[2]&0xf0)!=0x00))
	{
	   //两次不相等，则判为非相同的导联脱落
//	  if((dat[1]!=RLD_LOFF_Register[0])||(dat[2]!=RLD_LOFF_Register[1])||(dat[3]!=RLD_LOFF_Register[2]))
//	  {
//	    RLD_LOFF_Register[0] = dat[1];
//		RLD_LOFF_Register[1] = dat[2];
//		RLD_LOFF_Register[2] = dat[3];
//
//		temp[0] = ~((dat[1]&0x0f)<<4)+(dat[2]>>4);
//		temp[1] = ~(((dat[2]&0x0f)<<4)+((dat[3]&0xf0)>>4));
//	    Write_RLD_SENS_Regsiter(temp) ;
//		RLD_LOFF_Bit =1 ;
//	  }
	}
	else
	{
		Puts("\r\n Lead_off");
	}
}


void ADS1299Process(void)
{
	WORD i = 0;
	if (ADS1x9x_Status_Flags.ADC_Data_Ready == SET)
	{ 
		
		// Process the data...
		ADS1x9x_Status_Flags.ADC_Data_Ready = RESET;		
	//	AD_DATA_To_Usb(&ADS1x9x_Data[3],sizeof(ADS1x9x_Data)-3,AD_StatusData);
		//AD_DATA_To_Usb(ADS1x9x_Data,sizeof(ADS1x9x_Data),AD_StatusData);

		if(Enqueue_Bit>0)
		{
			buf_length = (tail+EnqueueLen-head)/SendData_Length;
		}
		else
		{
			buf_length = (tail-head)/SendData_Length;
		}


		 while(buf_length--)
		 {
		   	for(i=0;i<SendData_Length;i++)
		   	{
			 	buf[i] = PopDequeue();
			 	
				printf("\r\n buf[%d] %x", i, buf[i]);
		   	}
			//AD_DATA_To_Usb(buf,SendData_Length,AD_StatusData);
		 }
		 //判断导联是否脱落，脱落报警
 		 //Lead_off(ADS1x9x_Data);
 		 printf("\r\n ADS1x9x_Data0 %x", ADS1x9x_Data[0]);
 		 printf("\r\n ADS1x9x_Data1 %x", ADS1x9x_Data[1]);
 		 printf("\r\n ADS1x9x_Data2 %x", ADS1x9x_Data[2]);
 		 
	}
}

