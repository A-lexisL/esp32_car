#ifndef STEPPER_H
#define STEPPER_H
#include<cstdint>
#include <cmath>
#include "PWM.h"
#define STEPPERARR (pow(2,(int)STEPPER_PWM_RESOLOTION)) 
#define STEPPER_DIR_PIN 8
enum Stepper_Dir{Stepper_Stop,Stepper_Up,Stepper_Down};
void Stepper_SetMaxLocation(int64_t input);
void Stepper_SetMinLocation(int64_t input);
void Stepper_Init(void);
int64_t Stepper_Returnlocation(void);
enum Stepper_Dir Stepper_Returndir(void);
enum Stepper_Status{Stepper_Continued_Control,Stepper_Target_Location};
void Stepper_SetMode(Stepper_Status inputstatus);
void Stepper_SetTargetLocation(int64_t intputlocation);
void Stepper_ChangeDir(Stepper_Dir);
#endif
