#ifndef __USER_CORECONFIG_H__
#define __USER_CORECONFIG_H__

#undef EXTERN

#ifdef __USER_CORECONFIG_C__
#define EXTERN
#else
#define EXTERN extern
#endif


#include "typedef.h"
#include "stm32f10x.h"


EXTERN void RCC_Config(void);
EXTERN void NVIC_Config(void);
EXTERN void USART1_Config(u32 bound);
EXTERN void USART2_Config(u32 bound);

EXTERN void LED_GPIO_Config(void);
EXTERN void Timerx_Init(U16 arr,U16 psc);
EXTERN void Timer1_Init(u16 arr, u16 psc);
EXTERN void ADC_Config(void);
EXTERN void Bluetooth_RST(void);
EXTERN void Bluetooth_PowerON(void);
EXTERN void Bluetooth_Ctrl_Config(void);
EXTERN void SPIx_Init(void);
EXTERN u8 SPI_WriteByte(SPI_TypeDef* SPIx,u8 Byte);
EXTERN u8 SPIx_ReadWriteByte(u8 TxData);
EXTERN void init_ADS1x9x_Data_Ready_Interrupt (void);


#define ADS1299_PWDN_PORT	GPIOC
#define ADS1299_PWDN_PIN	GPIO_Pin_3

#define ADS1299_START_PORT	GPIOA
#define ADS1299_START_PIN	GPIO_Pin_1

#define ADS1299_RESET_PORT	GPIOB
#define ADS1299_RESET_PIN	GPIO_Pin_0

#define ADS1299_CLKSEL_PORT	GPIOB
#define ADS1299_CLKSEL_PIN	GPIO_Pin_1

#define ADS1299_CS_PORT		GPIOB
#define ADS1299_CS_PIN		GPIO_Pin_2



//STM32F103控制ADS1298引脚定义
//PWDN --PB10,输出0，ads1298断电，输出1则上电
#define ADS1298_PowerUp()   	GPIO_SetBits(ADS1299_PWDN_PORT,ADS1299_PWDN_PIN)
#define ADS1298_PowerDown() 	GPIO_ResetBits(ADS1299_PWDN_PORT,ADS1299_PWDN_PIN)

//START --PB0
#define ADS1298_StartHigh() 	GPIO_SetBits(ADS1299_START_PORT,ADS1299_START_PIN)
#define ADS1298_StartLow()  	GPIO_ResetBits(ADS1299_START_PORT,ADS1299_START_PIN)

//RESET --PA3,进行复位需产生一个低电平脉冲
#define ADS1298_ResetLow()  	GPIO_ResetBits(ADS1299_RESET_PORT,ADS1299_RESET_PIN)
#define ADS1298_ResetHigh() 	GPIO_SetBits(ADS1299_RESET_PORT,ADS1299_RESET_PIN)

//CLKSEL --PC4
#define ADS1298_ClkselHigh() 	GPIO_SetBits(ADS1299_CLKSEL_PORT,ADS1299_CLKSEL_PIN)
#define ADS1298_ClkselLow()  	GPIO_ResetBits(ADS1299_CLKSEL_PORT,ADS1299_CLKSEL_PIN)

//Chip Select --PB1,片选
#define ADS1298_CS_Low()  		GPIO_ResetBits(ADS1299_CS_PORT,ADS1299_CS_PIN)
#define ADS1298_CS_High() 		GPIO_SetBits(ADS1299_CS_PORT,ADS1299_CS_PIN)



#define LEDPOTR			GPIOC
#define A2DPLINK_PIN	GPIO_Pin_6	
#define SPPLINK_PIN		GPIO_Pin_7	
#define HFLINK_PIN		GPIO_Pin_8	
#define SCOLINK_PIN		GPIO_Pin_9	

#define BLUEtOOtH_RSTPORT		GPIOC
#define BLUEtOOtH_RSTPPIN		GPIO_Pin_1

#define BLUEtOOtH_POWERONPORT	GPIOC
#define BLUEtOOtH_POWERONPPIN	GPIO_Pin_2


EXTERN void enable_ADS1x9x_Interrupt (unsigned char device_slot);
EXTERN void disable_ADS1x9x_Interrupt (unsigned char device_slot);
EXTERN void set_ADS1x9x_Start_Pin (unsigned char state);
EXTERN void ADS1298_GPIO_init(void);


#if 0
EXTERN void Uart_init(u32 bound);
EXTERN void Timer3_Init(u16 arr,u16 psc);
EXTERN void Timer2_Init(u16 arr,u16 psc);
EXTERN void Photosensitive_Init(void);
EXTERN void SysTick_Configuration( void );
EXTERN void KEY_Init(void);
EXTERN void RCC_Config(void);
EXTERN void Digital_LED_Init(void);
EXTERN void Alarm_Init(void);
EXTERN void Beep_Init(void);
EXTERN void PVD_Config(void);
EXTERN void Flash_Init(void);
EXTERN void LogicNumInit(void);
#endif
#endif

