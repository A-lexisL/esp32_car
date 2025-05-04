#ifndef MOTOR_H
#define MOTOR_H
#include <cstdint>
#include <cmath>
#include "PWM.h"
#define MOTORARR (pow(2,(int)MOTOR_PWM_RESOLUTION))

enum VehicleMovement{
	Vehicle_Stop,
	Vehicle_Forward,
	Vehicle_Backward,
	Vehicle_Right_Translation,
	Vehicle_Left_Translation,
	Vehicle_Right_Rotation,
	Vehicle_Left_Rotation,
	Vehicle_Right_Forward,
	Vehicle_Left_Backward,
	Vehicle_Right_Backward,
	Vehicle_Left_Forward
};

enum VehicleHead{
    ARMHEAD,
    BOARDHEAD
};



#define Motor1_Dir_Pin1	7
#define Motor1_Dir_Pin2 15    
#define Motor2_Dir_Pin1 17
#define Motor2_Dir_Pin2 18
#define Motor3_Dir_Pin1 10
#define Motor3_Dir_Pin2 11
#define Motor4_Dir_Pin1 13
#define Motor4_Dir_Pin2 14
//only temporary, need specification!!
void Motor_Init(void);
void Motor1_Operate(int32_t speed);
void Motor2_Operate(int32_t speed);
void Motor3_Operate(int32_t speed);
void Motor4_Operate(int32_t speed);
void Vehicle_Move(uint8_t status,enum VehicleMovement move,uint16_t speed);
#endif
