#include "operate.h"
static enum ControlMode mode=CalibrateMaxLocationMode;
static uint8_t confirmcount=0;

static int64_t STEPPER1_BASKETLOCATION =0;
static int64_t STEPPER1_PICKLOCATION=0;

static enum Presetlocation targetarmlocation=Preset_None;
static VehicleHead Facingstatus=ARMHEAD;
static WristHorizon WristStatus=WristHorizonDisable;

static  Servo_Dir Servo1_Dir=SERVO_STOP;
static  Servo_Dir Servo2_Dir=SERVO_STOP;
static  Servo_Dir Servo3_Dir=SERVO_STOP;
static uint32_t Servo1_speed=0;
static uint32_t Servo2_speed=0;
static  Stepper_Dir Stepper1_Dir =Stepper_Stop;
static enum VehicleMovement movement=Vehicle_Stop;
static uint16_t vehiclespeed=0;

ControlMode ReturnControlMode(void){
	return mode;
}

uint8_t ReturnConfirmCount(void){return confirmcount;}

VehicleHead ReturnFacingStatus(void){return Facingstatus;}
WristHorizon ReturnWristStatus(void){return WristStatus;}

uint8_t ReturnTargetArmLocation(void){return targetarmlocation;}


void Operate_Init(void){
    Defined_Timer_Init();
    SERVO_Init();
    Motor_Init();
    Stepper_Init();
}

void ProceedControlMode(void){
	if(mode==CalibrateMaxLocationMode){
		mode=CalibrateMinLocationMode;
	}else if(mode==CalibrateMinLocationMode){
		mode=CalibratePickLocationMode;
	}else if(mode==CalibratePickLocationMode){
		mode=CalibrateBasketLocationMode;
	}else if(mode==CalibrateBasketLocationMode){
		mode=OperateMode;
	}
}

void Calibrate(void){
	if(ReturnControlMode()==OperateMode){
		return;
	}
	xbox_controller_data_t xboxdata=ReturnControllerData();
	Stepper1_Dir=Stepper_Stop; 
	if(xboxdata.dpad==DPAD_U||xboxdata.dpad==DPAD_UL||xboxdata.dpad==DPAD_UR){
		Stepper1_Dir=Stepper_Up;
	}else if(xboxdata.dpad==DPAD_D||xboxdata.dpad==DPAD_DR||xboxdata.dpad==DPAD_DL){
		Stepper1_Dir=Stepper_Down;
	}
	Stepper_SetMode(Stepper_Continued_Control);
	Stepper_ChangeDir(Stepper1_Dir);
}

