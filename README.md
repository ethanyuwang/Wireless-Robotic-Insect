# Wireless-Robotic-Insect
This is a LPCxpresso board based robotic insect that's controlled through Bluetooth. The robotic insect is essentially two servo motors, each responsible for two legs of the robot. Jumper wires are used to connect the servo motors to the LPC1115 board. A bluetooth module is added to the LPC1115 and communicates with a PC. Thus the insect is controlled wirelessly through bluetooth. The robotic insect is able to go forward, backward, left, and right. At the meantime the 7 Segment LED to display the current commands.

## Usage

1. Required hardware: 

```
 LPCExpresso LPC1115 board
 Insectbot Kit (http://www.amazon.com/dp/B014MB0SK4?psc=1)
 Bluetooth XBee Module
```

2. To run, connect the servo motors to the LPCxpresso board GPIO ports, XBee module to the UART port, and also XBee module to PC. A serial port communication port is also needed on the PC to send commands. Use w, a,  s, d, on keyboard for going forward, left, back, right respectively.

## Software Design
A single while loop controls the program. The beginning of the loop checks for the current command from PC, and then assign the appropriate movement function to the servo motors. Also at the same time the seven segment display shows letters of U, D, L, R to indicate what command is received.