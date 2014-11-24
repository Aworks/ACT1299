#define __DAC_C__


#include "DAC.h"
#include "SysTick.h"

void DAC_GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void DAC_Configuration(void)
{
  DAC_InitTypeDef DAC_InitStructure;
  
  DAC_DeInit();
  
  DAC_InitStructure.DAC_Trigger = DAC_Trigger_None;
  DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;
  DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0;
  DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Enable;

  DAC_Init(DAC_Channel_1, &DAC_InitStructure);

  DAC_Cmd(DAC_Channel_1, ENABLE);
  
  DAC_SetChannel1Data(DAC_Align_12b_R,0x7FF);

  DAC_SoftwareTriggerCmd(DAC_Channel_1,ENABLE);

}

void DAC_Config(void)
{
	#if 0
	 DAC_InitTypeDef DAC_InitStruct;

        GPIO_InitTypeDef GPIO_InitStructure;
        
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
        
		Delay_1ms(100);
        /* Configure DAC channe1 outputs pins */
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;    
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
        GPIO_Init(GPIOA, &GPIO_InitStructure);

        DAC_DeInit();

        DAC_Cmd(DAC_Channel_1,ENABLE); //
    //DAC_Cmd(DAC_Channel_2, ENABLE);
        DAC_StructInit(&DAC_InitStruct);//将DAC_Struct的值设为默认
        DAC_InitStruct.DAC_Trigger=DAC_Trigger_Software;//由软件触发
        DAC_InitStruct.DAC_WaveGeneration=DAC_WaveGeneration_None;//关闭波形生成
        DAC_InitStruct.DAC_LFSRUnmask_TriangleAmplitude=DAC_TriangleAmplitude_4095;
        DAC_InitStruct.DAC_OutputBuffer=DAC_OutputBuffer_Enable;//使能DAC通道缓存   
        DAC_Init(DAC_Channel_1,&DAC_InitStruct);
    /* Enable DAC Channel1 */
        DAC_Cmd(DAC_Channel_1, ENABLE);
        DAC_SetChannel1Data(DAC_Align_12b_R,0xF00);//12位右对齐,
        DAC_DualSoftwareTriggerCmd(ENABLE);//使能软件触发,更新DAC的值

    #endif

	RCC->APB2ENR|=1<<2;    //使能PORTA时钟           
	RCC->APB1ENR|=1<<29;   //使能DAC时钟         
	GPIOA->CRL&=0XFFF0FFFF;
	GPIOA->CRL|=0X00000000;//PA4 模拟输入      
	DAC->CR|=1<<0;  //使能DAC1
	DAC->CR|=1<<1;  //DAC1输出缓存不使能 BOFF1=1
	DAC->CR|=0<<2;  //不使用触发功能 TEN1=0
	DAC->CR|=0<<3;  //DAC TIM6 TRGO,不过要TEN1=1才行
	DAC->CR|=0<<6;  //不使用波形发生
	DAC->CR|=0<<8;  //屏蔽、幅值设置
	DAC->CR|=0<<12;       //DAC1 DMA不使能   
	DAC->DHR12R1=0;
}

//设置通道1输出电压
//vol:0~3300,代表0~3.3V
void Dac1_Set_Vol(u16 vol)
{
       float temp=vol;
       temp/=1000;
       temp=temp*4096/3.3;
       DAC->DHR12R1=temp;
}

