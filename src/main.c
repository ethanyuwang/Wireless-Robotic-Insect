/*****************************************************************************
 *   The proposed solution for LPCXpresso Experiment Kit, Lab 10c
 *
 *   Copyright(C) 2013, Embedded Artists AB
 *   All rights reserved.
 *
 ******************************************************************************/

#include "LPC11xx.h"
#include "type.h"
#include "board.h"
#include "gpio.h"
#include "delay.h"
#include "adc.h"
#include "pwm.h"
#include "uart.h"
#include "insectBot.h"

#define SCK_PORT    PORT2    //GPIO_3-SCK
#define SCK_PIN     11
#define MOSI_PORT   PORT0    //GPIO_1-MOSI
#define MOSI_PIN    9
#define SSEL_PORT   PORT0    //GPIO_4-LED-SSEL
#define SSEL_PIN    2

#define SEG_A   0x01
#define SEG_B   0x02
#define SEG_C   0x04
#define SEG_D   0x08
#define SEG_E   0x10
#define SEG_F   0x20
#define SEG_G   0x40

const uint8_t segments[10] = {
            SEG_B | SEG_C | SEG_D | SEG_E | SEG_F        ,  //0,U = B,C,D,E,F
    SEG_A | SEG_B |                 SEG_E | SEG_F | SEG_G,  //1,P = A,B,E,F,G
            SEG_B | SEG_C | SEG_D | SEG_E |         SEG_G,  //2,d = B, C, D, E, G
            		SEG_C | SEG_D | SEG_E |         SEG_G,  //3,O = C,D,E,G
                            SEG_D | SEG_E | SEG_F        ,  //4,L = D, E, F
    SEG_A |                         SEG_E | SEG_F | SEG_G,  //5,F = A,E,F,G
                                    SEG_E | SEG_F        ,  //6,I = E,F,
};

void updateShiftReg( uint8_t segments )
{
  uint8_t bitCnt;

  //Pull SCK and MOSI low, pull SSEL low
  GPIOSetValue( SCK_PORT, SCK_PIN, 0);
  GPIOSetValue( MOSI_PORT, MOSI_PIN, 0);
  GPIOSetValue( SSEL_PORT, SSEL_PIN, 0);

  //wait 1us
  delayUS(1);

  //Loop througth all eight bits
  for (bitCnt = 0; bitCnt < 8; bitCnt++)
  {
    //output MOSI value (bit 7 of “segments”)
    if (segments & 0x80)
      GPIOSetValue( MOSI_PORT, MOSI_PIN, 1);
    else
      GPIOSetValue( MOSI_PORT, MOSI_PIN, 0);

    //wait 1us
    delayUS(1);

    //pull SCK high
    GPIOSetValue( SCK_PORT, SCK_PIN, 1);

    //wait 1us
    delayUS(1);

    //pull SCK low
    GPIOSetValue( SCK_PORT, SCK_PIN, 0);

   //shift “segments”
    segments = segments << 1;
  }

  //Pull SSEL high
  GPIOSetValue( SSEL_PORT, SSEL_PIN, 1);
}

