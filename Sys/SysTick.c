#include "stm32f10x.h"
#include "delay.h"
#include "GLOBAL.h"

static __IO uint32_t TimingDelay;
/*******************************************************************************
* Function Name  : SysTick_Configuration
* Description    : Configure a SysTick Base time to 1us.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SysTick_Configuration(void)
{
  /* Setup SysTick Timer for 1us interrupts  */
  if (SysTick_Config(SystemCoreClock / 1000000))
  { 
    /* Capture error */ 
    while (1);
  }
 /* Configure the SysTick handler priority */
  NVIC_SetPriority(SysTick_IRQn, 0x00);
}

/*******************************************************************************
* Function Name  : Delay_100us
* Description    : Inserts a delay time.
* Input          : nTime: specifies the delay time length, in milliseconds.
* Output         : None
* Return         : None
*******************************************************************************/
void Delay_100us(uint32_t nTime)
{  
  TimingDelay = nTime * 100;
  while (TimingDelay != 0);
}

void Delay_1ms(uint32_t nTime)
{  
  TimingDelay = nTime * 1000;
  while (TimingDelay != 0);
}

void Delay_1us(uint32_t nTime)
{  
  TimingDelay = nTime;
  while (TimingDelay != 0);
}



/*******************************************************************************
* Function Name  : TimingDelayMs_Decrement
* Description    : Decrements the TimingDelay variable.
* Input          : None
* Output         : TimingDelay
* Return         : None
*******************************************************************************/
void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  { 
    TimingDelay--;
  }

}


