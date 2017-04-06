/*****************************************************************************
 *   Placeholder for board related defines
 *
 *   Copyright(C) 2013, Embedded Artists AB
 *   All rights reserved.
 *
 ******************************************************************************/
#ifndef __BOARD_H__
#define __BOARD_H__

// Create defines for simpler access of LED1-LED8
#define LED1_PORT    PORT0     //GPIO_4-LED-SSEL
#define LED1_PIN     2
#define LED2_PORT    PORT2     //GPIO_8-LED-SSEL
#define LED2_PIN     0
#define LED3_PORT    PORT2     //GPIO_9-LED-SSEL
#define LED3_PIN     1
#define LED4_PORT    PORT2     //GPIO_10-LED-CA1
#define LED4_PIN     2
#define LED5_PORT    PORT2     //GPIO_31-LED-CA2
#define LED5_PIN     3
#define LED6_PORT    PORT3     //GPIO_23-LED
#define LED6_PIN     2
#define LED7_PORT    PORT3     //GPIO_22-LED
#define LED7_PIN     1
#define LED8_PORT    PORT3     //GPIO_21-LED
#define LED8_PIN     0

#define LEDR_PORT    PORT1     //GPIO_28-PWM
#define LEDR_PIN     9
#define LEDG_PORT    PORT1     //GPIO_29-PWM
#define LEDG_PIN     10
#define LEDB_PORT    PORT1     //GPIO_30-PWM
#define LEDB_PIN     11

#define LED_ON       0    //Low output turn LED on
#define LED_OFF      1    //High output turn LED off

// Create define for simpler access of push-button
#define SW_PRESSED   0          //Push-button is pressed when input is low

#define SW1_PIN      1
#define SW1_PORT     PORT0
#define SW1_PORT_REG LPC_GPIO0->DATA

#define SW2_PIN      5
#define SW2_PORT     PORT1
#define SW2_PORT_REG LPC_GPIO1->DATA

#define SW3_PIN      4
#define SW3_PORT     PORT1
#define SW3_PORT_REG LPC_GPIO1->DATA

#define SW4_PIN      8
#define SW4_PORT     PORT1
#define SW4_PORT_REG LPC_GPIO1->DATA

#define SW5_PIN      7
#define SW5_PORT     PORT2
#define SW5_PORT_REG LPC_GPIO2->DATA

#define QA_PIN       10
#define QA_PORT      PORT2
#define QA_PORT_REG  LPC_GPIO2->DATA

#define QB_PIN       3
#define QB_PORT      PORT3
#define QB_PORT_REG  LPC_GPIO3->DATA

// Create define for simpler access of buzzer
#define BUZZ_PIN      7
#define BUZZ_PORT     PORT0
#define BUZZ_ON       0
#define BUZZ_OFF      1

// Create define for simpler access of 7-segments display
#define DIG1_PORT   PORT2    //GPIO_10-LED-CA1
#define DIG1_PIN    2
#define DIG2_PORT   PORT2    //GPIO_31-LED-CA2
#define DIG2_PIN    3

#endif /* __BOARD_H__ */
