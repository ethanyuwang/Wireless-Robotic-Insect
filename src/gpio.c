/*****************************************************************************
 *   Placeholder for GPIO related functions.
 *   Part of the proposed solutions for LPCXpresso Experiment Kit
 *
 *   Copyright(C) 2013, Embedded Artists AB
 *   All rights reserved.
 *
 ******************************************************************************/

#include "LPC11xx.h"
#include "type.h"
#include "gpio.h"

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
GPIOSetValue(uint32_t portNum, uint32_t bitPosi, uint32_t bitVal)
{
  // Check that bitVal is a binary value - 0 or 1
  if (bitVal < 2)
    {
      /* The MASKED_ACCESS registers give the ability to write to a specific bit
       * (or bits) within the GPIO data register. See the LPC11/13 user manual
       * for more details.
       *
       * (1<<bitPosi) gives us the MASKED_ACCESS register specific to the bit
       * that is being requested to be set or cleared.
       *
       * (bitVal<<bitPosi) will be either be 0 or will contain a 1 in the
       * appropriate bit position that matches the MASKED_ACCESS register
       * being written to.
       */
      switch (portNum)
        {
      case PORT0:
        LPC_GPIO0 ->MASKED_ACCESS[(1 << bitPosi)] = (bitVal << bitPosi);
        break;
      case PORT1:
        LPC_GPIO1 ->MASKED_ACCESS[(1 << bitPosi)] = (bitVal << bitPosi);
        break;
      case PORT2:
        LPC_GPIO2 ->MASKED_ACCESS[(1 << bitPosi)] = (bitVal << bitPosi);
        break;
      case PORT3:
        LPC_GPIO3 ->MASKED_ACCESS[(1 << bitPosi)] = (bitVal << bitPosi);
        break;
      default:
        break;
        }
    }
}

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
GPIOSetDir(uint32_t portNum, uint32_t bitPosi, uint32_t dir)
{
  /* if DIR is OUT(1), but GPIOx_DIR is not set, set DIR
   to OUT(1); if DIR is IN(0), but GPIOx_DIR is set, clr
   DIR to IN(0). All the other cases are ignored.
   On port3(bit 0 through 3 only), no error protection if
   bit value is out of range. */
  switch (portNum)
    {
  case PORT0:
    if (!(LPC_GPIO0 ->DIR & (0x1 << bitPosi)) && (dir == GPIO_OUTPUT))
      LPC_GPIO0 ->DIR |= (0x1 << bitPosi);
    else if ((LPC_GPIO0 ->DIR & (0x1 << bitPosi)) && (dir == GPIO_INPUT))
      LPC_GPIO0 ->DIR &= ~(0x1 << bitPosi);
    break;
  case PORT1:
    if (!(LPC_GPIO1 ->DIR & (0x1 << bitPosi)) && (dir == GPIO_OUTPUT))
      LPC_GPIO1 ->DIR |= (0x1 << bitPosi);
    else if ((LPC_GPIO1 ->DIR & (0x1 << bitPosi)) && (dir == GPIO_INPUT))
      LPC_GPIO1 ->DIR &= ~(0x1 << bitPosi);
    break;
  case PORT2:
    if (!(LPC_GPIO2 ->DIR & (0x1 << bitPosi)) && (dir == GPIO_OUTPUT))
      LPC_GPIO2 ->DIR |= (0x1 << bitPosi);
    else if ((LPC_GPIO2 ->DIR & (0x1 << bitPosi)) && (dir == GPIO_INPUT))
      LPC_GPIO2 ->DIR &= ~(0x1 << bitPosi);
    break;
  case PORT3:
    if (!(LPC_GPIO3 ->DIR & (0x1 << bitPosi)) && (dir == GPIO_OUTPUT))
      LPC_GPIO3 ->DIR |= (0x1 << bitPosi);
    else if ((LPC_GPIO3 ->DIR & (0x1 << bitPosi)) && (dir == GPIO_INPUT))
      LPC_GPIO3 ->DIR &= ~(0x1 << bitPosi);
    break;
  default:
    break;
    }
  return;
}

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
uint8_t GPIOGetValue( uint32_t portNum, uint32_t bitPosi)
{
  uint8_t ret = 0;

  switch ( portNum )
  {
    case PORT0:

        ret = ( (LPC_GPIO0->DATA & (0x1 << bitPosi)) != 0);
    break;
    case PORT1:
        ret = ( (LPC_GPIO1->DATA & (0x1 << bitPosi)) != 0);
    break;
    case PORT2:
        ret = ( (LPC_GPIO2->DATA & (0x1 << bitPosi)) != 0);
    break;
    case PORT3:
        ret = ( (LPC_GPIO3->DATA & (0x1 << bitPosi)) != 0);
    break;
    default:
      break;
  }
  return ret;
}

