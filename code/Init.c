 /*
 * Init.c
 *
 *  Created on: 2022年1月14日
 *      Author: lenovo 干你母
 */

#include "zf_common_headfile.h"
#include "Init.h"

enum init_state state = init_error;

void gpio_init_all()
{
    gpio_init(LED1_pin, GPO, 1, GPO_PUSH_PULL);//红
    gpio_init(LED2_pin, GPO, 1, GPO_PUSH_PULL);//绿
    gpio_init(LED3_pin, GPO, 1, GPO_PUSH_PULL);//蓝

    gpio_init(ringbell, GPO, 0, GPO_PUSH_PULL);//蜂鸣器
}

/*************************************************
Function: Init_All_CPU0
Description: 系统初始化
Calls:
Output: 无
Return: 无
Others: 无
*************************************************/
void Init_All_CPU0(void)
{
    /*驱动初始化*/
    pwm_init(Bike_ForwardWheel_pwmch, 50, 0);                        //前轮舵机初始化
    pwm_init(Bike_BackwardWheel_pwmch, 50, 0);                       //后轮电机初始化
    gpio_init(Bike_BackwardWheel_IO_pin, GPO, 0, GPO_PUSH_PULL);        //后轮电机io初始化
    gpio_init(Bike_BackwardWheel_EN_pin, GPO, 0, GPO_PUSH_PULL);        //后轮电机使能初始化
    /*使能开关初始化*/
    gpio_init(Enable_pin, GPI, 0, GPI_PULL_DOWN);                       //使能开关
    /*其余gpio初始化*/
    gpio_init_all();
    /*adc读值初始化*/
    adc_init(Battery_Power_Pin,  ADC_12BIT);                            //电源电压
    /*串口初始化*/
    uart_init(UART_1, 115200, UART1_TX_P11_12, UART1_RX_P11_10);        //蓝牙
    /*GNSS初始化*/
    gnss_init(TAU1201);
    /*陀螺仪初始化*/
    imu963ra_init();
    state = init_complete;
    system_delay_init();
    /*键显初始化*/
    OLED_Init();
    CH455_Init();
    Oled_Input();
}

/*************************************************
Function: Init_All_CPU1
Description: 系统初始化
Calls:
Output: 无
Return: 无
Others: 无
*************************************************/
void Init_All_CPU1(void)
{
}
