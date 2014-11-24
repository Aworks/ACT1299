#ifndef __ADC_H__
#define __ADC_H__

#undef EXTERN

#ifdef __ADC_C__
#define EXTERN
#else
#define EXTERN extern
#endif


#include "typedef.h"
#include "stm32f10x.h"


EXTERN u16 Get_Adc(void);
EXTERN void InitDMAForADC(void);
EXTERN void GetDMA(void);

#endif

