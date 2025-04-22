#include "PWM.h"
#include "esp_log.h"
void Defined_PWM_Init(void){
    //stepper
    ledc_timer_config_t Stepper_ledc_timer={
        .duty_resolution=STEPPER_PWM_RESOLOTION,
        .freq_hz=STEPPER_PWM_FREQUENCY,
        .speed_mode=LEDC_LOW_SPEED_MODE,//s3 only has low speed
        .timer_num=STEPPER_PWM_TIMER,
        .clk_cfg = LEDC_USE_APB_CLK
    };
    ESP_ERROR_CHECK(ledc_timer_config(&Stepper_ledc_timer));
    
    ledc_channel_config_t Stepper_ledc_channel={
        .channel=STEPPER_PWM_CHANNEL,
        .duty=0,
        .gpio_num=STEPPER_PWM_PIN,
        .speed_mode=LEDC_LOW_SPEED_MODE,
        .hpoint=0,
        .timer_sel=STEPPER_PWM_TIMER
    };
    ESP_ERROR_CHECK(ledc_channel_config(&Stepper_ledc_channel));
    
    
    //servo
    ledc_timer_config_t Servo_ledc_timer={
        .duty_resolution=SERVO_PWM_RESOLUTION,
        .freq_hz=SERVO_PWM_FREQUENCY,
        .speed_mode=LEDC_LOW_SPEED_MODE,//s3 only has low speed
        .timer_num=SERVO_PWM_TIMER,
        .clk_cfg = LEDC_USE_APB_CLK
    };
    ESP_ERROR_CHECK(ledc_timer_config(&Servo_ledc_timer));
    
    ledc_channel_config_t Servo1_ledc_channel={
        .channel=SERVO1_PWM_CHANNEL,
        .duty=0,
        .gpio_num=SERVO1_PWM_PIN,
        .speed_mode=LEDC_LOW_SPEED_MODE,
        .hpoint=0,
        .timer_sel=SERVO_PWM_TIMER
    };
    ledc_channel_config_t Servo2_ledc_channel={
        .channel=SERVO2_PWM_CHANNEL,
        .duty=0,
        .gpio_num=SERVO2_PWM_PIN,
        .speed_mode=LEDC_LOW_SPEED_MODE,
        .hpoint=0,
        .timer_sel=SERVO_PWM_TIMER
    };
    ledc_channel_config_t Servo3_ledc_channel={
        .channel=SERVO3_PWM_CHANNEL,
        .duty=0,
        .gpio_num=SERVO3_PWM_PIN,
        .speed_mode=LEDC_LOW_SPEED_MODE,
        .hpoint=0,
        .timer_sel=SERVO_PWM_TIMER
    };
    ESP_ERROR_CHECK(ledc_channel_config(&Servo1_ledc_channel));
    ESP_ERROR_CHECK(ledc_channel_config(&Servo2_ledc_channel));
    ESP_ERROR_CHECK(ledc_channel_config(&Servo3_ledc_channel));


    //motor
    ledc_timer_config_t Motor_ledc_timer={
        .duty_resolution=MOTOR_PWM_RESOLUTION,
        .freq_hz=MOTOR_PWM_FREQUENCY,
        .speed_mode=LEDC_LOW_SPEED_MODE,//s3 only has low speed
        .timer_num=MOTOR_PWM_TIMER,
        .clk_cfg = LEDC_USE_APB_CLK
    };
    ESP_ERROR_CHECK(ledc_timer_config(&Motor_ledc_timer));
    
    ledc_channel_config_t Motor1_ledc_channel={
        .channel=MOTOR1_PWM_CHANNEL,
        .duty=0,
        .gpio_num=MOTOR1_PWM_PIN,
        .speed_mode=LEDC_LOW_SPEED_MODE,
        .hpoint=0,
        .timer_sel=MOTOR_PWM_TIMER
    };
    ledc_channel_config_t Motor2_ledc_channel={
        .channel=MOTOR2_PWM_CHANNEL,
        .duty=0,
        .gpio_num=MOTOR2_PWM_PIN,
        .speed_mode=LEDC_LOW_SPEED_MODE,
        .hpoint=0,
        .timer_sel=MOTOR_PWM_TIMER
    };
    ledc_channel_config_t Motor3_ledc_channel={
        .channel=MOTOR3_PWM_CHANNEL,
        .duty=0,
        .gpio_num=MOTOR3_PWM_PIN,
        .speed_mode=LEDC_LOW_SPEED_MODE,
        .hpoint=0,
        .timer_sel=MOTOR_PWM_TIMER
    };
    ledc_channel_config_t Motor4_ledc_channel={
        .channel=MOTOR4_PWM_CHANNEL,
        .duty=0,
        .gpio_num=MOTOR4_PWM_PIN,
        .speed_mode=LEDC_LOW_SPEED_MODE,
        .hpoint=0,
        .timer_sel=MOTOR_PWM_TIMER
    };
    ESP_ERROR_CHECK(ledc_channel_config(&Motor1_ledc_channel));
    ESP_ERROR_CHECK(ledc_channel_config(&Motor2_ledc_channel));
    ESP_ERROR_CHECK(ledc_channel_config(&Motor3_ledc_channel));
    ESP_ERROR_CHECK(ledc_channel_config(&Motor4_ledc_channel));
}   

void Defined_PWM_Set_Duty(ledc_mode_t Input_Speed_Mode,ledc_channel_t Input_Channel,uint32_t Input_Duty){
    ledc_set_duty(Input_Speed_Mode,Input_Channel,Input_Duty);
    ledc_update_duty(Input_Speed_Mode,Input_Channel);
}

uint32_t Defined_PWM_Get_Duty(ledc_mode_t Input_speed_mode, ledc_channel_t Input_channel){
    return ledc_get_duty(Input_speed_mode,Input_channel);
}
