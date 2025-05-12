#include "servo.h"
#include <Arduino.h>
static uint16_t Servo1_compare=SERVO1_MINSTEP;
static uint16_t Servo2_compare=SERVO2_MINSTEP;
static uint16_t Servo3_compare=SERVO3_MAXSTEP;
static Servo_Status status=SERVO_Continue_Control;
void SERVO_Init(void){
    Defined_PWM_Init();
}

void Servo_SetStatus(Servo_Status input){
    status=input;
}

void Servo_SetTarget(uint16_t Servo1Input,uint16_t Servo2Input){
//set input ==0 if you want to remain the previous one
//the controller could operate servo3 under both status, so this function will not include servo3
	if(status==SERVO_Target_Angle){
		if(Servo1Input!=0&&Servo1Input>=SERVO1_MINSTEP&&Servo1Input<=SERVO1_MAXSTEP){
			Servo1_compare=Servo1Input;
		}
		if(Servo2Input!=0&&Servo2Input>=SERVO2_MINSTEP&&Servo2Input<=SERVO2_MAXSTEP){
			Servo2_compare=Servo2Input;
		}
	}
}

void Servo_Operate(Servo_Dir servo1dir,Servo_Dir servo2dir,Servo_Dir servo3dir,
    uint32_t servo1speed,uint32_t servo2speed,uint32_t servo3speed){
	//in this project servo3 doesn't have speed control, but for compatibility it's included
	if(status==SERVO_Continue_Control){//only in continue control mode can the controller operate servo1/2
		if(servo1dir==SERVO_CLKWISE){
			Servo1_compare+=servo1speed;
			if(Servo1_compare>SERVO1_MAXSTEP)
				Servo1_compare=SERVO1_MAXSTEP;	
		}else if (servo1dir==SERVO_COUNTERCLKWISE){
			Servo1_compare-=servo1speed;
			if(Servo1_compare<SERVO1_MINSTEP)
				Servo1_compare=SERVO1_MINSTEP;
		}else if(servo1dir==SERVO_STOP){
		}
		ledc_set_duty(LEDC_LOW_SPEED_MODE,SERVO1_PWM_CHANNEL,Servo1_compare);
		ledc_update_duty(LEDC_LOW_SPEED_MODE,SERVO1_PWM_CHANNEL);
		

		if(servo2dir==SERVO_CLKWISE){
			Servo2_compare+=servo2speed;
			if(Servo2_compare>SERVO2_MAXSTEP)
            Servo2_compare=SERVO2_MAXSTEP;			
		}else if (servo2dir==SERVO_COUNTERCLKWISE){
			Servo2_compare-=servo2speed;
			if(Servo2_compare<SERVO2_MINSTEP)
            Servo2_compare=SERVO2_MINSTEP;
		}else if(servo2dir==SERVO_STOP){
		}
		ledc_set_duty(LEDC_LOW_SPEED_MODE,SERVO2_PWM_CHANNEL,Servo2_compare);
		ledc_update_duty(LEDC_LOW_SPEED_MODE,SERVO2_PWM_CHANNEL);
	}else if(status==SERVO_Target_Angle){//servo1/2 is determined by Servo_SetTarget
		if(Servo1_compare>=SERVO1_MINSTEP&&Servo1_compare<=SERVO1_MAXSTEP)//for security
			ledc_set_duty(LEDC_LOW_SPEED_MODE,SERVO1_PWM_CHANNEL,Servo1_compare);
			ledc_update_duty(LEDC_LOW_SPEED_MODE,SERVO1_PWM_CHANNEL);
		if(Servo2_compare>=SERVO2_MINSTEP&&Servo2_compare<=SERVO2_MAXSTEP)
			ledc_set_duty(LEDC_LOW_SPEED_MODE,SERVO2_PWM_CHANNEL,Servo2_compare);
			ledc_update_duty(LEDC_LOW_SPEED_MODE,SERVO2_PWM_CHANNEL);
	}
	
	if(servo3dir==SERVO_CLKWISE){//servo3 is always controlled by the controller
		Servo3_compare+=servo3speed;
		if(Servo3_compare>SERVO3_MAXSTEP)
		Servo3_compare=SERVO3_MAXSTEP;
		
	}else if (servo3dir==SERVO_COUNTERCLKWISE){
		Servo3_compare-=servo3speed;
		if(Servo3_compare<SERVO3_MINSTEP)
		Servo3_compare=SERVO3_MINSTEP;
	}else if(servo3dir==SERVO_STOP){
	}
	ledc_set_duty(LEDC_LOW_SPEED_MODE,SERVO3_PWM_CHANNEL,Servo3_compare);
	ledc_update_duty(LEDC_LOW_SPEED_MODE,SERVO3_PWM_CHANNEL);
	
}

uint16_t Servo_ReturnCompare(ledc_channel_t chan){
	return ledcRead(chan);
}
