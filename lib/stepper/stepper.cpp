#include <Arduino.h>
#include "stepper.h"

static Stepper_Status status=Stepper_Continued_Control;
static int64_t MinLocation=-99999;
static int64_t MaxLocation=99999;
static int64_t location=0;//
static int64_t targetlocation=0;
static Stepper_Dir dir=Stepper_Stop;


void Stepper_SetMaxLocation(int64_t input){MaxLocation=input;}
void Stepper_SetMinLocation(int64_t input){MinLocation=input;}

void Stepper_Init(void){
	Defined_PWM_Init();
	//and the dir pin
    pinMode(STEPPER_DIR_PIN,OUTPUT);
    digitalWrite(STEPPER_DIR_PIN,LOW);
}

void Stepper_ChangeDir(Stepper_Dir input){
	if(status==Stepper_Continued_Control)
		dir=input;
	//outside can change the dir only if under Stepper_Continued_Control mode
}

void Stepper_SetMode(Stepper_Status inputstatus){
	status=inputstatus;
}

void Stepper_SetTargetLocation(int64_t inputlocation){
    if(status==Stepper_Target_Location)
		targetlocation=inputlocation;
}

int64_t Stepper_Returnlocation(void){
	return location;
}

Stepper_Dir Stepper_Returndir(void){
	return dir;
}
	
	
	
void Stepper_Operate(void){
    if(status==Stepper_Target_Location){
        if(targetlocation>location)
            dir=Stepper_Up;
        else if(targetlocation<location)
            dir=Stepper_Down;
        else
            dir=Stepper_Stop;
    }
    if(dir==Stepper_Stop){
    ledcWrite(STEPPER_PWM_CHANNEL,0);
    }else if(dir==Stepper_Up){
        digitalWrite(STEPPER_DIR_PIN,LOW);
        if(location<MaxLocation){
            ledcWrite(STEPPER_PWM_CHANNEL,STEPPERARR/2);
            location+=1;
        }else{
            ledcWrite(STEPPER_PWM_CHANNEL,0);
        }
    }else if(dir==Stepper_Down){
        digitalWrite(STEPPER_DIR_PIN,HIGH);
        if(location>MinLocation){
            ledcWrite(STEPPER_PWM_CHANNEL,STEPPERARR/2);
            location-=1;
        }else{
            ledcWrite(STEPPER_PWM_CHANNEL,0);
        }
    }
}
