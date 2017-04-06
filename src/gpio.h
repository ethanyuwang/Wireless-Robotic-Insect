/*****************************************************************************
 *   Placeholder for GPIO related functions.
 *   Part of the proposed solutions for LPCXpresso Experiment Kit
 *
 *   Copyright(C) 2013, Embedded Artists AB
 *   All rights reserved.
 *
 ******************************************************************************/
#ifndef __GPIO_H__
#define __GPIO_H__

#include "type.h"

#define PORT0          0
#define PORT1          1
#define PORT2          2
#define PORT3          3

#define GPIO_INPUT     0
#define GPIO_OUTPUT    1

/*****************************************************************************
 ** Function name:		GPIOSetValue
 **
 ** Descriptions:		Set/clear a bitvalue in a specific bit position
 **				in GPIO portX(X is the port number.)
 **
 ** parameters:			port num, bit position, bit value
 ** Returned value:		None
 **
 *****************************************************************************/
void
GPIOSetValue(uint32_t portNum, uint32_t bitPosi, uint32_t bitVal);

/*****************************************************************************
 ** Function name:		GPIOSetDir
 **
 ** Descriptions:		Set the direction in GPIO port
 **
 ** parameters:			port num, bit position, direction (1 out, 0 input)
 ** Returned value:		None
 **
 *****************************************************************************/
void
GPIOSetDir(uint32_t portNum, uint32_t bitPosi, uint32_t dir);

/*****************************************************************************
** Function name:       GPIOGetValue
**
** Descriptions:        Get bitvalue in a specific bit position
**                      in GPIO portX(X is the port number.)
**
** parameters:          port num, bit position
** Returned value:      bit value
**
*****************************************************************************/
uint8_t GPIOGetValue( uint32_t portNum, uint32_t bitPosi);

#endif /* __GPIO_H__ */
