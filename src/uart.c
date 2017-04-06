/*****************************************************************************
 *   Placeholder for UART related functions.
 *   Part of the proposed solutions for LPCXpresso Experiment Kit
 *
 *   Copyright(C) 2013, Embedded Artists AB
 *   All rights reserved.
 *
 ******************************************************************************/

#include "LPC11xx.h"
#include "type.h"
#include "uart.h"

/*****************************************************************************
** Function name:  UARTInit
**
** Descriptions:   Initialize UART0 port, setup pin select,
**                 clock, parity, stop bits, FIFO, etc.
**
** parameters:     UART baudrate
** Returned value: None
**
*****************************************************************************/
void UARTInit(uint32_t baudrate)
{
  uint32_t Fdiv;
  uint32_t regVal;

  LPC_IOCON->PIO1_6 &= ~0x07;        /*  UART I/O config */
  LPC_IOCON->PIO1_6 |= 0x01;         /* UART RXD */
  LPC_IOCON->PIO1_7 &= ~0x07;
  LPC_IOCON->PIO1_7 |= 0x01;         /* UART TXD */

  /* Enable UART clock */
  LPC_SYSCON->SYSAHBCLKCTRL |= (1<<12);
  LPC_SYSCON->UARTCLKDIV = 0x1;      /* divided by 1 */

  LPC_UART->LCR = 0x83;              /* 8 bits, no Parity, 1 Stop bit */
  regVal = LPC_SYSCON->UARTCLKDIV;
  Fdiv = (((SystemCoreClock/LPC_SYSCON->SYSAHBCLKDIV)/regVal)/16)/baudrate;

  LPC_UART->DLM = Fdiv / 256;
  LPC_UART->DLL = Fdiv % 256;
  LPC_UART->LCR = 0x03;   /* DLAB = 0 */
  LPC_UART->FCR = 0x07;   /* Enable and reset TX and RX FIFO. */

  /* Read to clear the line status. */
  regVal = LPC_UART->LSR;

  /* Ensure a clean start, no data in either TX or RX FIFO. */
  while ( (LPC_UART->LSR & (LSR_THRE|LSR_TEMT)) != (LSR_THRE|LSR_TEMT) );
  while ( LPC_UART->LSR & LSR_RDR )
  {
  regVal = LPC_UART->RBR; /* Dump data from RX FIFO */
  }

  return;
}

/*****************************************************************************
 ** Function name:  UARTSendChar
 **
 ** Descriptions:   Send a byte/char of data to the UART 0 port
 **
 ** parameters:     byte to send
 ** Returned value: None
 **
 *****************************************************************************/
void UARTSendChar(uint8_t toSend)
{
  /* THRE status, contain valid data */
  while ( !(LPC_UART->LSR & LSR_THRE) )
    ;
  LPC_UART->THR = toSend;
}

/*****************************************************************************
 ** Function name:  UARTSendString
 **
 ** Descriptions:   Send a null-terminated string to UART 0 port
 **
 ** parameters:     byte to send
 ** Returned value: None
 **
 *****************************************************************************/
void UARTSendString(uint8_t *pStr)
{
  while (*pStr != 0)
    UARTSendChar(*pStr++);

}

/*****************************************************************************
 ** Function name:  UARTSendBuffer
 **
 ** Descriptions:   Send a number of bytes/chars of data to UART 0 port
 **
 ** parameters:     byte to send
 ** Returned value: None
 **
 *****************************************************************************/
void UARTSendBuffer(uint8_t *pBuf, uint16_t length)
{
  while (length-- > 0)
    UARTSendChar(*pBuf++);
}

/*****************************************************************************
 ** Function name:  UARTReceive
 **
 ** Descriptions:   Receive a block of data from the UART 0 port based
 **                 on the data length
 **
 ** parameters:     buffer pointer, data length
 ** Returned value: Number of received bytes
 **
 *****************************************************************************/
uint32_t UARTReceive(uint8_t *buffer, uint32_t length, uint32_t blocking)
{
  uint32_t recvd = 0;
  uint32_t toRecv = length;

  if (blocking) {
    while (toRecv) {
      /* wait for data */
      while (!(LPC_UART->LSR & LSR_RDR));

      *buffer++ = LPC_UART->RBR;
      recvd++;
      toRecv--;
    }
  }
  else {
    while (toRecv) {
      /* break if no data */
      if (!(LPC_UART->LSR & LSR_RDR)) {
        break;
      }

      *buffer++ = LPC_UART->RBR;
      recvd++;
      toRecv--;
    }
  }
  return recvd;
}