void InterpretController(void){
    //the status button(preset,deletepreset,wristhorizontal,confirm,changefacing) are not included
	if(ReturnControlMode()!=OperateMode){
		return;
	}
	xbox_controller_data_t xboxdata=ReturnControllerData();
    XBOX_JoyconLocation xboxjoyconLdata=XBOX_InterpretJoycon(xboxdata,LEFTJOYCON);
    XBOX_JoyconLocation xboxjoyconRdata=XBOX_InterpretJoycon(xboxdata,RIGHTJOYCON);
    //stepper
	Stepper1_Dir=Stepper_Stop; 
	if(xboxdata.dpad==DPAD_U||xboxdata.dpad==DPAD_UL||xboxdata.dpad==DPAD_UR){
		Stepper1_Dir=Stepper_Up;
	}else if(xboxdata.dpad==DPAD_D||xboxdata.dpad==DPAD_DR||xboxdata.dpad==DPAD_DL){
		Stepper1_Dir=Stepper_Down;
	}
	//servo
	if(xboxjoyconRdata.r>=JOYCON_DEADZONE&&xboxjoyconRdata.angle>=-PI*3/4&&xboxjoyconRdata.angle<=-PI/4){
		Servo1_Dir=SERVO_CLKWISE;
        Servo1_speed=RadiusToServoSpeed(xboxjoyconRdata.r);
	}else if(xboxjoyconRdata.r>=JOYCON_DEADZONE&&xboxjoyconRdata.angle>=PI/4&&xboxjoyconRdata.angle<=PI*3/4){
		Servo1_Dir=SERVO_COUNTERCLKWISE;
        Servo1_speed=RadiusToServoSpeed(xboxjoyconRdata.r);
	}else{
		Servo1_Dir=SERVO_STOP;
        Servo1_speed=0;
	}
	
    if(xboxjoyconRdata.r>=JOYCON_DEADZONE){
        if(xboxjoyconRdata.angle>PI*3/4||xboxjoyconRdata.angle<-PI*3/4){
            Servo2_Dir=SERVO_CLKWISE;
            Servo2_speed=RadiusToServoSpeed(xboxjoyconRdata.r);
        }else if(-PI/4<xboxjoyconRdata.angle&&xboxjoyconRdata.angle<PI/4){
            Servo2_Dir=SERVO_COUNTERCLKWISE;
            Servo2_speed=RadiusToServoSpeed(xboxjoyconRdata.r);
        }else{
            Servo2_Dir=SERVO_STOP;
            Servo2_speed=0;
        }
    }
	if(xboxdata.btnA==PRESSED||xboxdata.btnB==PRESSED){
		if(xboxdata.btnA==PRESSED)
			Servo3_Dir=SERVO_CLKWISE;
		else if(xboxdata.btnB==PRESSED)
			Servo3_Dir=SERVO_COUNTERCLKWISE;
	}else{
		Servo3_Dir=SERVO_STOP;
	}
	//motor
    if(xboxjoyconLdata.r>JOYCON_DEADZONE){
        if(xboxjoyconLdata.angle>=-PI*5/8&&xboxjoyconLdata.angle<=-PI*3/8){
            movement=Vehicle_Forward;
        }else if(xboxjoyconLdata.angle>=PI*3/8&&xboxjoyconLdata.angle<=PI*5/8){
            movement=Vehicle_Backward;
        }else if(xboxjoyconLdata.angle>=PI*7/8||xboxjoyconLdata.angle<=-PI*7/8){
            movement=Vehicle_Left_Translation;
        }else if(xboxjoyconLdata.angle>=-PI/8&&xboxjoyconLdata.angle<PI/8){
            movement=Vehicle_Right_Translation;
        }else if(xboxjoyconLdata.angle<-PI/8&&xboxjoyconLdata.angle>-PI*3/8){
            movement=Vehicle_Right_Forward;
        }else if(xboxjoyconLdata.angle<-PI*5/8&&xboxjoyconLdata.angle>-PI*7/8){
            movement=Vehicle_Left_Forward;
        }else if(xboxjoyconLdata.angle>PI/8&&xboxjoyconLdata.angle<PI*3/8){
            movement=Vehicle_Right_Backward;
        }else if(xboxjoyconLdata.angle>PI*5/8&&xboxjoyconLdata.angle<PI*7/8){
            movement=Vehicle_Left_Backward;
        }
        vehiclespeed=RadiusToMotorSpeed(xboxjoyconLdata.r);
    }else if(xboxdata.trg_l>TRG_DEADZONE){
        movement=Vehicle_Left_Rotation;
        vehiclespeed=TrgToMotorSpeed(xboxdata.trg_l);
    }else if(xboxdata.trg_r>TRG_DEADZONE){
        movement=Vehicle_Right_Rotation;
        vehiclespeed=TrgToMotorSpeed(xboxdata.trg_r);
    }else{
        movement=Vehicle_Stop;
        vehiclespeed=0;
    }
		
}
	
