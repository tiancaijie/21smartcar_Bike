/*
 * Init.h
 *
 *  Created on: 2022年1月14日
 *      Author: lenovo
 */

#ifndef CODE_INIT_H_
#define CODE_INIT_H_
#include "zf_common_headfile.h"

#define Battery_Power_Pin           ADC1_CH5_A21


#define Bike_ForwardWheel_pwmch     ATOM1_CH1_P21_3              //ATOM1_CH1_P21_3

#define Bike_BackwardWheel_pwmch    ATOM0_CH0_P02_0              //ATOM0_CH0_P02_0
#define Bike_BackwardWheel_IO_pin   P10_5                        //P10_2
#define Bike_BackwardWheel_EN_pin   P10_2                        //P10_5

#define Enable_pin                  P33_5

#define LED1_pin                    P20_12
#define LED2_pin                    P20_9
#define LED3_pin                    P20_11

#define ringbell                    P33_4



#define test_pin                    IMU660RA_CS_PIN

#define LED1(x)                     gpio_set_level(LED1_pin, (0 == x ? 1 : 0))
#define LED2(x)                     gpio_set_level(LED2_pin, (0 == x ? 1 : 0))
#define LED3(x)                     gpio_set_level(LED3_pin, (0 == x ? 1 : 0))
#define Buzzer(x)                   gpio_set(ringbell,x)

//开关
#define ENABLE_SWITCHON             (gpio_get_level(Enable_pin) == 1)  //使能开关
#define ENABLE_SWITCHOFF            (gpio_get_level(Enable_pin) == 0)

#define ForwardWheelForward         gpio_set_level(ForwardWheel_dir_pin, 1)
#define ForwardWheelBackward        gpio_set_level(ForwardWheel_dir_pin, 0)

#define BackwardWheelForward        gpio_set_level(BackwardWheel_dir_pin, 0)
#define BackwardWheelBackward       gpio_set_level(BackwardWheel_dir_pin, 1)


enum init_state
{
   init_error = 0,
   init_complete
};
extern enum init_state state;


extern void Init_All(void);
extern void gpio_init_all();

/*************************************************************************************/

void Init_All_CPU0(void);
void Init_All_CPU1(void);
#endif /* CODE_INIT_H_ */
