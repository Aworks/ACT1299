#define __USER_CORECONFIG_C__


#include "user_coreconfig.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_flash.h"
#include "Global.h"
#include "printf.h"
#include "delay.h"
#include "spi.h"
//#include "stm32f10x_spi.h"


void RCC_Config(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , 	ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , 	ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, 	ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, 	ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, 	ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, 	ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO  , 	ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, 	ENABLE); 
  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, 	ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, 	ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, 	ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,	 	ENABLE);	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, 		ENABLE);
	//RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, 		ENABLE);

	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1 , ENABLE);

}

void NVIC_Config(void)
{
#ifdef  VECT_TAB_RAM
    NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0);
#else
    NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);  
#endif
}


void USART1_GPIO_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);  
}


void USART1_Config(u32 bound)
{
  USART_InitTypeDef USART_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

  USART1_GPIO_Config();
  		  
  USART_InitStructure.USART_BaudRate = bound;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(USART1, &USART_InitStructure);  

  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

  USART_Cmd(USART1, ENABLE);
  
}


void USART2_GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  // Configure USART1_Tx as push-pull 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  // Configure USART1_Rx as input floating 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);  
}

void USART2_Config(u32 bound)
{
  USART_InitTypeDef USART_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  
  USART2_GPIO_Configuration();

   /* Configure the USART2*/ 
  USART_InitStructure.USART_BaudRate = bound;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  USART_Init(USART2, &USART_InitStructure);
  
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
   //USART_ITConfig(USART2, USART_IT_TXE, ENABLE);
   
  USART_Cmd(USART2, ENABLE);
}



void Timerx_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_ITConfig( TIM3, TIM_IT_Update | TIM_IT_Trigger, ENABLE);
	
	TIM_TimeBaseStructure.TIM_Period = arr;// 5000/10K = 0.5S = 500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc-1;//TIMXCLK/PSC:72000 000/7200 = 10KHz
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;//设置时钟分割:TDTS = Tck_tim 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上计数  
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); 

	/* Enable the TIMER3 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);  

	TIM_ClearFlag(TIM3, TIM_FLAG_Update);
    TIM_ARRPreloadConfig(TIM3, DISABLE);
    
	TIM_Cmd(TIM3, ENABLE);
				 
}



void Timer1_Init(u16 arr, u16 psc)
{
	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	TIM_ITConfig( TIM1, TIM_IT_Update | TIM_IT_Trigger, ENABLE);
	
	TIM_TimeBaseStructure.TIM_Period = arr;// 200/10K = 0.02S =20ms
	TIM_TimeBaseStructure.TIM_Prescaler = psc-1;//TIMXCLK/PSC:72000 000/7200 = 10KHz
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;//设置时钟分割:TDTS = Tck_tim 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上计数 
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); 

	/* Enable the TIMER1 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);  

	TIM_ClearFlag(TIM1, TIM_FLAG_Update);
    TIM_ARRPreloadConfig(TIM1, DISABLE);
    
	TIM_Cmd(TIM1, ENABLE);

}



void InitDMAForADC(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	DMA_DeInit(DMA1_Channel1);
		
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;					//Peripheral address:ADC_Channel_14_Addr
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADCConvertedValue;		//DMA Memory address
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;                          //As data sources.
	DMA_InitStructure.DMA_BufferSize = 1;                                       //Length
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;             //Peripheral address register.
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;                 	//Memory address register.
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; //Peripheral Data width is 16
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;         //Memory Data width is 16
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;                             //Circular buffer mode
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;                         //Set Priority
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;                                //Disable the memory to memory transfer
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);

	DMA_Cmd(DMA1_Channel1, ENABLE);

    //DMA_ITConfig(DMA1_Channel1, DMA_IT_TC, ENABLE); 
    
}


void ADC_Config(void)
{ 	
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;

    InitDMAForADC();
    
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //72M/6=12M

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	

	ADC_DeInit(ADC1);
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;					//working in independent mode
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;						//Operating in Scanning channel mode
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;					//Working in a Scanning conversion mode
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//software trigger
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;				//Data alignment
	ADC_InitStructure.ADC_NbrOfChannel = 1;								//Conversion sequence length
	ADC_Init(ADC1, &ADC_InitStructure);
	
 	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_71Cycles5 );
 	
 	ADC_DMACmd(ADC1, ENABLE);					//Enable ADC DMA
	ADC_Cmd(ADC1, ENABLE);						//Start the ADC peripherals
	Delay_1ms(10);
	
	ADC_ResetCalibration(ADC1);					//Reset Calibration registers ADC
	while(ADC_GetResetCalibrationStatus(ADC1));	//Gets a ADC reset calibration register state, Waiting...
	
	ADC_StartCalibration(ADC1);					//Start the calibration status of ADC
	while(ADC_GetCalibrationStatus(ADC1));		//The calibration procedure to obtain ADC, Waiting
 
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//Start 

}	



void LED_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin   = A2DPLINK_PIN | SPPLINK_PIN | HFLINK_PIN | SCOLINK_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_Init(LEDPOTR, &GPIO_InitStructure);

	GPIO_ResetBits(LEDPOTR, A2DPLINK_PIN | SPPLINK_PIN | HFLINK_PIN | SCOLINK_PIN);
}

void Bluetooth_Ctrl_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin   = BLUEtOOtH_RSTPPIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_Init(BLUEtOOtH_RSTPORT, &GPIO_InitStructure);


	GPIO_InitStructure.GPIO_Pin   = BLUEtOOtH_POWERONPPIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_Init(BLUEtOOtH_POWERONPORT, &GPIO_InitStructure);

}
void Bluetooth_RST(void)
{
	GPIO_ResetBits(BLUEtOOtH_RSTPORT, BLUEtOOtH_RSTPPIN);
	Delay_1ms(2);
	GPIO_SetBits(BLUEtOOtH_RSTPORT, BLUEtOOtH_RSTPPIN);
}

void Bluetooth_PowerON(void)
{
	GPIO_SetBits(BLUEtOOtH_POWERONPORT, BLUEtOOtH_POWERONPPIN);
	Delay_1ms(600);
	GPIO_ResetBits(BLUEtOOtH_POWERONPORT, BLUEtOOtH_POWERONPPIN);
	SetChangeNameTimeout(16);
}


void SPIx_Init(void)
{	 
  
	SPI_InitTypeDef  SPI_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	/* Configure SPI1 pins: SCK, MISO and MOSI */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6|GPIO_Pin_7 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* SPI1 configuration */
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //设置SPI单向或者双向的数据模式:SPI设置为双线双向全双工
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		//设置SPI工作模式:设置为主SPI
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//设置SPI的数据大小:SPI发送接收8位帧结构
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;		//选择了串行时钟的稳态:时钟悬空高
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;	//数据捕获于第二个时钟沿

	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		//NSS信号由硬件（NSS管脚）还是软件（使用SSI位）管理:内部NSS信号有SSI位控制
