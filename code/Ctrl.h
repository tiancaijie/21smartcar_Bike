#ifndef __CTRL_H
#define __CTRL_H

#include "zf_common_headfile.h"
#include "zf_common_typedef.h"

/* =========== 宏定义 ============= */

#define  PWM_deadline  800

#define Buzzer_Test 0

//extern uint8 Power_Off;
//extern uint8 Get_Point;
typedef enum
{
    Silent    = 0,
    Power_Off = 1,
    Get_Point,
    Mark_Point,
    Mark_Board,
    Mark_Over,
    Ringing,
} BuzzerState;

//typedef enum
//{
//    Off = 0,
//    On  = 1,
//}Flag_State;


void Buzzer_Ctrl(void);           //蜂鸣器控制

typedef struct
{
    /* ----Switch---- */
    struct
    {
        uint16 OK_ForwardWheel_spd;
        uint8  OK_ForwardWheel_dir;
        uint16 OK_BackwardWheel_spd;
        uint8  OK_BackwardWheel_dir;
        uint16 OK_FootWheel_spd;
        uint8  OK_FootWheel_dir;
        uint8  speed_debug;
        uint8  Oled_Show;
        uint8  Param_send;
        uint8  NewThreshold;
    }Debug;
    struct
    {
        boolean BackWheelEN;                // 后轮使能开关
        boolean ServosEN;                   // 舵机使能
        boolean RC_CtrlEN;                  // 遥控器接收机使能
        boolean DynamicZeroEN;              // 动态零点使能

        boolean Yaw_CtrlEN;                 // 方向环使能
        boolean BigWheelEN;                 // 大轮速度环
    }Switch;

    /* ----Roll control----*/
    struct
    {
        float ActSpeed;                     //Roll实际转速之和
        float ExpectSpeed;                  // 动量轮期望转速
        float ExpectAngle;                  // Roll轴期望角度
        float ExpectOmega;                  // Roll轴期望角速度
        float DynamicZero;                  // 动态零点值
        float Dynamic_k;                    // 动态零点值

        float DynamicZero_T;                // 动态零点值

        uint8 BalanceSign;
        float Output;
    }Roll;
    /* ----Pitch control----*/
    struct
    {
        float ExpectSpeed_Exp;              // 期望车速
        float ExpectSpeed_Input_Find;
        float ExpectSpeed_Input_Turn;
        float ExpectSpeed_Input_Fast;
        int ExpectSpeed_Input_Start;
        float ExpectSpeed_Act;
        float ExpectAngle;                  // Pitch轴期望角度
        float ExpectOmega;                  // Pitch轴期望角速度
        float BalancePoint;                 // 平衡点
        uint8 BalanceSign;
        float Output;
    }Pitch;
    struct
    {
        float ExpectAngle_Act;              // Yaw轴期望角度
        float ExpectOmega_Act;              // Yaw轴期望角速度
        float ExpectOmega_Exp;
        float Output;
    }Yaw;


    /* ----GlobalFlag---- */
    struct
    {
        boolean            CarStop;                   // 停车标志
        boolean           CarStart;

        Flag_State  Power_Off_Flag;
        Flag_State  Get_Point_Flag;

        Flag_State Mark_Board_Flag;

        Flag_State Mark_Point_Flag;
        Flag_State Mark_Over_Flag;



    }GlobalFlag;

    struct
    {
        Flag_State   NearBoard_Flag;
        uint8            Board_Order;
    }GlobalState;
    struct
    {
        uint8        Flag;                          // 发车标志
        uint8        Turn_Test;
        uint16_t     Delay_count;                   // 发车延时
        uint16_t     Delay_Limit;                   // 发车延时

    }Start_Run;



    /* ----Buzzer---- */
    struct
    {
        BuzzerState buzzState;
        uint16      Ring_time;
    }Buzzer_typ;

    int Battery_v;
    /* ----Speed control---- */
    struct
    {
        float Forward[3];                 // 后轮实际速度
        float Backward[3];                // 后轮实际速度

        float Foot_Ctrl[3];               //small
        float Foot_Odo[3];                //small

        int Flag;                         //速度标志位，用于切换速度
    }Speed;
    /* ----Out Put---- */
    struct
    {
        int16 BackwardWheel;
        int16 ForwardWheel;
    }Motor_Output;
    /* ----Out Put---- */
    struct
    {
        int Flag;                              //转向标志位
        int Choose;
        int TimeCount;                         //转向计数
        int Row;
        int State;
        float Omega;
    }Turn;

    struct
    {
        int Flag;
        float Angle;
    }Error;
}CtrlHandle_TypeDef;

/* ========= 全局变量声明 ========== */
extern CtrlHandle_TypeDef hCtrl;
extern int error;
extern int Point[30];
/* =========== 函数声明 ============ */
void CtrlHandle_Init(CtrlHandle_TypeDef *CtrlHandle);

void Angle_cal(void);

void SpeedCtrl(void);

void RollOmegaCtrl(void);
void RollAngleCtrl(void);
void TurnAngelCtrl(void);

void SetMotorVoltage_Back(void);
void SetMotorVoltage(void) ;
void PID_InitAll(void);

#endif /* __CTRL_H */

