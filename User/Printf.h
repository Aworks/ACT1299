#ifndef __PRINTF_H__
#define __PRINTF_H__

#undef EXTERN

#ifdef __PRINTF_C__
#define EXTERN
#else
#define EXTERN extern
#endif


#include "typedef.h"
#include <stdio.h>
#include "string.h"


EXTERN void Puts(u8* pBuffer);


#endif

