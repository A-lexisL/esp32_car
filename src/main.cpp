#include <Arduino.h>
#include <NimBLEDevice.h>

#include <bleretro32/bleretro32.h>
#include <bleretro32/xbox.h>

#include "operate.h"
#include "OLED.h"
pad_definition_t pad_list[] = {
    {"Xbox Wireless Controller"},
};

#define LOOP_DELAY 5

void Defined_Init(void){
    Operate_Init();
    OLED_Init();
    
}

void setup()
{   
    Defined_Init();


    SetControllerSerialReportStatus(ControllerDataSerialReportDisable);
    Serial.begin(115200);
    Serial.printf("Starting liming-vehicle\n");

    Serial.printf("Starting BLERetro32\n");
    BLERetro32_Setup(pad_list, sizeof(pad_list) / sizeof(pad_definition_t));

}

void loop()
{   
    auto cnn_status = BLERetro32_Loop();
    if(ReturnControlMode()!=OperateMode){
		Calibrate();
		if(cnn_status==CnnStatus::Connected){
            OperateReport();
        }
	}
	
	
	else if(ReturnControlMode()==OperateMode){
		InterpretController();
		Operate();
        OperateReport();
	}
    
}