//	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128;		//定义波特率预分频的值:波特率预分频值为256
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;		//定义波特率预分频的值:波特率预分频值为256
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
	SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRC值计算的多项式
	USR_SPI_Init(SPI1, &SPI_InitStructure);  //根据SPI_InitStruct中指定的参数初始化外设SPIx寄存器
	
	//SPI1->CR1|=1<<6; //SPI设备使能
	/* Enable SPI1  */
	USR_SPI_Cmd(SPI1, ENABLE); //使能SPI外设
    //使能PA4作为CS	
//	USR_SPI_SSOutputCmd(SPI1, ENABLE);
//
//	SPIx_ReadWriteByte(0xff);//启动传输		 
}  


u8 SPI_WriteByte(SPI_TypeDef* SPIx,u8 Byte)
{
	while((SPIx->SR&SPI_FLAG_TXE)==RESET);		//等待发送区空	  
	SPIx->DR=Byte;	 								//发送一个byte   
	while((SPIx->SR&SPI_FLAG_RXNE)==RESET);		//等待接收完一个byte  
	return SPIx->DR;          	     				//返回收到的数据			
} 

u8 SPIx_ReadWriteByte(u8 TxData)
{		
	u8 retry=0;				 
	//while((SPI1->SR&1<<1)==0)//等待发送区空	
	/* Loop while DR register in not emplty */
	while (USR_SPI_GetFlagStatus(SPI1, SPI_FLAG_TXE) == RESET) //检查指定的SPI标志位设置与否:发送缓存空标志位
	{
		retry++;
		if(retry>200)return 0;
	}			  
	//SPI1->DR=TxData;	 	  //发送一个byte 
	/* Send byte through the SPI1 peripheral */
	USR_SPI_SendData(SPI1, TxData); //通过外设SPIx发送一个数据
	retry=0;
	//while((SPI1->SR&1<<0)==0) //等待接收完一个byte  
	/* Wait to receive a byte */
	while (USR_SPI_GetFlagStatus(SPI1, SPI_FLAG_RXNE) == RESET); //检查指定的SPI标志位设置与否:接受缓存非空标志位
		{
		retry++;
		if(retry>200)return 0;
		}	  						    
	//return SPI1->DR;          //返回收到的数据
	/* Return the byte read from the SPI bus */
	return USR_SPI_ReceiveData(SPI1); //返回通过SPIx最近接收的数据				    
}


