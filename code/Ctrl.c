#include "Ctrl.h"

int error;
int Light_Numeber = 0;
int Point[30] = {0};
int count_time = 0;
#define Bike_ForwardWheel_Center  750
/* ========= 全局变量定义 ========== */

//-----CtrlHandle-----
CtrlHandle_TypeDef hCtrl = {.Buzzer_typ.buzzState = Silent,
                            .GlobalState.NearBoard_Flag = Off,
                            .GlobalState.Board_Order    = 0,
                            };

//-----PID------
/*Pitch角速度*/
PID_HandleTypeDef PID_PitchOmega;
PID_InitTypeDef   PID_PitchOmega_init=
{
    .name = "Pitch_Omega",
    .index = 1,
    .mode = PID_MODE_POSITION,
    .kp = 0.0,
    .factor_kp = 1.0,
    .ki = 0.0,
    .factor_ki = 1.0,
    .kd = 0.0,
    .factor_kd = 1.0,
    .factor_iOutMax = 1.0,
    .factor_outMax = 1.0,
    .iOutMax = 3000,
    .outMax  = 7000,
};

/*Pitch角度*/
PID_HandleTypeDef PID_PitchAngle;
PID_InitTypeDef   PID_PitchAngle_init=
{
    .name = "Pitch_Angle",
    .index = 2,
    .mode = PID_MODE_POSITION,
    .kp = 0.0,
    .factor_kp = 0.001,
    .ki = 0.0,
    .factor_ki = 0.001,
    .kd = 0.0,
    .factor_kd = 0.001,
    .factor_iOutMax = 1.0e-3,
    .factor_outMax  = 1.0e-3,
    .iOutMax = 1,
    .outMax  = 3,
};

/*Pitch速度*/
PID_HandleTypeDef PID_PitchSpeed;
PID_InitTypeDef   PID_PitchSpeed_init=
{
    .name = "Pitch_Speed",
    .index = 3,
    .mode = PID_MODE_POSITION,
    .kp = 0.0,
    .factor_kp = 1.0e-6,
    .ki = 0.0,
    .factor_ki = 1.0e-8,
    .kd = 0.0,
    .factor_kd = 1.0e-8,
    .factor_iOutMax = 1.0e-3,
    .factor_outMax  = 1.0e-3,
    .iOutMax = 0.1,
    .outMax  = 0.3,
};

/*Roll角速度*/
PID_HandleTypeDef PID_RollOmega;
PID_InitTypeDef   PID_RollOmega_init=
{
    .name = "Roll_Omega",
    .index = 4,
    .mode = PID_MODE_POSITION,
    .kp = 0.0,
    .factor_kp = 1.0,
    .ki = 0.0,
    .factor_ki = 1.0,
    .kd = 0.0,
    .factor_kd = 1.0,
    .factor_iOutMax = 1.0,
    .factor_outMax = 1.0,
    .iOutMax = 3000,
    .outMax  = 10000,
};

/*Roll角度*/
PID_HandleTypeDef PID_RollAngle;
PID_InitTypeDef   PID_RollAngle_init=
{
    .name = "Roll_Angle",
    .index = 5,
    .mode = PID_MODE_POSITION,
    .kp = 0.0,
    .factor_kp = 1.0e-3,
    .ki = 0.0,
    .factor_ki = 1.0e-5,
    .kd = 0.0,
    .factor_kd = 1.0e-4,
    .factor_iOutMax = 1.0e-3,
    .factor_outMax  = 1.0e-3,
    .iOutMax = 0.5,
    .outMax  = 1.5,
};

