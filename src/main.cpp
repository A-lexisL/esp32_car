#include <Arduino.h>
#include <NimBLEDevice.h>

#include <bleretro32/bleretro32.h>
#include <bleretro32/xbox.h>

#include "PWM.h"

pad_definition_t pad_list[] = {
    {"Xbox Wireless Controller"},
};

#define LOOP_DELAY 5

void Defined_Init(void){
    
}

void setup()
{   
    Defined_Init();
    Serial.begin(115200);
    Serial.printf("Starting liming-vehicle\n");

    Serial.printf("Starting BLERetro32\n");
    BLERetro32_Setup(pad_list, sizeof(pad_list) / sizeof(pad_definition_t));

}

void loop()
{
    auto cnn_status = BLERetro32_Loop();
    delay(LOOP_DELAY);
}
