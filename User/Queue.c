#define __QUEUE_C__


#include "QUEUE.h"
#include "global.h"

//记录缓冲器压入栈是否已到最大
U8 Enqueue_Bit=0;
//存放数据的环形队列
S8 queue[EnqueueLen];
/*利用队列方式来完成对一个迷宫数组进行深度搜索*/
WORD head = 0;
WORD tail = 0;
//signed char ADS1x9x_Data [ADS1298_DATA_LENGTH];

/*入栈*/
void Push_Enqueue(char data)
{
    if(tail == EnqueueLen)
	{
        tail = 0;
		Enqueue_Bit = 1;
    }
     queue[tail++] = data;

 }
 
/*出栈*/
char PopDequeue(void)
{
     if(head == EnqueueLen)
	 {
         head = 0;
		 Enqueue_Bit = 0;
     }
     return queue[head++];
}
 
/*判断队列是否为空*/
int is_empty(void)
{
	if((head == tail)&&(Enqueue_Bit==0))
	{
    	return 1;
	}
	else
	{

	 	return 0;
	}
}