void ADS1298_GPIO_init(void)
{

  //STM32F103控制ADS1298引脚定义
  GPIO_InitTypeDef GPIO_InitStruct;
     //总线时钟允许
  /* Enable GPIOA GPIOB GPIOC clock */
 
  //PWDN --PD10	  
  GPIO_InitStruct.GPIO_Pin = ADS1299_PWDN_PIN;  
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode	= GPIO_Mode_Out_PP;	//作为输出端口
  GPIO_Init(ADS1299_PWDN_PORT, &GPIO_InitStruct) ;

  //START --PB0
  GPIO_InitStruct.GPIO_Pin = ADS1299_START_PIN;  
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode	= GPIO_Mode_Out_PP;	//作为输出端口
  GPIO_Init(ADS1299_START_PORT, &GPIO_InitStruct) ;

  //RESET --PA3
  GPIO_InitStruct.GPIO_Pin = ADS1299_RESET_PIN;  
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode	= GPIO_Mode_Out_PP;	//作为输出端口
  GPIO_Init(ADS1299_RESET_PORT, &GPIO_InitStruct) ;

  //CLKSEL --PC4
  GPIO_InitStruct.GPIO_Pin = ADS1299_CLKSEL_PIN;  //PC4
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode	= GPIO_Mode_Out_PP;	//作为输出端口
  GPIO_Init(ADS1299_CLKSEL_PORT, &GPIO_InitStruct) ;

  /* Configure I/O for Flash Chip select */
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;  //SPI CS
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;  //复用推挽输出
  GPIO_Init(ADS1299_CS_PORT, &GPIO_InitStruct);

}

EXTI_InitTypeDef EXTI_InitStruct_PD8;

void init_ADS1x9x_Data_Ready_Interrupt (void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_IPU;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource8);
	
	 /* Configure the EXTI9*/ 
	EXTI_InitStruct_PD8.EXTI_Line	= EXTI_Line8;
	EXTI_InitStruct_PD8.EXTI_Mode	= EXTI_Mode_Interrupt;
	EXTI_InitStruct_PD8.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStruct_PD8.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStruct_PD8);

	/* Enable the EXTI Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
		
}

void enable_ADS1x9x_Interrupt (unsigned char device_slot)
{
  EXTI_ClearITPendingBit(EXTI_Line8);
  EXTI_InitStruct_PD8.EXTI_LineCmd = ENABLE; 
  EXTI_Init(&EXTI_InitStruct_PD8);
}

void disable_ADS1x9x_Interrupt (unsigned char device_slot)
{
  EXTI_InitStruct_PD8.EXTI_LineCmd = DISABLE; 
  EXTI_Init(&EXTI_InitStruct_PD8);

}

void set_ADS1x9x_Start_Pin (unsigned char state)
{
	if(state==RESET)
		{
			ADS1298_StartLow();			
		}
	else if(state==SET)
    {
    	ADS1298_StartHigh();    	
    }
}	

#if 0

void Timer3_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;


	TIM_TimeBaseStructure.TIM_Period = arr;
	TIM_TimeBaseStructure.TIM_Prescaler =(psc-1);
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); 
 
	TIM_ITConfig(TIM3,TIM_IT_Update,   ENABLE);
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);  

	TIM_Cmd(TIM3, ENABLE); 
							 
}

void Timer2_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;


	TIM_TimeBaseStructure.TIM_Period = arr;
	TIM_TimeBaseStructure.TIM_Prescaler =(psc-1);
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); 
 
	TIM_ITConfig(TIM2,TIM_IT_Update,   ENABLE);
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);  

	TIM_Cmd(TIM2, ENABLE); 
							 
}

void SysTick_Configuration( void )
{
    /*  Set SysTick Timer For 1us Interrupt  */
    if(SysTick_Config(72000000 / 1000000))
    {
        /*  Capture Error  */
        while(1);
    }

    /*  Configure The SysTick Handler Priority  */
    NVIC_SetPriority(SysTick_IRQn, 0x00);
}

void KEY_Init(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE); 
	
	
	GPIO_InitStructure.GPIO_Pin = KEY_PIN_SEL | KEY_PIN_START | KEY_PIN_UP | KEY_PIN_DOWN;      
  	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(KEY_PORT, &GPIO_InitStructure);	
}

void Photosensitive_Init(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin   = PHOTOSENSOR_PIN;      
  	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(PHOTOSENSOR_PORT, &GPIO_InitStructure);	
}

void Alarm_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = ALARM_PIN; 
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(ALARM_PORT, &GPIO_InitStructure);
  	GPIO_ResetBits(ALARM_PORT, ALARM_PIN);
}

