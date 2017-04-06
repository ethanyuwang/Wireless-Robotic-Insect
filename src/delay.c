/*****************************************************************************
 *   Placeholder for delay functions.
 *   Part of the proposed solutions for LPCXpresso Experiment Kit
 *
 *   Copyright(C) 2013, Embedded Artists AB
 *   All rights reserved.
 *
 ******************************************************************************/

#include "type.h"
#include "delay.h"
#include "LPC11xx.h"

#define MS_1           2440
#define USE_TIMER

#ifndef USE_TIMER
/*****************************************************************************
 ** Function name:               delayMS
 **
 ** Descriptions:                Delay execution for specified time.
 **
 ** parameters:                  delay in milliseconds
 ** Returned value:              None
 **
 *****************************************************************************/
void
delayMS(uint32_t ms)
{
  volatile uint32_t i;
  uint32_t nops;
  nops = MS_1 * ms;

  for (i = 0; i < nops; i++)
    asm volatile ("nop");
}

/*****************************************************************************
 ** Function name:               delayUS
 **
 ** Descriptions:                Delay execution for specified time.
 **
 ** parameters:                  delay in microseconds
 ** Returned value:              None
 **
 *****************************************************************************/
void
delayUS(uint32_t us)
{
  volatile uint32_t i;
  uint32_t nops;
  nops = (MS_1 * us) / 1000;

  for (i = 0; i < nops; i++)
    asm volatile ("nop");
}

#else

/*****************************************************************************
** Function name:  delayMS
**
** Descriptions:   Start the timer delay in milliseconds until elapsed
**                 32-bit timer #0 is used
**
** Parameters:     Delay value in millisecond
**
** Returned value: None
**
*****************************************************************************/
void delayMS(uint32_t delayInMs)
{
  //setup timer #0 for delay
  LPC_SYSCON->SYSAHBCLKCTRL |= (1<<9); /* Enable 32-bit timer #0 clock */
  LPC_TMR32B0->TCR = 0x02;             /* reset timer */
  LPC_TMR32B0->PR  = 0x00;             /* set prescaler to zero */

  //limit delay to 85 seconds in order not to overflow the 32-bit counter
  if (delayInMs > 85000)
    delayInMs = 85000;
  //(SystemCoreClock/LPC_SYSCON->SYSAHBCLKDIV) = 48000000 => Timer clock is 48MHz
  LPC_TMR32B0->MR0 = delayInMs * ((SystemCoreClock/LPC_SYSCON->SYSAHBCLKDIV)/ 1000);

  LPC_TMR32B0->IR  = 0xff;             /* reset all interrupts (not needed) */
  LPC_TMR32B0->MCR = 0x04;             /* stop timer on match */
  LPC_TMR32B0->TCR = 0x01;             /* start timer */

  /* wait until delay time has elapsed */
  while (LPC_TMR32B0->TCR & 0x01);
}

/*****************************************************************************
** Function name:  delayUS
**
** Descriptions:   Start the timer delay in microseconds until elapsed
**                 32-bit timer #0 is used
**
** Parameters:     Delay value in microseconds
**
** Returned value: None
**
*****************************************************************************/
void delayUS(uint32_t delayInUs)
{
  //setup timer #0 for delay
  LPC_SYSCON->SYSAHBCLKCTRL |= (1<<9); /* Enable 32-bit timer #0 clock */
  LPC_TMR32B0->TCR = 0x02;             /* reset timer */
  LPC_TMR32B0->PR  = 0x00;             /* set prescaler to zero */

  //limit delay to 85 seconds in order not to overflow the 32-bit counter
  if (delayInUs > 85000000)
    delayInUs = 85000000;

  //(SystemCoreClock/LPC_SYSCON->SYSAHBCLKDIV) = 48000000 => Timer clock is 48MHz
  LPC_TMR32B0->MR0 = delayInUs * ((SystemCoreClock/LPC_SYSCON->SYSAHBCLKDIV)/ 1000000);

  LPC_TMR32B0->IR  = 0xff;             /* reset all interrupts (not needed) */
  LPC_TMR32B0->MCR = 0x04;             /* stop timer on match */
  LPC_TMR32B0->TCR = 0x01;             /* start timer */

  /* wait until delay time has elapsed */
  while (LPC_TMR32B0->TCR & 0x01);
}
#endif

/*****************************************************************************
 ** Function name:               delayNops
 **
 ** Descriptions:                Delay by executing a given number of NOPs.
 **                              About 2.440.000 iterations per second.
 **
 ** parameters:                  number of NOP instructions
 ** Returned value:              None
 **
 *****************************************************************************/
void
delayNops(uint32_t nops)
{
  volatile uint32_t i;

  for (i = 0; i < nops; i++)
    asm volatile ("nop");
}

