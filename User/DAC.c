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
        DAC_StructInit(&DAC_InitStruct);//��DAC_Struct��ֵ��ΪĬ��
        DAC_InitStruct.DAC_Trigger=DAC_Trigger_Software;//���������
        DAC_InitStruct.DAC_WaveGeneration=DAC_WaveGeneration_None;//�رղ�������
        DAC_InitStruct.DAC_LFSRUnmask_TriangleAmplitude=DAC_TriangleAmplitude_4095;
        DAC_InitStruct.DAC_OutputBuffer=DAC_OutputBuffer_Enable;//ʹ��DACͨ������   
        DAC_Init(DAC_Channel_1,&DAC_InitStruct);
    /* Enable DAC Channel1 */
        DAC_Cmd(DAC_Channel_1, ENABLE);
        DAC_SetChannel1Data(DAC_Align_12b_R,0xF00);//12λ�Ҷ���,
        DAC_DualSoftwareTriggerCmd(ENABLE);//ʹ���������,����DAC��ֵ

    #endif

	RCC->APB2ENR|=1<<2;    //ʹ��PORTAʱ��           
	RCC->APB1ENR|=1<<29;   //ʹ��DACʱ��         
	GPIOA->CRL&=0XFFF0FFFF;
	GPIOA->CRL|=0X00000000;//PA4 ģ������      
	DAC->CR|=1<<0;  //ʹ��DAC1
	DAC->CR|=1<<1;  //DAC1������治ʹ�� BOFF1=1
	DAC->CR|=0<<2;  //��ʹ�ô������� TEN1=0
	DAC->CR|=0<<3;  //DAC TIM6 TRGO,����ҪTEN1=1����
	DAC->CR|=0<<6;  //��ʹ�ò��η���
	DAC->CR|=0<<8;  //���Ρ���ֵ����
	DAC->CR|=0<<12;       //DAC1 DMA��ʹ��   
	DAC->DHR12R1=0;
}

//����ͨ��1�����ѹ
//vol:0~3300,����0~3.3V
void Dac1_Set_Vol(u16 vol)
{
       float temp=vol;
       temp/=1000;
       temp=temp*4096/3.3;
       DAC->DHR12R1=temp;
}