void Operate(void){
    //include servomode steppermode and vehiclemove
	if(ReturnControlMode()!=OperateMode){
		return;
	}
	if(targetarmlocation==Preset_None){
		Servo_SetStatus(SERVO_Continue_Control);
		Stepper_SetMode(Stepper_Continued_Control);
		Stepper_ChangeDir(Stepper1_Dir);
		Vehicle_Move(Facingstatus,movement,vehiclespeed);
	}else if(targetarmlocation==Preset_Basketlocation){
		Servo_SetStatus(SERVO_Target_Angle);
		Servo_SetTarget(SERVO1_MINSTEP,SERVO2_MINSTEP);
		Stepper_SetMode(Stepper_Target_Location);
        Stepper_SetTargetLocation(STEPPER1_BASKETLOCATION);
		Vehicle_Move(Facingstatus,movement,vehiclespeed);
	}else if(targetarmlocation==Preset_Picklocation){
		Servo_SetStatus(SERVO_Target_Angle);
		Servo_SetTarget(1850,1460); //2020,2040,0
		Stepper_SetMode(Stepper_Target_Location);
        Stepper_SetTargetLocation(STEPPER1_PICKLOCATION);
		Vehicle_Move(Facingstatus,movement,vehiclespeed);
	}else if(targetarmlocation==Preset_Preparelocation){
		Servo_SetStatus(SERVO_Target_Angle);
		Servo_SetTarget(SERVO1_MINSTEP,1260);//MG901_MAXSTEP,MG902_MINSTEP,0
		Stepper_SetMode(Stepper_Continued_Control);
		Stepper_ChangeDir(Stepper1_Dir);//doesn't need to decide the location of stepper1
		Vehicle_Move(Facingstatus,movement,vehiclespeed);
	}
}


struct __attribute__((packed)) reportdata{
    ControlMode mode;
     uint8_t confirm;
    Presetlocation targetarmlocation;
    int64_t stepperlocation;
    VehicleHead Facingstatus;
    WristHorizon WristStatus;

    Servo_Dir Servo1_Dir;
    Servo_Dir Servo2_Dir;
    Servo_Dir Servo3_Dir;
    uint32_t Servo1_speed;
    uint32_t Servo2_speed;
    uint16_t Servo1_compare;
    uint16_t Servo2_compare;
    uint16_t Servo3_compare;
    Stepper_Dir Stepper1_Dir;
    VehicleMovement movement;
    uint16_t vehiclespeed;
};


void OperateReport(void){
    reportdata data;
    data.confirm=confirmcount;
    data.mode=ReturnControlMode();
    data.stepperlocation=Stepper_Returnlocation();
    data.Stepper1_Dir=Stepper1_Dir;
    data.movement=movement;
    data.vehiclespeed=vehiclespeed;
    data.Servo1_Dir=Servo1_Dir;
    data.Servo1_speed=Servo1_speed;
    data.Servo1_compare=Servo_ReturnCompare(SERVO1_PWM_CHANNEL);
    data.Servo2_Dir=Servo2_Dir;
    data.Servo2_speed=Servo2_speed;
    data.Servo2_compare=Servo_ReturnCompare(SERVO2_PWM_CHANNEL);
    data.Servo3_Dir=Servo3_Dir;
    data.Servo3_compare=Servo_ReturnCompare(SERVO3_PWM_CHANNEL);
    data.Facingstatus=Facingstatus;
    data.WristStatus=WristStatus;
    data.targetarmlocation=targetarmlocation;
    static reportdata oldreportdata=data;
    if(!memcmp(&oldreportdata, &data, sizeof(reportdata))){
        return;
    }
    xbox_controller_data_t xboxdata=ReturnControllerData();
    if(ReturnControlMode()!=OperateMode){
        Serial.printf("confirm :%d, controlmode: %d \n",confirmcount,ReturnControlMode());
        Serial.printf("location: %lld\n",Stepper_Returnlocation());
    }else{
        Serial.printf("vhiclemovement: %d, speed: %d, axis(%d,%d) \n",movement,vehiclespeed,xboxdata.joy_l_h,xboxdata.joy_l_v);
        Serial.printf("servo1: (%d, %d, %d) ",Servo1_Dir,Servo1_speed,Servo_ReturnCompare(SERVO1_PWM_CHANNEL));
        Serial.printf("servo2:(%d, %d, %d) ",Servo2_Dir,Servo2_speed,Servo_ReturnCompare(SERVO2_PWM_CHANNEL));
        Serial.printf("servo3:(%d, %d) \n",Servo3_Dir,Servo_ReturnCompare(SERVO3_PWM_CHANNEL));
        Serial.printf("Stepper: dir %d, location %lld \n",Stepper1_Dir,Stepper_Returnlocation());
        Serial.printf("head: %d, wrist: %d, preset: %d\n",Facingstatus,WristStatus,targetarmlocation);
    }
    oldreportdata=data;
}

