#define __ADC_C__


#include "ADC.h"
#include "printf.h"
#include "stm32f10x.h"
#include "SysTick.h"
#include "GLOBAL.h"



u16 Get_Adc(void)
{

	ADC_RegularChannelConfig(ADC1, ADC_Channel_14, 1, ADC_SampleTime_71Cycles5 );	    
  
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));

	return ADC_GetConversionValue(ADC1);
}


#if 0
void DMA_Config(DMA_Channel_TypeDef*DMA_CHx,u32 cpar,u32 cmar,u16 cndtr)
{
	DMA_InitTypeDef DMA_InitStructure;
	DMA_DeInit(DMA_CHx);
	
	DMA_InitStructure.DMA_PeripheralBaseAddr = cpar;					//Peripheral address:ADC_Channel_14_Addr
	DMA_InitStructure.DMA_MemoryBaseAddr = cmar;		//DMA Memory address
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;                          //As data sources.
	DMA_InitStructure.DMA_BufferSize = cndtr;                                       //Length
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;            //Peripheral address register.
	DMA_InitStructure.DMA_MemoryInc = DMA_PeripheralInc_Disable;                //Memory address register.
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; //Peripheral Data width is 16
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;         //Memory Data width is 16
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;                             //Circular buffer mode
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;                         //Set Priority
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;                                //Disable the memory to memory transfer
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);

	DMA_Cmd(DMA1_Channel1, ENABLE);
}
#endif

void GetDMA(void)
{
	U8 i = 0;
	
	for(i = 0; i < 10; i++)
	{
		printf("\n\rThe ADC_Channel_14 Value:%d\n\r",ADCConvertedValue[i]);
	}
	
	printf("\n\rThe Value of sample voltage is:%4.3f\n\r",(10000 * ADCConvertedValue[0]/4096 * 3.299) / 10000);
}
