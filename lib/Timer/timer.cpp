#include "timer.h"
#include "Arduino.h"
void IRAM_ATTR servotimer_intr(void);
void IRAM_ATTR buttontimer_intr(void);
void Defined_Timer_Init(void){
    //servo
    hw_timer_t *servotimer=timerBegin(SERVO_INTR_TIMER_IDX,SERVO_INTR_TIMER_DIVIDER,true);
    timerAttachInterrupt(servotimer,servotimer_intr,true);
    timerAlarmWrite(servotimer,SERVO_INTR_TIMER_ALARM_VALUE,true);
    timerAlarmEnable(servotimer);
    //button
    hw_timer_t *buttontimer=timerBegin(BUTTON_INTR_TIMER_IDX,BUTTON_INTR_TIMER_DIVIDER,true);
    timerAttachInterrupt(buttontimer,buttontimer_intr,true);
    timerAlarmWrite(buttontimer,BUTTON_INTR_TIMER_ALARM_VALUE,true);
    timerAlarmEnable(buttontimer);



}