void IRAM_ATTR servotimer_intr(void){//only for servo operation  
    Servo_Operate(Servo1_Dir,Servo2_Dir,Servo3_Dir,Servo1_speed,Servo2_speed);
}

void IRAM_ATTR buttontimer_intr(void){//for status buttons
/*
x:confirm/facing; y:wristhorizontal ;RB:preset1/2;LB: delete preset
*/
    static uint8_t Confirmprekey=UNPRESSED;
    static uint8_t Facingprekey=UNPRESSED;
    static uint8_t PresetNoneprekey=UNPRESSED;
    static uint8_t Presetprekey=UNPRESSED;
    xbox_controller_data_t xboxdata=ReturnControllerData();
    
    if(ReturnControlMode()==CalibrateMaxLocationMode){//calibration Max
        if(xboxdata.btnX==UNPRESSED&&Confirmprekey==PRESSED){
            confirmcount+=1;
            if(confirmcount==2){
                confirmcount=0;
                Confirmprekey=UNPRESSED;
                Stepper_SetMaxLocation(Stepper_Returnlocation());//set the max
                ProceedControlMode();//proceed to clibrating min
                return;
            }
        }
        Confirmprekey=xboxdata.btnX;
    }else if(ReturnControlMode()==CalibrateMinLocationMode){//calibration min
        if(xboxdata.btnX==UNPRESSED&&Confirmprekey==PRESSED){
            confirmcount+=1;
            if(confirmcount==2){
                confirmcount=0;
                Confirmprekey=UNPRESSED;
                Stepper_SetMinLocation(Stepper_Returnlocation());//set the min
                ProceedControlMode();//proceed to clibrating pick
                return;
            }
        }
        Confirmprekey=xboxdata.btnX;
    }else if(ReturnControlMode()==CalibratePickLocationMode){//calibration pick
        if(xboxdata.btnX==UNPRESSED&&Confirmprekey==PRESSED){
            confirmcount+=1;
            if(confirmcount==2){
                confirmcount=0;
                Confirmprekey=UNPRESSED;
                STEPPER1_PICKLOCATION=Stepper_Returnlocation();//set the pick location
                ProceedControlMode();//proceed to clibrating basket
                return;
            }
        }
        Confirmprekey=xboxdata.btnX;
    }else if(ReturnControlMode()==CalibrateBasketLocationMode){
        if(xboxdata.btnX==UNPRESSED&&Confirmprekey==PRESSED){
            confirmcount+=1;
            if(confirmcount==2){
                confirmcount=0;
                Confirmprekey=UNPRESSED;
                STEPPER1_BASKETLOCATION=Stepper_Returnlocation();//set the basket location
                ProceedControlMode();//proceed to operate
                return;
            }
        }
        Confirmprekey=xboxdata.btnX;
        
    }else if(ReturnControlMode()==OperateMode){
        if(xboxdata.btnX==UNPRESSED&&Facingprekey==PRESSED){//rising
            if(Facingstatus==ARMHEAD)
                Facingstatus=BOARDHEAD;
            else if(Facingstatus==BOARDHEAD)
                Facingstatus=ARMHEAD;
        }
        if(xboxdata.btnL==UNPRESSED&&PresetNoneprekey==PRESSED){
            targetarmlocation=Preset_None;
        }else if(xboxdata.btnR==UNPRESSED&&Presetprekey==PRESSED){
            //if L2 is released, the release of R2 won't work
            if(targetarmlocation==Preset_None){
                //targetarmlocation=Preset_Preparelocation;
            //}else if(targetarmlocation==Preset_Preparelocation){
                targetarmlocation=Preset_Picklocation;
            }else if(targetarmlocation==Preset_Picklocation){
                targetarmlocation=Preset_Basketlocation;
            }else if(targetarmlocation==Preset_Basketlocation){
                //targetarmlocation=Preset_Preparelocation;
                targetarmlocation=Preset_Picklocation;
            }
        }	
//preset location of the arm
        
        //wristhorizontal?
        Presetprekey=xboxdata.btnR;
        PresetNoneprekey=xboxdata.btnL;
        Facingprekey=xboxdata.btnX;
    }
}
