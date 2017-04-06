/*****************************************************************************
 *   Placeholder for PWM related functions.
 *   Part of the proposed solutions for LPCXpresso Experiment Kit
 *
 *   Copyright(C) 2013, Embedded Artists AB
 *   All rights reserved.
 *
 ******************************************************************************/

#include "LPC11xx.h"
#include "type.h"
#include "pwm.h"

/*****************************************************************************
** Function name:  initPWM
**
** Descriptions:   Initialize 16-bit timer #1 for PWM generation
**
** Parameters:     cycleLength: set PWM cycle length in microseconds
**
** Returned value: None
**
*****************************************************************************/
void initPWM(uint16_t cycleLengthInUs)
{
  LPC_SYSCON->SYSAHBCLKCTRL |= (1<<8); /* Enable timer #1 (enable clock to block) */

  //setup I/O pins to be MAT-outputs
  LPC_IOCON->PIO1_9   &= ~0x07;
  LPC_IOCON->PIO1_9   |=  0x01;       /* 16-bit timer#1 MAT0 */
  LPC_IOCON->PIO1_10  &= ~0x07;
  LPC_IOCON->PIO1_10  |=  0x02;       /* 16-bit timer#1 MAT1 */

  LPC_TMR16B1->TCR = 0x02;            /* reset timer */
  
  /* Set prescaler so that timer counts in us-steps */
  /*(SystemCoreClock/LPC_SYSCON->SYSAHBCLKDIV) = 48000000 => Timer clock is 48MHz */
  LPC_TMR16B1->PR  = ((SystemCoreClock/LPC_SYSCON->SYSAHBCLKDIV) / 1000000) - 1;
  LPC_TMR16B1->MR2 = cycleLengthInUs;

  //Setup match registers to generate a PWM signal with 0% duty = constant low
  LPC_TMR16B1->MR0 = LPC_TMR16B1->MR2;
  LPC_TMR16B1->MR1 = LPC_TMR16B1->MR2;

  LPC_TMR16B1->IR   = 0xff;            /* reset all interrupts (not needed) */
  LPC_TMR16B1->MCR  = (1<<7);          /* reset timer on MR2 match */
  LPC_TMR16B1->PWMC = (1<<0) | (1<<1); /* Enable PWM mode for MAT0 and MAT1 */
}

/*****************************************************************************
** Function name:  startPWM
**
** Descriptions:   Start 16-bit timer #1
**
** Parameters:     None
**
** Returned value: None
**
*****************************************************************************/
void startPWM(void)
{
  LPC_TMR16B1->TCR = 0x01;  /* start timer (16B1) = start generating PWM signal(s) */
}

/*****************************************************************************
** Function name:  stopPWM
**
** Descriptions:   Stop 16-bit timer #1
**
** Parameters:     None
**
** Returned value: None
**
*****************************************************************************/
void stopPWM(void)
{
  LPC_TMR16B1->TCR = 0x00;  /* stop timer (16B1) = stop generating PWM signal(s) */
}

/*****************************************************************************
** Function name:  updatePWM100
**
** Descriptions:   Update the PWM output setting
**
** Parameters:     channel: selects with PWM signals to update (0 or 1)
**                 value:   set duty cycle (a value between 0 and 100)
**
** Returned value: None
**
*****************************************************************************/
void updatePWM100( uint8_t channel, uint16_t value)
{
  uint32_t matchValue;

  matchValue = (LPC_TMR16B1->MR2 * (100 - value)) / 100;
  if (channel == 0)
    LPC_TMR16B1->MR0 = matchValue;
  else if (channel == 1)
    LPC_TMR16B1->MR1 = matchValue;
}

/*****************************************************************************
** Function name:  updatePWM1000
**
** Descriptions:   Update the PWM output setting
**
** Parameters:     channel: selects with PWM signals to update (0 or 1)
**                 value:   set duty cycle (a value between 0 and 1000)
**
** Returned value: None
**
*****************************************************************************/
void updatePWM1000( uint8_t channel, uint16_t value)
{
  uint32_t matchValue;

  matchValue = (LPC_TMR16B1->MR2 * (1000 - value)) / 1000;
  if (channel == 0)
    LPC_TMR16B1->MR0 = matchValue;
  else if (channel == 1)
    LPC_TMR16B1->MR1 = matchValue;
}

/*****************************************************************************
** Function name:  updatePWM10000
**
** Descriptions:   Update the PWM output setting
**
** Parameters:     channel: selects with PWM signals to update (0 or 1)
**                 value:   set duty cycle (a value between 0 and 10000)
**
** Returned value: None
**
*****************************************************************************/
void updatePWM10000( uint8_t channel, uint16_t value)
{
  uint32_t matchValue;

  matchValue = (LPC_TMR16B1->MR2 * (10000 - value)) / 10000;
  if (channel == 0)
    LPC_TMR16B1->MR0 = matchValue;
  else if (channel == 1)
    LPC_TMR16B1->MR1 = matchValue;
}
