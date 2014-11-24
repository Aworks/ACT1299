
#include "stm32f10x.h"
#include "global.h"
#include "delay.h"
#include "printf.h"
#include "user_coreconfig.h"
#include "User_handle.h"
#include "ADS1299.h"
#include "QUEUE.h"


void InitSystem(void)
{
	RCC_Config();
	NVIC_Config();
	NVIC_SetPriorityGrouping(NVIC_PriorityGroup_2);
	USART1_Config(115200);
	USART2_Config(115200);
	printf("\r\n USART2_Config");
	Puts("\r\n USART2_Config");
	Delay_init(72);
	LED_GPIO_Config();
	Timerx_Init(50,7200);//10K   0.1ms   5ms
	//Timer1_Init(100,7200);//10K   0.1ms   10ms
	ADC_Config();
	Bluetooth_Ctrl_Config();
	Bluetooth_RST();
	Bluetooth_PowerON();

	ADS1298_GPIO_init();
	SPIx_Init();
	init_ADS1x9x_Data_Ready_Interrupt();
}

void InitGlobal(void)
{
	
}

void Task_RealTime(void)
{
	BTMCMDHandler();
	SendPackage();
}

void Task_5ms(void)
{
	ADS1299Process();
}

void Task_10ms(void)
{
	U8 ucKeyValue = 0xFE;
	WORD SendPackageTimeout = 0;
	ucKeyValue = KeyScan();
	KeyProcess(ucKeyValue);

	SendPackageTimeout = GetSendPackageTimeout();
	if(SendPackageTimeout != 0)
	{
		SendPackageTimeout--;
		SetSendPackageTimeout(SendPackageTimeout);
		if(SendPackageTimeout == 0)
		{
			/*MCU send data to the BTM, BTM no response timeout*/
			Puts("\r\n BTM no response timeout");
			SysSendAppData.SendFlag = OFF;
		}
	}
}

void Task_100ms(void)
{	
	//Puts("\r\n Task_100ms");

	U8 ucCount = 0;
	ucCount = GetChangeNameTimeout();
	if(ucCount != 0)
	{
		ucCount--;
		SetChangeNameTimeout(ucCount);
		if(ucCount == 0)
		{
			SendMSGHandle(SEND_MSG_CHANGENAME);
		}
	}
	
}
void Task_500ms(void)
{
	//Puts("\r\n Task_500ms");
	//printf("\r\n ADCConvertedValue %d", ADCConvertedValue);
}

void Task_1s(void)
{
	static U8 ucCount;
	
	if(GetBtm_state().A2DpLink == SET)
	{
		if(ucCount == 0)
		{
			ucCount = 1;
			GPIO_SetBits(LEDPOTR, A2DPLINK_PIN);
		}
		else
		{
			ucCount = 0;
			GPIO_ResetBits(LEDPOTR, A2DPLINK_PIN);
		}
	}
	else
	{
		GPIO_ResetBits(LEDPOTR, A2DPLINK_PIN);
	}

	if(GetBtm_state().HFLink == SET)
	{
		if(ucCount == 1)
		{
			GPIO_SetBits(LEDPOTR, HFLINK_PIN);
		}
		else
		{
			GPIO_ResetBits(LEDPOTR, HFLINK_PIN);
		}
	}
	else
	{
		GPIO_ResetBits(LEDPOTR, HFLINK_PIN);
	}

	if(GetBtm_state().SPPLink == SET)
	{
		if(ucCount == 1)
		{
			GPIO_SetBits(LEDPOTR, SPPLINK_PIN);
		}
		else
		{
			GPIO_ResetBits(LEDPOTR, SPPLINK_PIN);
		}
	}
	else
	{
		GPIO_ResetBits(LEDPOTR, SPPLINK_PIN);
	}
	
	
}


int main(void)
{
	U8 ADS1x9x_DEVICE_SLOT = 0;
	InitSystem();
	InitGlobal();
	Puts("\r\n System Init End");
	
	Puts("\r\n ADS1x9x_DEVICE_SLOT");

	ADS1x9x_DEVICE_SLOT = init_ADS1x9x (ADS1x9x_DEVICE_SLOT);
	

	
	printf("\r\n init_ADS1x9x %d", ADS1x9x_DEVICE_SLOT);

	//Initialize_ADS1x9x_Registers(ADS1x9x_DEVICE_SLOT, ADS1x9x_Default_Register_Settings);
	while (1)
	{
		Task_RealTime();
		//if(GetTask5msFlg() == SET) {Task_5ms();		}
  		if(GetSysClkFlg(0) == SET) {Task_5ms();		}
		if(GetSysClkFlg(1) == SET) {Task_10ms();	}
		if(GetSysClkFlg(2) == SET) {Task_100ms();	}
		if(GetSysClkFlg(3) == SET) {Task_500ms();	}
		if(GetSysClkFlg(4) == SET) {Task_1s();		}
    }

}



