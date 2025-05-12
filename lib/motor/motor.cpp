#include "motor.h"
#include <Arduino.h>
void Motor_Init(void){
	Defined_PWM_Init();
	//and the GPIO for dir pins
	pinMode(Motor1_Dir_Pin1,OUTPUT);
    pinMode(Motor1_Dir_Pin2,OUTPUT);
    pinMode(Motor2_Dir_Pin1,OUTPUT);
    pinMode(Motor2_Dir_Pin2,OUTPUT);
    pinMode(Motor3_Dir_Pin1,OUTPUT);
    pinMode(Motor3_Dir_Pin2,OUTPUT);
    pinMode(Motor4_Dir_Pin1,OUTPUT);
    pinMode(Motor4_Dir_Pin2,OUTPUT);
}

void Motor1_Operate(int32_t speed){
    if(speed<-MOTORARR)
        speed=-MOTORARR;
    else if(speed>MOTORARR)
        speed=MOTORARR;

	if(speed>0){
        digitalWrite(Motor1_Dir_Pin1,HIGH);
        digitalWrite(Motor1_Dir_Pin2,LOW);
		ledc_set_duty(LEDC_LOW_SPEED_MODE,MOTOR1_PWM_CHANNEL,speed);
		ledc_update_duty(LEDC_LOW_SPEED_MODE,MOTOR1_PWM_CHANNEL);
	}else if (speed<0){
		digitalWrite(Motor1_Dir_Pin1,LOW);
        digitalWrite(Motor1_Dir_Pin2,HIGH);
        ledc_set_duty(LEDC_LOW_SPEED_MODE,MOTOR1_PWM_CHANNEL,-speed);
		ledc_update_duty(LEDC_LOW_SPEED_MODE,MOTOR1_PWM_CHANNEL);
	}else{
		ledc_set_duty(LEDC_LOW_SPEED_MODE,MOTOR1_PWM_CHANNEL,0);
		ledc_update_duty(LEDC_LOW_SPEED_MODE,MOTOR1_PWM_CHANNEL);
	}
}

void Motor2_Operate(int32_t speed){
    if(speed<-MOTORARR)
        speed=-MOTORARR;
    else if(speed>MOTORARR)
        speed=MOTORARR;

	if(speed>0){
		digitalWrite(Motor2_Dir_Pin1,HIGH);
        digitalWrite(Motor2_Dir_Pin2,LOW);
        ledc_set_duty(LEDC_LOW_SPEED_MODE,MOTOR2_PWM_CHANNEL,speed);
		ledc_update_duty(LEDC_LOW_SPEED_MODE,MOTOR2_PWM_CHANNEL);
	}else if (speed<0){
		digitalWrite(Motor2_Dir_Pin1,LOW);
        digitalWrite(Motor2_Dir_Pin2,HIGH);
        ledc_set_duty(LEDC_LOW_SPEED_MODE,MOTOR2_PWM_CHANNEL,-speed);
		ledc_update_duty(LEDC_LOW_SPEED_MODE,MOTOR2_PWM_CHANNEL);
	}else{
		ledc_set_duty(LEDC_LOW_SPEED_MODE,MOTOR2_PWM_CHANNEL,0);
		ledc_update_duty(LEDC_LOW_SPEED_MODE,MOTOR2_PWM_CHANNEL);
	}
}

void Motor3_Operate(int32_t speed){
    if(speed<-MOTORARR)
        speed=-MOTORARR;
    else if(speed>MOTORARR)
        speed=MOTORARR;
	if(speed>0){
		digitalWrite(Motor3_Dir_Pin1,HIGH);
        digitalWrite(Motor3_Dir_Pin2,LOW);
        ledc_set_duty(LEDC_LOW_SPEED_MODE,MOTOR3_PWM_CHANNEL,speed);
		ledc_update_duty(LEDC_LOW_SPEED_MODE,MOTOR3_PWM_CHANNEL);
	}else if (speed<0){
		digitalWrite(Motor3_Dir_Pin1,LOW);
        digitalWrite(Motor3_Dir_Pin2,HIGH);
        ledc_set_duty(LEDC_LOW_SPEED_MODE,MOTOR3_PWM_CHANNEL,-speed);
		ledc_update_duty(LEDC_LOW_SPEED_MODE,MOTOR3_PWM_CHANNEL);
	}else{
		ledc_set_duty(LEDC_LOW_SPEED_MODE,MOTOR3_PWM_CHANNEL,0);
		ledc_update_duty(LEDC_LOW_SPEED_MODE,MOTOR3_PWM_CHANNEL);
	}
}