int main (void)
{
  uint8_t state = 0;

  //setup pins for controlling 7-segment display
  GPIOSetDir( DIG1_PORT, DIG1_PIN, GPIO_OUTPUT);
  GPIOSetValue( DIG1_PORT, DIG1_PIN, 1);
  GPIOSetDir( DIG2_PORT, DIG2_PIN, GPIO_OUTPUT);
  GPIOSetValue( DIG2_PORT, DIG2_PIN, 1);

  GPIOSetDir( SCK_PORT, SCK_PIN, GPIO_OUTPUT);
  GPIOSetValue( SCK_PORT, SCK_PIN, 0);
  GPIOSetDir( MOSI_PORT, MOSI_PIN, GPIO_OUTPUT);
  GPIOSetValue( MOSI_PORT, MOSI_PIN, 0);
  GPIOSetDir( SSEL_PORT, SSEL_PIN, GPIO_OUTPUT);
  GPIOSetValue( SSEL_PORT, SSEL_PIN, 1);

  //Set SW1/SW2/SW3/SW5 pins as inputs
  GPIOSetDir( SW1_PORT, SW1_PIN, GPIO_INPUT);
  GPIOSetDir( SW2_PORT, SW2_PIN, GPIO_INPUT);
  GPIOSetDir( SW3_PORT, SW3_PIN, GPIO_INPUT);
  GPIOSetDir( SW5_PORT, SW5_PIN, GPIO_INPUT);

  //Extra, turn buzzer pin to input
  GPIOSetDir( BUZZ_PORT, BUZZ_PIN, GPIO_OUTPUT);
  GPIOSetValue( BUZZ_PORT, BUZZ_PIN, BUZZ_OFF);

  //Initialize ADC peripheral and pin-mixing
  ADCInit(4500000);  //4.5MHz ADC clock

  //get initial value
  //analogValue = getADC(AIN0);   /* AIN0 = trimming pot for servo position */

  insectSetUp();
  state = 0;
  uint32_t currentState = 0;

  //initialize the UART to 9600bps 8N1
  UARTInit(9600);

  UARTSendString((uint8_t*)"\nPlease enter 'w' for going forward, 'a' for going left, 'd' for going right back, 's' for stop");

  //enter forever loop - uart echo application
  while(1)
  {
    uint8_t rxChar;
    UARTReceive(&rxChar, 1, FALSE);

    printf("\nReceived: %c", rxChar);

   //check if char has been receiveds
    if (UARTReceive(&rxChar, 1, FALSE) == 1)
    {
    	if (rxChar == 'w')
    		state=1;
    	else if (rxChar == 'a')
    		state=5;
    	else if (rxChar == 's')
    		state=3;
    	else if (rxChar == 'd')
    		state=2;
    	rxChar = '0';
    }

	  if (currentState > 3)
		    currentState = 0;

	  if (GPIOGetValue(SW1_PORT, SW1_PIN) == SW_PRESSED)
	      {
	        state=1;
	        //wait until push-button is released
	        while(GPIOGetValue(SW2_PORT, SW2_PIN) == SW_PRESSED)
	          ;
	      }
	  if (GPIOGetValue(SW2_PORT, SW2_PIN) == SW_PRESSED)
	      {
	        state=2;
	        //wait until push-button is released
	        while(GPIOGetValue(SW2_PORT, SW2_PIN) == SW_PRESSED)
	          ;
	      }
	  if (GPIOGetValue(SW3_PORT, SW3_PIN) == SW_PRESSED)
	      {
	        state=3;
	        //wait until push-button is released
	        while(GPIOGetValue(SW2_PORT, SW2_PIN) == SW_PRESSED)
	          ;
	      }
	  if (GPIOGetValue(SW5_PORT, SW5_PIN) == SW_PRESSED)
	      {
	        state=5;
	        //wait until push-button is released
	        while(GPIOGetValue(SW2_PORT, SW2_PIN) == SW_PRESSED)
	          ;
	      }

	  switch(state)
	   {
	   case 1:
		   	   GPIOSetValue( DIG1_PORT, DIG1_PIN, 1);
		       updateShiftReg(~segments[1]);
		       GPIOSetValue( DIG2_PORT, DIG2_PIN, 0);
		       //ROBOT
	           insectGoForward(&currentState);
	           //second digit
		       GPIOSetValue( DIG2_PORT, DIG2_PIN, 1);
		       updateShiftReg(~segments[0]);
		       GPIOSetValue( DIG1_PORT, DIG1_PIN, 0);
		       delayMS(20);
	           break;
	   case 2:
		   	   GPIOSetValue( DIG1_PORT, DIG1_PIN, 1);
		       updateShiftReg(~segments[3]);
		       GPIOSetValue( DIG2_PORT, DIG2_PIN, 0);
		   	   //ROBOT
	           insectGoBackRight(&currentState);
		       //second digit
		       GPIOSetValue( DIG2_PORT, DIG2_PIN, 1);
		       updateShiftReg(~segments[2]);
		       GPIOSetValue( DIG1_PORT, DIG1_PIN, 0);
		       delayMS(20);
	           break;
	   case 3:
		   	   GPIOSetValue( DIG1_PORT, DIG1_PIN, 1);
		       updateShiftReg(~segments[2]);
		       GPIOSetValue( DIG2_PORT, DIG2_PIN, 0);
		   	   //ROBOT
	           insectStop();
	           //second digit
	           GPIOSetValue( DIG2_PORT, DIG2_PIN, 1);
	           updateShiftReg(~segments[6]);
	           GPIOSetValue( DIG1_PORT, DIG1_PIN, 0);
	           delayMS(20);
	           break;
	   case 5:
		   	   GPIOSetValue( DIG1_PORT, DIG1_PIN, 1);
		       updateShiftReg(~segments[5]);
		       GPIOSetValue( DIG2_PORT, DIG2_PIN, 0);
	       	   //ROBOT
	           insectTurnLeft(&currentState);
		       //second digit
		       GPIOSetValue( DIG2_PORT, DIG2_PIN, 1);
		       updateShiftReg(~segments[4]);
		       GPIOSetValue( DIG1_PORT, DIG1_PIN, 0);
		       delayMS(20);
	           break;
	   }
  }

  return 0;
}
