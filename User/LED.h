#ifndef __LED_H__
#define __LED_H__

#undef EXTERN

#ifdef __LED_C__
#define EXTERN
#else
#define EXTERN extern
#endif


#include "typedef.h"
EXTERN void LED_GPIO_Configuration(void);
EXTERN void Turn_On_LED(U8 LED_NUM);


#endif


