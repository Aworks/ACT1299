#define __PRINTF_C__


#include "printf.h"

#if 0
#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */


PUTCHAR_PROTOTYPE
{
  USART_SendData(USART1, (uint8_t) ch);
  /* Loop until the end of transmission */
  while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
  {
  
  }
  return ch;
}
#else
int fputc(int ch, FILE *f)
{
	USART_SendData(USART2, (u8) ch);
	while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
	return ch;
}
#endif




#if 1
void Puts(u8* pBuffer)
{
	u16 temp;
    //while(NumByteToSend--)
    while(*pBuffer!='\0')
    {
        temp = (u16)(*pBuffer)&0x00FF;
        USART_SendData(USART2,temp);
        while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET); 
        pBuffer++;
    }    
}
#else
void Puts( USART_TypeDef* USARTx,u8* pBuffer)
{
	while(*pBuffer!='\0')
	{
		USART_SendData(USARTx, *pBuffer++);
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET); 
	}
}
#endif