/*Roll速度*/
PID_HandleTypeDef PID_RollError;
PID_InitTypeDef   PID_RollError_init=
{
    .name = "Roll_Speed",
    .index = 6,
    .mode = PID_MODE_POSITION,
    .kp = 0.0,
    .factor_kp = 1.0e-7,
    .ki = 0.0,
    .factor_ki = 1.0e-7,
    .kd = 0.0,
    .factor_kd = 1.0e-7,
    .factor_iOutMax = 1.0e-4,
    .factor_outMax  = 1.0e-4,
    .iOutMax = 0.05,
    .outMax  = 0.15,
};
/*Yaw角速度*/
PID_HandleTypeDef PID_YawOmega;
PID_InitTypeDef   PID_YawOmega_init=
{
    .name = "Yaw_Omega",
    .index = 7,
    .mode = PID_MODE_POSITION,
    .kp = 0.0,
    .factor_kp = 1.0,
    .ki = 0.0,
    .factor_ki = 1.0,
    .kd = 0.0,
    .factor_kd = 1.0,
    .factor_iOutMax = 1.0,
    .factor_outMax = 1.0,
    .iOutMax = 2000,
    .outMax  = 10000,
};
/*Yaw角度*/
PID_HandleTypeDef PID_YawAngle;
PID_InitTypeDef   PID_YawAngle_init=
{
    .name = "Yaw_Angle",
    .index = 8,
    .mode = PID_MODE_POSITION,
    .kp = 0.0,
    .factor_kp = 1.0e-3,
    .ki = 0.0,
    .factor_ki = 1.0e-4,
    .kd = 0.0,
    .factor_kd = 1.0e-3,
    .factor_iOutMax = 1.0e-3,
    .factor_outMax  = 1.0e-3,
    .iOutMax = 0.5,
    .outMax  = 1.5,
};

void PID_InitAll(void)
{
    for(uint8 i = 0; i < PID_Num; i++)
    {
        PID_init(PID_list[i], PID_init_list[i]);
    }
}

/* ========= 内部函数声明  ========== */

/* ========= 函数定义 ========== */

/*****************************************
** Function: CtrlHandle_Init
** Description: 控制句柄结构体初始化
** Means:   从Flash中读取相应的标志或其他变量的值，对一些flag赋初始值
** Others:
******************************************/
void CtrlHandle_Init(CtrlHandle_TypeDef *CtrlHandle)
{

}

/*****************************************
** Function: Get_Speed
** Description: 获取单车后轮速度
** Others: 无
******************************************/
void Get_Speed(void)
{

}

/*****************************************
** Function: Angle_cal
** Description: 获取角度信息
** Others: 无
******************************************/
void Angle_cal(void)
{
    imu963ra_get_acc();
    imu963ra_get_gyro();
    imu963_data_trans();
    //加速度低通滤波
    IMUData.ax_Filt = IMUData.ax_Filt*0.9  + IMUData.ax*0.1;
    IMUData.ay_Filt = IMUData.ay_Filt*0.9  + IMUData.ay*0.1;
    IMUData.az_Filt = IMUData.az_Filt*0.9  + IMUData.az*0.1;

    IMUData.gx_Filt = IMUData.gx_Filt*0.9  + IMUData.gx*0.1;
    IMUData.gy_Filt = IMUData.gy_Filt*0.9  + IMUData.gy*0.1;
    IMUData.gz_Filt = IMUData.gz_Filt*0.9  + IMUData.gz*0.1;

    MahonyAHRSupdateIMU(&IMUData.q[0],IMUData.gx,IMUData.gy,IMUData.gz,IMUData.ax_Filt,IMUData.ay_Filt,IMUData.az_Filt);       //基于Mahony算法更新四元数IMUData.q

    get_angle(&IMUData.q[0],&IMUData.yaw_mahony,&IMUData.pitch_mahony,&IMUData.roll_mahony);  //从四元数解算欧拉序列的角度
}

