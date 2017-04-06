/*****************************************************************************
 *   Placeholder for ADC related functions.
 *   Part of the proposed solutions for LPCXpresso Experiment Kit
 *
 *   Copyright(C) 2013, Embedded Artists AB
 *   All rights reserved.
 *
 ******************************************************************************/
#ifndef __ADC_H__
#define __ADC_H__

#include "type.h"

// Create define for simpler access of analog inputs
#define AIN0         0
#define AIN1         1
#define AIN2         2
#define AIN3         3

/*****************************************************************************
** Function name:               ADCInit
**
** Descriptions:                initialize ADC channel
**
** parameters:                  ADC clock rate
** Returned value:              None
**
*****************************************************************************/
void ADCInit( uint32_t ADC_Clk );

/*****************************************************************************
** Function name:               getADC
**
** Descriptions:                Read ADC channel
**
** parameters:                  Channel number
** Returned value:              Value read
**
*****************************************************************************/
uint32_t getADC( uint8_t channelNum );

#endif /* __ADC_H__ */
