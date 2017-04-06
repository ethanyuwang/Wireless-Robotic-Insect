/*
 * insectBot.cpp
 *
 *  Created on: Mar 6, 2016
 *      Author: yuxiang
 */
#include "insectBot.h"


void insectSetUp()
{
	initPWM(20000);        /* Setup to generate a PWM signal with cycle time 20ms */
	updatePWM1000(front, centerPos);  /* Update PWM output to midscale = 7.5% */
	updatePWM1000(rear, centerPos);  /* Update PWM output to midscale = 7.5% */
	startPWM();
}

void insectGoForward(uint32_t *currentState)
{
	  if (*currentState > 3)
		  *currentState = 0;

	  switch(*currentState)
		   {
		   case 0:
			   	   updatePWM1000(front, frontRightUp);
			   	   updatePWM1000(rear, backLeftForward);
			   	   delayMS(110);
			   	   ++*currentState;
		           break;
		   case 1:
			   	   updatePWM1000(front, centerPos);
			   	   updatePWM1000(rear, centerPos);
			   	   delayMS(90);
			   	   ++*currentState;
		           break;
		   case 2:
				   updatePWM1000(front, frontLeftUp);
				   updatePWM1000(rear, backRightForward);
				   delayMS(110);
				   ++*currentState;
		           break;
		   case 3:
				   updatePWM1000(front, centerPos);
				   updatePWM1000(rear, centerPos);
				   delayMS(90);
				   delayMS(walkSpeed);
				   ++*currentState;
		           break;
		   }
}

void insectGoBackRight(uint32_t *currentState)
{
	  if (*currentState > 3)
		  *currentState = 0;

	  switch(*currentState)
		   {
		   case 0:
			   	   updatePWM1000(front, frontRightUp);
			   	   updatePWM1000(rear, backRightForward-6);
			   	   delayMS(110);
				   ++*currentState;
		           break;
		   case 1:
			   	   updatePWM1000(front, centerPos);
			   	   updatePWM1000(rear, centerPos-6);
			   	   delayMS(90);
				   ++*currentState;
		           break;
		   case 2:
				   updatePWM1000(front, frontLeftUp);
				   updatePWM1000(rear, backLeftForward-6);
				   delayMS(110);
				   ++*currentState;
		           break;
		   case 3:
				   updatePWM1000(front, centerPos);
				   updatePWM1000(rear, centerPos);
				   delayMS(90);
				   ++*currentState;
		           break;
		   }
}

void insectTurnLeft(uint32_t *currentState)
{
	  if (*currentState > 3)
		  *currentState = 0;

	  switch(*currentState)
		   {
		   case 0:
			   	   updatePWM1000(front, frontRightUp);
			   	   updatePWM1000(rear, backTurnLeftForward);
			   	   delayMS(110);
				   ++*currentState;
		           break;
		   case 1:
			   	   updatePWM1000(front, centerTurnPos);
			   	   updatePWM1000(rear, centerTurnPos);
			   	   delayMS(90);
				   ++*currentState;
		           break;
		   case 2:
			   	   updatePWM1000(front, frontTurnLeftUp);
			   	   updatePWM1000(rear, backTurnRightForward);
				   delayMS(110);
				   ++*currentState;
		           break;
		   case 3:
			   	   updatePWM1000(front, centerTurnPos);
			   	   updatePWM1000(rear, centerTurnPos);
				   delayMS(20);
				   ++*currentState;
		           break;
		   }
}

void insectStop()
{
	updatePWM1000(front, centerPos);
	updatePWM1000(rear, centerPos);
	delayMS(110);
}