void Beep_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = BEEP_PIN; 
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(BEEP_PORT, &GPIO_InitStructure);

  	GPIO_SetBits(BEEP_PORT,BEEP_PIN);
}


void Digital_LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = DIGITAL_LED_AA 
								 |DIGITAL_LED_BB
								 |DIGITAL_LED_CC
								 |DIGITAL_LED_DD
								 |DIGITAL_LED_EE
								 |DIGITAL_LED_FF
								 |DIGITAL_LED_GG
								 |DIGITAL_LED_HH; 
								 
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(DIGITAL_LED_PORT, &GPIO_InitStructure);
	
	GPIO_ResetBits(DIGITAL_LED_PORT , DIGITAL_LED_AA 
									 |DIGITAL_LED_BB
									 |DIGITAL_LED_CC
									 |DIGITAL_LED_DD
									 |DIGITAL_LED_EE
									 |DIGITAL_LED_FF
									 |DIGITAL_LED_GG
									 |DIGITAL_LED_HH);

	GPIO_InitStructure.GPIO_Pin = DIGITAL_LED_CTRL_W1 
								 |DIGITAL_LED_CTRL_W2
								 |DIGITAL_LED_CTRL_W3
								 |DIGITAL_LED_CTRL_W4; 
								 
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(DIGITAL_LED_CTRL_PORT, &GPIO_InitStructure);
	
	GPIO_ResetBits(DIGITAL_LED_CTRL_PORT , DIGITAL_LED_CTRL_W1 
										  |DIGITAL_LED_CTRL_W2
										  |DIGITAL_LED_CTRL_W3
								 		  |DIGITAL_LED_CTRL_W4);

}



void PVD_Config(void)
{
    EXTI_InitTypeDef EXTI_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    /* Enable PWR and BKP clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

    /* Configure EXTI Line16(PVD Output) to generate an 
     interrupt on rising and falling edges */
    EXTI_ClearITPendingBit(EXTI_Line16);
    EXTI_InitStructure.EXTI_Line = EXTI_Line16;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	 
    /* Enable the PVD Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = PVD_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
	PWR_PVDLevelConfig(PWR_PVDLevel_2V9);

    /* Enable the PVD Output */
    PWR_PVDCmd(ENABLE);
}


void Flash_Init(void)
{
	//u32 cnt = 0;
	//u16 data[5] = {0x0001, 0x0002, 0x0003, 0x0004, 0x0005};	
	//u16 Flash[5]= {0};
	U16 usDat = 0;
	//U8 i = 0;
	FLASH_Unlock();

	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR );

	#if 0
	FLASH_ErasePage(FLASH_ADDR);

	do											   
	{
		FLASH_ProgramHalfWord((FLASH_ADDR + cnt * 2), data[cnt]);
		cnt++;
	}while(cnt != 5);

	FLASH_Lock();
	
	//FLASH_ProgramHalfWord((0x8007000), 0x0007);
	
	Delay5ms(20);

	for(i = 0; i < 5; i++)
	{
		Flash[i] = *(vu32*)(FLASH_ADDR + i*2);
		printf("\r\n Flash[i]=%x",Flash[i]);
	}
	#endif
	
	usDat = *(vu32*)(FLASH_ADDR);

	printf("\r\n 1usDat %x",usDat);

	if(usDat == 0xffff)
	{
		usDat = 0x1234;
	}
	
	printf("\r\n 2usDat %x",usDat);
	
	FLASH_ErasePage(FLASH_ADDR);
}

void LogicNumInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = LOGIC_2_PIN 
								 |LOGIC_8_PIN
								 |LOGIC_7_PIN; 
								 
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(LOGIC_PORT1, &GPIO_InitStructure);
	
	GPIO_SetBits(LOGIC_PORT1 , 	  LOGIC_2_PIN 
								 |LOGIC_8_PIN
								 |LOGIC_7_PIN);

	GPIO_InitStructure.GPIO_Pin = LOGIC_9_PIN 
								 |LOGIC_10_PIN
								 |LOGIC_11_PIN
								 |LOGIC_24_PIN 
								 |LOGIC_23_PIN
								 |LOGIC_12_PIN
								 |LOGIC_13_PIN 
								 |LOGIC_14_PIN
								 |LOGIC_15_PIN; 
								 
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(LOGIC_PORT2, &GPIO_InitStructure);
	
	GPIO_SetBits(LOGIC_PORT2 ,    LOGIC_9_PIN 
								 |LOGIC_10_PIN
								 |LOGIC_11_PIN
 								 |LOGIC_24_PIN
 								 |LOGIC_23_PIN
 								 |LOGIC_12_PIN
 								 |LOGIC_13_PIN
 								 |LOGIC_14_PIN
 								 |LOGIC_15_PIN);
}
#endif
