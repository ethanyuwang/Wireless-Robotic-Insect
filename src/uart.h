/*****************************************************************************
 *   Placeholder for UART related functions.
 *   Part of the proposed solutions for LPCXpresso Experiment Kit
 *
 *   Copyright(C) 2013, Embedded Artists AB
 *   All rights reserved.
 *
 ******************************************************************************/
#ifndef __UART_H__
#define __UART_H__

#include "type.h"

#define LSR_RDR    0x01
#define LSR_OE     0x02
#define LSR_PE     0x04
#define LSR_FE     0x08
#define LSR_BI     0x10
#define LSR_THRE   0x20
#define LSR_TEMT   0x40
#define LSR_RXFE   0x80

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
void UARTInit(uint32_t baudrate);

/*****************************************************************************
 ** Function name:  UARTSendChar
 **
 ** Descriptions:   Send a byte/char of data to the UART 0 port
 **
 ** parameters:     byte to send
 ** Returned value: None
 **
 *****************************************************************************/
void UARTSendChar(uint8_t toSend);

/*****************************************************************************
 ** Function name:  UARTSendString
 **
 ** Descriptions:   Send a null-terminated string to UART 0 port
 **
 ** parameters:     byte to send
 ** Returned value: None
 **
 *****************************************************************************/
void UARTSendString(uint8_t *pStr);

/*****************************************************************************
 ** Function name:  UARTSendBuffer
 **
 ** Descriptions:   Send a number of bytes/chars of data to UART 0 port
 **
 ** parameters:     byte to send
 ** Returned value: None
 **
 *****************************************************************************/
void UARTSendBuffer(uint8_t *pBuf, uint16_t length);

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
uint32_t UARTReceive(uint8_t *buffer, uint32_t length, uint32_t blocking);

#endif /* __UART_H__ */
