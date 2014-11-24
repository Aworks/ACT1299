#ifndef __DAC_H__
#define __DAC_H__

#undef EXTERN

#ifdef __DAC_C__
#define EXTERN
#else
#define EXTERN extern
#endif


#include "typedef.h"

#include "stm32f10x.h"
#define  DAC_Out1_Code   0x1FF0
#define  DAC_Out2_Code   0xFFF0
EXTERN void DAC_GPIO_Configuration(void);
EXTERN void DAC_Configuration(void);
EXTERN void DAC_Config(void);
EXTERN void Dac1_Set_Vol(u16 vol);

#endif

