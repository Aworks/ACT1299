#define __QUEUE_C__


#include "QUEUE.h"
#include "global.h"

//��¼������ѹ��ջ�Ƿ��ѵ����
U8 Enqueue_Bit=0;
//������ݵĻ��ζ���
S8 queue[EnqueueLen];
/*���ö��з�ʽ����ɶ�һ���Թ���������������*/
WORD head = 0;
WORD tail = 0;
//signed char ADS1x9x_Data [ADS1298_DATA_LENGTH];

/*��ջ*/
void Push_Enqueue(char data)
{
    if(tail == EnqueueLen)
	{
        tail = 0;
		Enqueue_Bit = 1;
    }
     queue[tail++] = data;

 }
 
/*��ջ*/
char PopDequeue(void)
{
     if(head == EnqueueLen)
	 {
         head = 0;
		 Enqueue_Bit = 0;
     }
     return queue[head++];
}
 
/*�ж϶����Ƿ�Ϊ��*/
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



