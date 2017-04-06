/*****************************************************************************
 *   Placeholder for PWM related functions.
 *   Part of the proposed solutions for LPCXpresso Experiment Kit
 *
 *   Copyright(C) 2013, Embedded Artists AB
 *   All rights reserved.
 *
 ******************************************************************************/
#ifndef __PWM_H__
#define __PWM_H__

#include "type.h"

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
void initPWM(uint16_t cycleLengthInUs);

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
void startPWM(void);

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
void stopPWM(void);

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
void updatePWM100( uint8_t channel, uint16_t value);

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
void updatePWM1000( uint8_t channel, uint16_t value);

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
void updatePWM10000( uint8_t channel, uint16_t value);

#endif /* __PWM_H__ */
