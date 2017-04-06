/*
 * insectBot.h
 *
 *  Created on: Mar 6, 2016
 *      Author: yuxiang
 */

#ifndef INSECTBOT_H_
#define INSECTBOT_H_
#include "delay.h"
#include "pwm.h"

//global variables:
#define  front                   0
#define  rear                    1
#define  walkSpeed               50
#define  centerPos               90
#define  frontRightUp            70
#define  frontLeftUp             110
#define  backRightForward        70
#define  backLeftForward         110
#define  centerTurnPos           81
#define  frontTurnRightUp        70
#define  frontTurnLeftUp         110
#define  backTurnRightForward    70
#define  backTurnLeftForward     110


void insectSetUp();
void insectGoForward(uint32_t *currentSate);
void insectGoBackRight(uint32_t *currentSate);
void insectTurnLeft(uint32_t *currentSate);
void insectStop();
#endif /* INSECTBOT_H_ */
