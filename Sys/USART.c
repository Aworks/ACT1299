#include "stm32f10x.h"
#include "USART.h"
#include "timer.h"
#include "ADC.h"
#include "printf.h"
#include "i2c.h"
#include "delay.h"

/*******************************************************************************
* Function Name  : USART1_Configuration
* Description    : Configures the USART1 
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
/* USART1 configured as follow:
        - BaudRate = 115200 baud  
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control Disabled
        - Receive and transmit enabled
*/

/*******************************************************************************
* Function Name  : USART1_GPIO_Configuration
* Description    : Configures the uart1 GPIO ports.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/


/* USART2 configured as follow:
        - BaudRate = 115200 baud  
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control Disabled
        - Receive and transmit enabled
*/
void USART2_Configuration(void)
{
  USART_InitTypeDef USART_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
  //USART_ITConfig(USART2, USART_IT_TXE, ENABLE);
  
   /* Configure the USART2*/ 
  USART_InitStructure.USART_BaudRate = 9600;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  USART_Init(USART2, &USART_InitStructure);
  
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  USART_Cmd(USART2, ENABLE);
}

/*******************************************************************************
* Function Name  : USART2_GPIO_Configuration
* Description    : Configures the uart1 GPIO ports.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
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


//while(UART1GetByte(USART1, &i))
//{
// 	USART_SendData(USART1,i);
// 	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET); 
// 	Puts(USART1,"\r\n RCV OK");
//}


