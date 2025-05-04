#ifndef SERVO_H
#define SERVO_H
#include <cmath>
#include "PWM.h"
#define SERVO_ARR (pow(2,(int)SERVO_PWM_RESOLUTION))
//410< <2048
#define SERVO1_MINSTEP 880
#define SERVO1_MAXSTEP 1957
#define SERVO2_MINSTEP 482
#define SERVO2_MAXSTEP 2048
#define SERVO3_MINSTEP 865
#define SERVO3_MAXSTEP 1730
#define SERVO1_ONESTEP 20
#define SERVO2_ONESTEP 20
#define SERVO3_ONESTEP 50
enum Servo_Dir{SERVO_CLKWISE,SERVO_COUNTERCLKWISE,SERVO_STOP};
enum Servo_Status{SERVO_Continue_Control,SERVO_Target_Angle};
void SERVO_Init(void);
void Servo_SetStatus(Servo_Status input);
void Servo_SetTarget(uint16_t Servo1Input,uint16_t Servo2Input);
void Servo_Operate(Servo_Dir servo1dir,Servo_Dir servo2dir,Servo_Dir servo3dir);
uint16_t Servo_ReturnCompare(ledc_channel_t chan);
#endif
