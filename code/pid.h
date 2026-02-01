#ifndef __PID_H
#define __PID_H

#include "zf_common_headfile.h"

typedef enum
{
    PID_MODE_POSITION = 0,
    PID_MODE_POSITION_ISeparation,
    PID_MODE_ADD,
}PID_MODE_TypeDef;

typedef struct
{
    uint8               name[20];                                                       //对应结构体的名字
    uint8               index;                                                          //在flash中存储的引导值（从1开始）
    PID_MODE_TypeDef    mode;
    uint8               ZeroOutFlag;
    float               kp;
    float               ki;
    float               kd;
    float               factor_kp;                                                      //kp倍数
    float               factor_ki;                                                      //ki倍数
    float               factor_kd;                                                      //kd倍数

    float               factor_iOutMax;                                                 //iOutMax倍数
    float               factor_outMax;                                                  //outMax倍数

    float               iOutMax;
    float               outMax;
    float               ISeparation_error_max;
}PID_InitTypeDef;

typedef struct
{
    PID_MODE_TypeDef    mode;
    uint8               ZeroOutFlag;

    float               set;                                                            //希望值
    float               err3[3];                                                        //偏差值

    float               kp;
    float               ki;
    float               kd;

    float               pOut;
    float               iOut;
    float               dOut;

    float               out;            //储存每一次pid计算后的输出值
    float               out_terminal;

    float               iOutMax;
    float               outMax;
    float               ISeparation_error_max;

}PID_HandleTypeDef;
/*Pitch*/
extern PID_HandleTypeDef PID_PitchOmega;
extern PID_InitTypeDef   PID_PitchOmega_init;

extern PID_HandleTypeDef PID_PitchAngle;
extern PID_InitTypeDef   PID_PitchAngle_init;

extern PID_HandleTypeDef PID_PitchSpeed;
extern PID_InitTypeDef   PID_PitchSpeed_init;

/*Roll*/
extern PID_HandleTypeDef PID_RollOmega;
extern PID_InitTypeDef   PID_RollOmega_init;

extern PID_HandleTypeDef PID_RollAngle;
extern PID_InitTypeDef   PID_RollAngle_init;

extern PID_HandleTypeDef PID_RollError;
extern PID_InitTypeDef   PID_RollError_init;

/*Yaw*/
extern PID_HandleTypeDef PID_YawOmega;
extern PID_InitTypeDef   PID_YawOmega_init;

extern PID_HandleTypeDef PID_YawAngle;
extern PID_InitTypeDef   PID_YawAngle_init;

/*List*/
extern PID_HandleTypeDef *PID_list[];
extern PID_InitTypeDef   *PID_init_list[];
#define PID_Num 8

#define Led_Num 20
//#define PID_Sector 2
#define PID_Sector 5
#define Led_Sector 8

void PID_init(PID_HandleTypeDef *pid, PID_InitTypeDef *PID);
void PID_loadparam(PID_HandleTypeDef *pid, float kp, float ki, float kd);
void PID_loadtarget(PID_HandleTypeDef *pid, float target);
float PID_calc(PID_HandleTypeDef *pid, float exp_data, float real_data);
void PID_cleardata(PID_HandleTypeDef *pid);
boolean PID_InputCheck(PID_InitTypeDef *target);

#endif/* __PID_H */


