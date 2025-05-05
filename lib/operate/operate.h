#ifndef OPERATION_H
#define OPERATION_H

#include "bleretro32/bleretro32.h"
#include "Servo.h"
#include "motor.h"
#include "stepper.h"
#include "timer.h"
enum Presetlocation{
	Preset_None,
	Preset_Basketlocation,
	Preset_Picklocation,
	Preset_Preparelocation//this preset is deserted
};
enum ControlMode{
	CalibrateMaxLocationMode,
	CalibrateMinLocationMode,
	CalibratePickLocationMode,
	CalibrateBasketLocationMode,
	OperateMode
};
enum WristHorizon{
    WristHorizonEnable,
    WristHorizonDisable
};

#define JOYCON_DEADZONE 5000
#define TRG_DEADZONE 10
inline uint32_t RadiusToServoSpeed(double r){return (uint32_t)(r-JOYCON_DEADZONE)/270;}
inline uint16_t RadiusToMotorSpeed(double r){return ((uint16_t)(r-JOYCON_DEADZONE)/220<127?(uint16_t)(r-JOYCON_DEADZONE)/220:127);}
inline uint16_t TrgToMotorSpeed(uint32_t trg){return (trg+1)/8-1;}
ControlMode ReturnControlMode(void);
uint8_t ReturnConfirmCount(void);
VehicleHead ReturnFacingStatus(void);
WristHorizon ReturnWristStatus(void);
uint8_t ReturnTargetArmLocation(void);
void Operate_Init(void);
void Calibrate(void);
void InterpretController(void);
//the status button(preset,deletepreset,wristhorizontal,confirm,changefacing) are not included
void Operate(void);
void OperateReport(void);
#endif