/************************************************
** Function: SpeedCtrl
** Description: 单车速度控制
** Others:
*************************************************/
void SpeedCtrl(void)
{
    hCtrl.Pitch.ExpectSpeed_Exp = (float)hCtrl.Pitch.ExpectSpeed_Input_Start;

    hCtrl.Pitch.ExpectSpeed_Act = Step_Limit(hCtrl.Pitch.ExpectSpeed_Exp, hCtrl.Pitch.ExpectSpeed_Act, 0.4);

    hCtrl.Speed.Foot_Ctrl[0] = 0.5 * hCtrl.Speed.Foot_Ctrl[1] + 0.5 * hCtrl.Speed.Foot_Ctrl[0];

    hCtrl.Speed.Foot_Ctrl[1] = hCtrl.Speed.Foot_Ctrl[0];                    //速度滤波

    hCtrl.Motor_Output.BackwardWheel  = PID_calc(&PID_PitchSpeed, hCtrl.Pitch.ExpectSpeed_Act, hCtrl.Speed.Foot_Ctrl[0]);  //速度与角度之间极性相反
}

/**********************************************************************************************************************************/
//                                      Roll                                                                                      //
//                                     Balance                                                                                    //
/**********************************************************************************************************************************/

/*************************************************************************
** Function: RollOmegaCtrl
** Description: 单车Roll角速度控制
** Others: 无
**************************************************************************/
void RollOmegaCtrl(void)
{
    hCtrl.Roll.Output = PID_calc(&PID_RollOmega,hCtrl.Roll.ExpectOmega,IMUData.gy);
}

/************************************************
** Function: RollAngleCtrl
** Description: 单车Roll角度控制
** Others:无
*************************************************/
void RollAngleCtrl(void)
{
//    if(hCtrl.Yaw.ExpectOmega_Act > 0.30)
//    {
//        hCtrl.Roll.DynamicZero = -0.0006153*(hCtrl.Pitch.ExpectSpeed_Act)*(hCtrl.Yaw.ExpectOmega_Act - 0.30)*hCtrl.Roll.Dynamic_k;
//    }
//    else if(hCtrl.Yaw.ExpectOmega_Act < -0.30)
//    {
//        hCtrl.Roll.DynamicZero = -0.0006153*(hCtrl.Pitch.ExpectSpeed_Act)*(hCtrl.Yaw.ExpectOmega_Act + 0.30)*hCtrl.Roll.Dynamic_k;
//    }
//    else
//    {
//        hCtrl.Roll.DynamicZero = 0;
//    }

    hCtrl.Roll.ExpectOmega = PID_calc(&PID_RollAngle,hCtrl.Roll.ExpectAngle,(IMUData.roll_mahony-(hCtrl.Roll.DynamicZero + hCtrl.Roll.DynamicZero_T)));
}

/************************************************
** Function: TurnAngelCtrl
** Description: 单车转向角度控制环
** Others:
*************************************************/
void TurnAngelCtrl(void)
{
    hCtrl.Error.Angle = 0;
    hCtrl.Roll.ExpectAngle = -PID_calc(&PID_RollError,0,hCtrl.Error.Angle);
}

/*****************************************
** Function:    SetMotorVoltage
** Description: 输出PWM控制
** Others:
******************************************/
#define Bike_ForwardWheel_Center  750
void SetMotorVoltage(void)
{
    hCtrl.Motor_Output.ForwardWheel = Bike_ForwardWheel_Center + hCtrl.Roll.Output;
    pwm_set_duty(Bike_ForwardWheel_pwmch, hCtrl.Motor_Output.ForwardWheel);

    if (hCtrl.Motor_Output.BackwardWheel > 0)
    {
        gpio_set_level(Bike_BackwardWheel_EN_pin,1);
        gpio_set_level(Bike_BackwardWheel_IO_pin,0);
        pwm_set_duty(Bike_BackwardWheel_pwmch, hCtrl.Motor_Output.BackwardWheel);
    }
    else if (hCtrl.Motor_Output.BackwardWheel <= 0)
    {
        gpio_set_level(Bike_BackwardWheel_EN_pin,1);
        gpio_set_level(Bike_BackwardWheel_IO_pin,1);
        pwm_set_duty(Bike_BackwardWheel_pwmch, hCtrl.Motor_Output.BackwardWheel);
    }
}
