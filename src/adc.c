/*****************************************************************************
 *   Placeholder for ADC related functions.
 *   Part of the proposed solutions for LPCXpresso Experiment Kit
 *
 *   Copyright(C) 2013, Embedded Artists AB
 *   All rights reserved.
 *
 ******************************************************************************/

#include "LPC11xx.h"
#include "type.h"
#include "adc.h"

/*****************************************************************************
** Function name:               ADCInit
**
** Descriptions:                initialize ADC channel
**
** parameters:                  ADC clock rate
** Returned value:              None
**
*****************************************************************************/
void ADCInit( uint32_t ADC_Clk )
{
  /* Disable Power down bit to the ADC block. */
  LPC_SYSCON->PDRUNCFG &= ~(0x1<<4);

  /* Enable AHB clock to the ADC. */
  LPC_SYSCON->SYSAHBCLKCTRL |= (1<<13);

  /* Set pin-mux correct for ADC-IN0, -IN1, -IN2 and –IN3 */
  LPC_IOCON->JTAG_TDI_PIO0_11 &= ~0x8F;
  LPC_IOCON->JTAG_TDI_PIO0_11 |= 0x02;    /* ADC IN0 */
  LPC_IOCON->JTAG_TMS_PIO1_0  &= ~0x8F;
  LPC_IOCON->JTAG_TMS_PIO1_0  |= 0x02;    /* ADC IN1 */
  LPC_IOCON->JTAG_TDO_PIO1_1  &= ~0x8F;
  LPC_IOCON->JTAG_TDO_PIO1_1  |= 0x02;    /* ADC IN2 */
  LPC_IOCON->JTAG_nTRST_PIO1_2 &= ~0x8F;
  LPC_IOCON->JTAG_nTRST_PIO1_2 |= 0x02;   /* ADC IN3 */

  LPC_ADC->CR =
    ( 0x01 << 0 ) |   /* SEL=1, select channel 0~7 on ADC0 */
                      /* CLKDIV = Fpclk / 1000000 - 1 */
    (((SystemCoreClock/LPC_SYSCON->SYSAHBCLKDIV)/ADC_Clk-1)<<8) |
    ( 0x0 << 16 ) |   /* BURST = 0, no BURST, software controlled */
    ( 0x0 << 17 ) |   /* CLKS = 0, 11 clocks/10 bits */
    ( 0x0 << 24 ) |   /* START = 0 A/D conversion stops */
    ( 0x0 << 27 );    /* EDGE = 0 (CAP/MAT singal falling,trigger A/D conversion) */
}

/*****************************************************************************
** Function name:               getADC
**
** Descriptions:                Read ADC channel
**
** parameters:                  Channel number
** Returned value:              Value read
**
*****************************************************************************/
uint32_t getADC( uint8_t channelNum )
{
  uint32_t regVal, ADC_Data;

  /* channel number is 0 through 3 */
  if ( channelNum > AIN3 )
    channelNum = AIN0;         /* reset channel number to 0 */
  LPC_ADC->CR &= 0xFFFFFF00;
  LPC_ADC->CR |= (1 << 24) | (1 << channelNum);
                                /* switch channel,start A/D convert */
  while ( 1 )                   /* wait until end of A/D convert */
  {
#if 1
    if ((LPC_ADC->GDR & 0x80000000) != 0)
    {
      regVal = LPC_ADC->GDR;
      break;
    }
#else
#define ADC_OFFSET   0x10
#define ADC_INDEX    4
#define ADC_DONE     0x80000000
    regVal = *(volatile unsigned long *)(LPC_ADC_BASE + ADC_OFFSET + ADC_INDEX * channelNum);
    /* read result of A/D conversion */
    if ( regVal & ADC_DONE )
    {
      break;
    }
#endif
  }

  LPC_ADC->CR &= 0xF8FFFFFF;    /* stop ADC now */
  ADC_Data = ( regVal >> 6 ) & 0x3FF;
  return ( ADC_Data );  /* return A/D conversion value */
}
