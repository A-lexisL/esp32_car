#include "PWM.h"
#include "Arduino.h"
#include "driver/ledc.h"
void Defined_PWM_Init(void){
    //stepper
    ledc_timer_config_t ledc_stepper_timer = {
        .speed_mode       = LEDC_LOW_SPEED_MODE,
        .duty_resolution  = STEPPER_PWM_RESOLOTION,
        .timer_num        = STEPPER_PWM_TIMER,
        .freq_hz          = STEPPER_PWM_FREQUENCY,
        .clk_cfg          = LEDC_USE_APB_CLK
    };
    ledc_timer_config(&ledc_stepper_timer);

    ledc_channel_config_t ledc_stepper_channel = {
        .gpio_num       = STEPPER_PWM_PIN,
        .speed_mode     = LEDC_LOW_SPEED_MODE,
        .channel        = STEPPER_PWM_CHANNEL,
        .intr_type      = LEDC_INTR_DISABLE,
        .timer_sel      = STEPPER_PWM_TIMER,
        .duty           = 0,
        .hpoint         = 0
    };
    ledc_channel_config(&ledc_stepper_channel);

    //servo
    ledc_timer_config_t ledc_servo_timer = {
        .speed_mode       = LEDC_LOW_SPEED_MODE,
        .duty_resolution  = SERVO_PWM_RESOLUTION,
        .timer_num        = SERVO_PWM_TIMER,
        .freq_hz          = SERVO_PWM_FREQUENCY,
        .clk_cfg          = LEDC_USE_APB_CLK
    };
    ledc_timer_config(&ledc_servo_timer);

    ledc_channel_config_t ledc_servo1_channel = {
        .gpio_num       = SERVO1_PWM_PIN,
        .speed_mode     = LEDC_LOW_SPEED_MODE,
        .channel        = SERVO1_PWM_CHANNEL,
        .intr_type      = LEDC_INTR_DISABLE,
        .timer_sel      = SERVO_PWM_TIMER,
        .duty           = 0,
        .hpoint         = 0
    };
    ledc_channel_config(&ledc_servo1_channel);

    ledc_channel_config_t ledc_servo2_channel = {
        .gpio_num       = SERVO2_PWM_PIN,
        .speed_mode     = LEDC_LOW_SPEED_MODE,
        .channel        = SERVO2_PWM_CHANNEL,
        .intr_type      = LEDC_INTR_DISABLE,
        .timer_sel      = SERVO_PWM_TIMER,
        .duty           = 0,
        .hpoint         = 0
    };
    ledc_channel_config(&ledc_servo2_channel);

    ledc_channel_config_t ledc_servo3_channel = {
        .gpio_num       = SERVO3_PWM_PIN,
        .speed_mode     = LEDC_LOW_SPEED_MODE,
        .channel        = SERVO3_PWM_CHANNEL,
        .intr_type      = LEDC_INTR_DISABLE,
        .timer_sel      = SERVO_PWM_TIMER,
        .duty           = 0,
        .hpoint         = 0
    };
    ledc_channel_config(&ledc_servo3_channel);

    //motor
    ledc_timer_config_t ledc_motor_timer = {
        .speed_mode       = LEDC_LOW_SPEED_MODE,
        .duty_resolution  = MOTOR_PWM_RESOLUTION,
        .timer_num        = MOTOR_PWM_TIMER,
        .freq_hz          = MOTOR_PWM_FREQUENCY,
        .clk_cfg          = LEDC_USE_APB_CLK
    };
    ledc_timer_config(&ledc_motor_timer);

    ledc_channel_config_t ledc_motor1_channel = {
        .gpio_num       = MOTOR1_PWM_PIN,
        .speed_mode     = LEDC_LOW_SPEED_MODE,
        .channel        = MOTOR1_PWM_CHANNEL,
        .intr_type      = LEDC_INTR_DISABLE,
        .timer_sel      = MOTOR_PWM_TIMER,
        .duty           = 0,
        .hpoint         = 0
    };
    ledc_channel_config(&ledc_motor1_channel);

    ledc_channel_config_t ledc_motor2_channel = {
        .gpio_num       = MOTOR2_PWM_PIN,
        .speed_mode     = LEDC_LOW_SPEED_MODE,
        .channel        = MOTOR2_PWM_CHANNEL,
        .intr_type      = LEDC_INTR_DISABLE,
        .timer_sel      = MOTOR_PWM_TIMER,        
        .duty           = 0,
        .hpoint         = 0
    };
    ledc_channel_config(&ledc_motor2_channel);
    ledc_channel_config_t ledc_motor3_channel = {
        .gpio_num       = MOTOR3_PWM_PIN,
        .speed_mode     = LEDC_LOW_SPEED_MODE,
        .channel        = MOTOR3_PWM_CHANNEL,
        .intr_type      = LEDC_INTR_DISABLE,
        .timer_sel      = MOTOR_PWM_TIMER,       
        .duty           = 0,
        .hpoint         = 0
    };
    ledc_channel_config(&ledc_motor3_channel);
    ledc_channel_config_t ledc_motor4_channel = {
        .gpio_num       = MOTOR4_PWM_PIN,
        .speed_mode     = LEDC_LOW_SPEED_MODE,
        .channel        = MOTOR4_PWM_CHANNEL,
        .intr_type      = LEDC_INTR_DISABLE,
        .timer_sel      = MOTOR_PWM_TIMER,
        .duty           = 0,
        .hpoint         = 0
    };
    ledc_channel_config(&ledc_motor4_channel);
}