void Motor4_Operate(int32_t speed){
    if(speed<-MOTORARR)
        speed=-MOTORARR;
    else if(speed>MOTORARR)
        speed=MOTORARR;
	if(speed>0){
		digitalWrite(Motor4_Dir_Pin1,HIGH);
        digitalWrite(Motor4_Dir_Pin2,LOW);
        ledc_set_duty(LEDC_LOW_SPEED_MODE,MOTOR4_PWM_CHANNEL,speed);
		ledc_update_duty(LEDC_LOW_SPEED_MODE,MOTOR4_PWM_CHANNEL);
	}else if (speed<0){
		digitalWrite(Motor4_Dir_Pin1,LOW);
        digitalWrite(Motor4_Dir_Pin2,HIGH);
        ledc_set_duty(LEDC_LOW_SPEED_MODE,MOTOR4_PWM_CHANNEL,-speed);
		ledc_update_duty(LEDC_LOW_SPEED_MODE,MOTOR4_PWM_CHANNEL);
	}else{
		ledc_set_duty(LEDC_LOW_SPEED_MODE,MOTOR4_PWM_CHANNEL,0);
		ledc_update_duty(LEDC_LOW_SPEED_MODE,MOTOR4_PWM_CHANNEL);
	}
}


void Motor_Forward(uint16_t speed){
	Motor1_Operate(speed);
	Motor2_Operate(speed);
	Motor3_Operate(speed);
	Motor4_Operate(speed);
}

void Motor_Backward(uint16_t speed){
	Motor1_Operate(-speed);
	Motor2_Operate(-speed);
	Motor3_Operate(-speed);
	Motor4_Operate(-speed);
}

void Motor_RightTranslation(uint16_t speed){
	Motor1_Operate(speed);
	Motor2_Operate(-speed);
	Motor3_Operate(-speed);
	Motor4_Operate(speed);
}

void Motor_LeftTranslation(uint16_t speed){
	Motor1_Operate(-speed);
	Motor2_Operate(speed);
	Motor3_Operate(speed);
	Motor4_Operate(-speed);
}

void Motor_RightRotation(uint16_t speed){
	Motor1_Operate(speed);
	Motor2_Operate(-speed);
	Motor3_Operate(speed);
	Motor4_Operate(-speed);
}

void Motor_LeftRotation(uint16_t speed){
	Motor1_Operate(-speed);
	Motor2_Operate(speed);
	Motor3_Operate(-speed);
	Motor4_Operate(speed);
}

void Motor_RightForward(uint16_t speed){
	Motor1_Operate(speed);
	Motor2_Operate(0);
	Motor3_Operate(0);
	Motor4_Operate(speed);
}

void Motor_LeftBackward(uint16_t speed){
	Motor1_Operate(-speed);
	Motor2_Operate(0);
	Motor3_Operate(0);
	Motor4_Operate(-speed);
}

void Motor_LeftForward(uint16_t speed){
	Motor1_Operate(0);
	Motor2_Operate(speed);
	Motor3_Operate(speed);
	Motor4_Operate(0);
}

void Motor_RightBackward(uint16_t speed){
	Motor1_Operate(0);
	Motor2_Operate(-speed);
	Motor3_Operate(-speed);
	Motor4_Operate(0);
}

void Motor_Stop(void){
	Motor1_Operate(0);
	Motor2_Operate(0);
	Motor3_Operate(0);
	Motor4_Operate(0);
}

void Vehicle_Move(uint8_t status,enum VehicleMovement move,uint16_t speed){
	if(status==ARMHEAD){
		if(move==Vehicle_Stop){
			Motor_Stop();
		}else if(move==Vehicle_Forward){
			Motor_Forward(speed);
		}else if(move==Vehicle_Backward){
			Motor_Backward(speed);
		}else if(move==Vehicle_Right_Translation){
			Motor_RightTranslation(speed);
		}else if(move==Vehicle_Left_Translation){
			Motor_LeftTranslation(speed);
		}else if(move==Vehicle_Right_Rotation){
			Motor_RightRotation(speed);
		}else if(move==Vehicle_Left_Rotation){
			Motor_LeftRotation(speed);
		}else if(move==Vehicle_Right_Forward){
			Motor_RightForward(speed);
		}else if(move==Vehicle_Left_Backward){
			Motor_LeftBackward(speed);
		}else if(move==Vehicle_Right_Backward){
			Motor_RightBackward(speed);
		}else if(move==Vehicle_Left_Forward){
			Motor_LeftForward(speed);
		}
	}else if(status==BOARDHEAD){
		if(move==Vehicle_Stop){
			Motor_Stop();
		}else if(move==Vehicle_Forward){
			Motor_Backward(speed);
		}else if(move==Vehicle_Backward){
			Motor_Forward(speed);
		}else if(move==Vehicle_Right_Translation){
			Motor_LeftTranslation(speed);
		}else if(move==Vehicle_Left_Translation){
			Motor_RightTranslation(speed);
		}else if(move==Vehicle_Right_Rotation){
			Motor_RightRotation(speed);
		}else if(move==Vehicle_Left_Rotation){
			Motor_LeftRotation(speed);
		}else if(move==Vehicle_Right_Forward){
			Motor_LeftBackward(speed);
		}else if(move==Vehicle_Left_Backward){
			Motor_RightForward(speed);
		}else if(move==Vehicle_Right_Backward){
			Motor_LeftForward(speed);
		}else if(move==Vehicle_Left_Forward){
			Motor_RightBackward(speed);
		}
	}
}
