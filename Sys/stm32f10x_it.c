/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "delay.h"
#include "USART.h"
#include "GLOBAL.h"
#include "printf.h"
#include "User_handle.h"
#include "ADS1299.h"
#include "QUEUE.h"

/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	//TimingDelay_Decrement();   //100us interrupt
}

void USART1_IRQHandler(void)
{
    static U8  ucIdx = 0xFF;
	static WORD ucLength = 0;
    U8 data = 0;

	while(USART_GetFlagStatus(USART1,USART_FLAG_RXNE))
	{
    	data = USART_ReceiveData(USART1);
		switch( data )
		{
			case 0xAA:
				ReceiveMBBuff[0] = 0xAA;
				ucIdx = 0;
			break;

			default:
				if(ReceiveMBBuff[0] != 0xAA)
				{
					ClearArray(ReceiveMBBuff, ((WORD)ReceiveMBBuff[1]<<8) | ReceiveMBBuff[2]);
					ucIdx = 0xFF;
					return;
				}
				ucIdx++;
				ReceiveMBBuff[ucIdx] =	data;
				
				ucLength = ((WORD)ReceiveMBBuff[1]<<8) | ReceiveMBBuff[2];

				if(ucIdx == ucLength + 3)
				{
					//if(ReceiveMBBuff[ucIdx] == CheckSum(ReceiveMBBuff, ucIdx))
					
					if(ReceiveMBBuff[ucIdx] == 0xFC)
					{							 
						//ReceiveMBBuff[ucIdx] = CheckSum(ReceiveMBBuff, ucLength+3);
						Puts("\r\n RCV OK");
						gucRCVFlg = SET;
					}
					else if(ReceiveMBBuff[ucIdx] ==  CheckSum(ReceiveMBBuff, ucLength))
					{
						gucRCVFlg = 2;
						//Puts("\r\n RCV OK2");
					}
					else
					{
						
						Puts("\r\n RCV ERROR");
						ClearArray(ReceiveMBBuff, ((WORD)ReceiveMBBuff[1]<<8) | ReceiveMBBuff[2]);
					}
					ucIdx = 0xFF;
				}
			break;
		}
				
		enQueue();
	}
        
}

void USART2_IRQHandler(void)
{
	//static U8  ucIdx = 0xFF, ucLength = 0;
   // U8 data = 0;
	
	while(USART_GetFlagStatus(USART2,USART_FLAG_RXNE))
    {
    	//data = USART_ReceiveData(USART2);
    	

    }
}

void TIM3_IRQHandler(void)  
{
	static U16 ucCount = 0;
	
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  
		ucCount++;

		if(ucCount%1 == 0)	{TimeSlice[0] = SET;}	//5ms

		if(ucCount%2 == 0) 	{TimeSlice[1] = SET;}	//10ms

		if(ucCount%20 == 0) {TimeSlice[2] = SET;}	//100ms

		if(ucCount%100 == 0)	{TimeSlice[3] = SET;}	//500ms

		if(ucCount%200 == 0){TimeSlice[4] = SET;ucCount = 0;}//1S
	}
}


void TIM4_IRQHandler(void)  
{

}

void TIM1_UP_IRQHandler(void)  
{
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update  );  
		//Puts(USART1, "\r\n TIM1_IRQHandler");
	}
}

void DMA1_Channel1_IRQHandler(void)
{
	#if 0
	U8 i = 0;
	if(DMA_GetITStatus(DMA1_IT_TC1) != RESET)
	{
	  	for(i = 0; i < 10; i++)
		{
			printf("\n\rThe ADC_Channel_14 Value:%d\n\r",ADCConvertedValue[i]);
		}
	  	DMA_ClearITPendingBit(DMA1_IT_TC1);
	}
	#endif
}

void EXTI9_5_IRQHandler(void)
{
	unsigned char i=0;
	unsigned char device_slot=0;
	signed char temp=0;
	
	if(EXTI_GetITStatus(EXTI_Line8) != RESET)
	{
		EXTI_ClearITPendingBit(EXTI_Line8);
		//Puts("\r\n EXTI8_IRQHandler");

		// Set the Chip ENABLE to start the SPI transaction

		//根据数据输出率为1000，则延时大约1ms
		delayUS(500);
		// Set the Chip ENABLE to start the SPI transaction
		Set_ADS1x9x_Chip_Enable (device_slot);
		delayUS(500);

//		temp = ADS1x9x_SPI_Burst (device_slot, SPI_TEST_DATA);
//
//		temp = ADS1x9x_SPI_Burst (device_slot, SPI_TEST_DATA);
//		temp = 0xc0;
//		ADS1x9x_Data [0] = temp;
//		Push_Enqueue(temp);

		for ( i = 0; i < ADS1298_DATA_LENGTH; i++)                      		
		{
//			ADS1x9x_Data [i] = ADS1x9x_SPI_Burst (device_slot, SPI_TEST_DATA); 
			temp = ADS1x9x_SPI_Burst (device_slot, SPI_TEST_DATA);
			ADS1x9x_Data [i] = temp;
			Push_Enqueue(temp);
		}

		Clear_ADS1x9x_Chip_Enable (device_slot); // Clear the Chip ENABLE 
		ADS1x9x_Status_Flags.ADC_Data_Ready = SET;
	}
}

#if 0
void EXTI9_5_IRQHandler(void)
{		
   unsigned char i=0;
   unsigned char device_slot=0;
   signed char temp=0;

   if(EXTI_GetITStatus(EXTI_Line5)==SET)
   {
	 	EXTI_ClearITPendingBit(EXTI_Line5);

		// Set the Chip ENABLE to start the SPI transaction

		//根据数据输出率为1000，则延时大约1ms
		delayUS(500);
		// Set the Chip ENABLE to start the SPI transaction
		Set_ADS1x9x_Chip_Enable (device_slot);
		delayUS(500);

//		temp = ADS1x9x_SPI_Burst (device_slot, SPI_TEST_DATA);
//
//		temp = ADS1x9x_SPI_Burst (device_slot, SPI_TEST_DATA);
//		temp = 0xc0;
//		ADS1x9x_Data [0] = temp;
//		Push_Enqueue(temp);

		for ( i = 0; i < ADS1298_DATA_LENGTH; i++)                      		
		{
//			ADS1x9x_Data [i] = ADS1x9x_SPI_Burst (device_slot, SPI_TEST_DATA); 
			temp = ADS1x9x_SPI_Burst (device_slot, SPI_TEST_DATA);
			ADS1x9x_Data [i] = temp;
			Push_Enqueue(temp);
		}

		Clear_ADS1x9x_Chip_Enable (device_slot); // Clear the Chip ENABLE 
		ADS1x9x_Status_Flags.ADC_Data_Ready = SET;
   }
}
#endif

/******************************************************************************/
/*            STM32F10x Peripherals Interrupt Handlers                        */
/******************************************************************************/
/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
