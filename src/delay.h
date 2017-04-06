/*****************************************************************************
 *   Placeholder for delay functions.
 *   Part of the proposed solutions for LPCXpresso Experiment Kit
 *
 *   Copyright(C) 2013, Embedded Artists AB
 *   All rights reserved.
 *
 ******************************************************************************/
#ifndef __DELAY_H__
#define __DELAY_H__

#include "type.h"

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
delayNops(uint32_t nops);

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
delayMS(uint32_t ms);

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
delayUS(uint32_t us);

#endif /* __DELAY_H__ */
