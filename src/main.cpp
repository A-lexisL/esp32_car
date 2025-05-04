#include <Arduino.h>
#include <NimBLEDevice.h>

#include <bleretro32/bleretro32.h>
#include <bleretro32/xbox.h>

pad_definition_t pad_list[] = {
    {"Xbox Wireless Controller"},
};

#define LOOP_DELAY 5

void setup()
{
    Serial.begin(115200);
    Serial.printf("Starting liming-vehicle\nStarting BLERetro32\n");
    BLERetro32_Setup(pad_list, sizeof(pad_list) / sizeof(pad_definition_t));

}

void loop()
{
    auto cnn_status = BLERetro32_Loop();
    delay(LOOP_DELAY);
}
