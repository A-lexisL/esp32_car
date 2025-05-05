#ifndef SERVO_H
#define SERVO_H
#include <cmath>
#include "PWM.h"
#define SERVO_ARR (pow(2,(int)SERVO_PWM_RESOLUTION))
/*
servo1: arm servo; servo2: wrist servo; servo3: claw servo;
*/
//410< <2048
#define SERVO1_MINSTEP 880
#define SERVO1_MAXSTEP 1957
#define SERVO2_MINSTEP 482
#define SERVO2_MAXSTEP 2048
#define SERVO3_MINSTEP 865
#define SERVO3_MAXSTEP 1730
#define SERVO1_STANDARDSTEP 20
#define SERVO2_STANDARDSTEP 20
#define SERVO3_STANDARDSTEP 50
enum Servo_Dir{SERVO_CLKWISE,SERVO_COUNTERCLKWISE,SERVO_STOP};
enum Servo_Status{SERVO_Continue_Control,SERVO_Target_Angle};
void SERVO_Init(void);
void Servo_SetStatus(Servo_Status input);
void Servo_SetTarget(uint16_t Servo1Input=0,uint16_t Servo2Input=0);
//set input ==0 if you want to remain the previous one
void Servo_Operate(Servo_Dir servo1dir,Servo_Dir servo2dir,Servo_Dir servo3dir,
    uint32_t servo1speed=SERVO1_STANDARDSTEP,uint32_t servo2speed=SERVO2_STANDARDSTEP,uint32_t servo3speed=SERVO3_STANDARDSTEP);
uint16_t Servo_ReturnCompare(ledc_channel_t chan);
#endif
