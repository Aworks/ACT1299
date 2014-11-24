#ifndef __QUEUE_H__
#define __QUEUE_H__

#undef EXTERN

#ifdef __QUEUE_C__
#define EXTERN
#else
#define EXTERN extern
#endif


#include "typedef.h"
#include "stm32f10x.h"
#include "global.h"

EXTERN void Push_Enqueue(char data);
EXTERN char PopDequeue(void);
EXTERN int is_empty(void);

EXTERN U8 Enqueue_Bit;
EXTERN S8 queue[EnqueueLen];
EXTERN WORD head;
EXTERN WORD tail;

#endif

