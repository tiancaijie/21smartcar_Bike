#include <Fun.h>


/*************************************************
Function: CheckVoltage
Description: 检测电池电压
Detail:
*************************************************/
void CheckVoltage(void)
{

}

/*******************************************************************************************
** Function: Float_to_Byte
** Description: 浮点型转4字节
** Others:VOFA_ParameterSent内部调用
** Author:赵鑫鑫
********************************************************************************************/
typedef union//浮点型转长整型共用体
{
  float fdata;
  unsigned long ldata;
}FloatLongType;
void Float_to_Byte(float f,unsigned char byte[])//浮点型转4字节
{
    FloatLongType fl;
    fl.fdata=f;
    byte[0]=(unsigned char)fl.ldata;
    byte[1]=(unsigned char)(fl.ldata>>8);
    byte[2]=(unsigned char)(fl.ldata>>16);
    byte[3]=(unsigned char)(fl.ldata>>24);
}


uint32 ADCTime = 0;
uint32 ADCTime2 = 0;
/*******************************************************************************************
** Function: VOFA_ParameterSent
** Description: VOFA+下位机JustFloat协议发数据
** Others:直接连线，蓝牙发送，WIFI_UDP均可用
********************************************************************************************/
#define VOFA_JustFloat_index    20
unsigned long VOFAdata[VOFA_JustFloat_index] = {0};

uint8 MapCount_Send = 1;
void VOFA_ParameterSent(void)
{
    unsigned char tail[4] = {0x00,0x00,0x80,0x7f};//帧尾

/********VOFA模板***********
 * 将 temp_f赋为需显示的值即可
 * *************************/

    float Temp_f[VOFA_JustFloat_index] = {0.0};
    switch(hCtrl.Debug.Param_send)
    {
        case 1 :
        {
            Temp_f[0] = (float)PID_PitchSpeed.pOut;
            Temp_f[1] = (float)PID_PitchSpeed.iOut;
            Temp_f[2] = (float)PID_PitchSpeed.out;

            Temp_f[3] = (float)PID_PitchAngle.pOut;
            Temp_f[4] = (float)PID_PitchAngle.iOut;
            Temp_f[5] = (float)PID_PitchAngle.dOut;
            Temp_f[6] = (float)PID_PitchAngle.out;

            Temp_f[7] = (float)PID_PitchOmega.pOut;
            Temp_f[8] = (float)PID_PitchOmega.iOut;
            Temp_f[9] = (float)PID_PitchOmega.out;

            Temp_f[10] = (float)hCtrl.Speed.Foot_Ctrl[0];
            Temp_f[11] = (float)IMUData.pitch_mahony - Deg2Rad(hCtrl.Pitch.BalancePoint);
            Temp_f[12] = (float)IMUData.gx;

            Temp_f[13] = (float)hCtrl.Pitch.ExpectSpeed_Act;
            Temp_f[14] = (float)hCtrl.Pitch.ExpectAngle;
            Temp_f[15] = (float)hCtrl.Pitch.ExpectOmega;

            Temp_f[16] = (float)PID_PitchAngle.outMax;
            Temp_f[17] = (float)PID_PitchSpeed.outMax;

            break;
        }
        case 2 :
        {
            Temp_f[0] = (float)PID_RollError.pOut;
            Temp_f[1] = (float)PID_RollError.iOut;
            Temp_f[2] = (float)PID_RollError.out;

            Temp_f[3] = (float)PID_RollAngle.pOut;
            Temp_f[4] = (float)PID_RollAngle.iOut;
            Temp_f[5] = (float)PID_RollAngle.dOut;
            Temp_f[6] = (float)PID_RollAngle.out;

            Temp_f[7] = (float)PID_RollOmega.pOut;
            Temp_f[8] = (float)PID_RollOmega.iOut;
            Temp_f[9] = (float)PID_RollOmega.out;

            Temp_f[10] = (float)hCtrl.Roll.ActSpeed;
            Temp_f[11] = (float)IMUData.roll_mahony;
            Temp_f[12] = (float)IMUData.gy;

            Temp_f[13] = (float)hCtrl.Roll.ExpectSpeed;
            Temp_f[14] = (float)hCtrl.Roll.ExpectAngle;
            Temp_f[15] = (float)hCtrl.Roll.ExpectOmega;

            Temp_f[16] = (float)hCtrl.Speed.Backward[0];
            Temp_f[17] = (float)hCtrl.Roll.DynamicZero;

            Temp_f[18] = (float)hCtrl.Speed.Forward[0];

            break;
        }
        case 3 :
        {
            Temp_f[0] = (float)PID_YawAngle.pOut;
            Temp_f[1] = (float)PID_YawAngle.iOut;
            Temp_f[2] = (float)PID_YawAngle.dOut;
            Temp_f[3] = (float)PID_YawAngle.out;

            Temp_f[4] = (float)PID_YawOmega.pOut;
            Temp_f[5] = (float)PID_YawOmega.iOut;
            Temp_f[6] = (float)PID_YawOmega.out;

            Temp_f[7] = (float)hCtrl.Speed.Forward[0];
            Temp_f[8] = (float)hCtrl.Speed.Backward[0];//(float)IMUData.yaw_mahony;
            Temp_f[9] = (float)IMUData.gz;

            Temp_f[10] = (float)hCtrl.Yaw.ExpectAngle_Act;
            Temp_f[11] = (float)hCtrl.Yaw.ExpectOmega_Act;
            Temp_f[12] = (float)error;

            break;
        }
        case 4 :
        {
            Temp_f[0] = (float)IMUData.pitch_mahony;
            Temp_f[1] = (float)IMUData.roll_mahony;
            Temp_f[2] = (float)IMUData.yaw_mahony;

            Temp_f[3] = (float)IMUData.gx_Filt;
            Temp_f[4] = (float)IMUData.gy_Filt;
            Temp_f[5] = (float)IMUData.gz_Filt;

            Temp_f[6] = (float)IMUData.ax;
            Temp_f[7] = (float)IMUData.ay;
            Temp_f[8] = (float)IMUData.az;

            Temp_f[9]  = (float)IMUData.gx;
            Temp_f[10] = (float)IMUData.gy;
            Temp_f[11] = (float)IMUData.gz;

            Temp_f[12] = (float)IMUData.gxOffset;
            Temp_f[13] = (float)IMUData.gyOffset;
            Temp_f[14] = (float)IMUData.gzOffset;

            break;
        }
        case 5 :
        {


            break;
        }
        case 6 : //Speed
        {
            Temp_f[0] = hCtrl.Speed.Foot_Ctrl[0];
            Temp_f[1] = hCtrl.Speed.Forward[0];
            Temp_f[2] = hCtrl.Speed.Backward[0];

            break;
        }


        default:
        {
            break;
        }
    }

 /***************最大VOFA_JustFloat_index-1****************************/
    for(unsigned char i =0;i < VOFA_JustFloat_index;i++)
    {
        Float_to_Byte(Temp_f[i],&VOFAdata[i]);
    }
    uart_putbuff(parasent_uart,VOFAdata,sizeof(float) * VOFA_JustFloat_index);
    uart_putbuff(parasent_uart,tail,4);//发帧尾
}


/*********************************************
** Function: m_sqrt
** Description: 正数开根
** Others:无
**********************************************/
unsigned int m_sqrt(unsigned int x)
{
   unsigned char ans = 0,p = 0x80;
   while(p!=0)
     {
     ans+=p;
     if(ans*ans>x)
     {
       ans-=p;
     }
     p=(unsigned char)(p/2);
   }
   return(ans);
}

/******************************************
** Function: Shift_int
** Description: 数组移位
** Others:
*******************************************/
void Shift_int(int *Ptemp,int num)
{
    for(;num > 0;num--)
    {
        *(Ptemp + num) = *(Ptemp + num - 1);
    }
}
void Shift_short_int(short int *Ptemp,short int num)
{
    for(;num > 0;num--)
    {
        *(Ptemp + num) = *(Ptemp + num - 1);
    }
}
void Shift_float(float *Ptemp,int num)
{
    for(;num > 0;num--)
    {
        *(Ptemp + num) = *(Ptemp + num - 1);
    }
}

/*************************************************
** Function: ClearArrayChar ClearArraySignedChar
             ClearArrayInt ClearArrayShortInt
             ClearArrayfloat
** Descripe: 清空数据
** call by : 很多地方--通信，畸变，PID
** Others   :    不同类型数据的清除,Pointertemporary
*************************************************/
void ClearArrayChar(unsigned char *PTemp, unsigned char *PEnd)                  //数组首尾
{
    while (PTemp <= PEnd)
    {
        *(PTemp++) = 0;
    }
}
void ClearArraySignedChar(signed char *PTemp,signed char *PEnd)
{
    while (PTemp <= PEnd)
    {
        *(PTemp++) = 0;
    }
}
void ClearArrayInt(int *PTemp, int *PEnd)
{
    while (PTemp <= PEnd)
    {
        *(PTemp++) = 0;
    }
}
void ClearArrayShortInt(short int *PTemp,short int *PEnd)
{
    while (PTemp <= PEnd)
    {
        *(PTemp++) = 0;
    }
}
void ClearArrayfloat(float *PTemp, float *PEnd)
{
    while (PTemp <= PEnd)
    {
        *(PTemp++) = 0;
    }
}
/*******************************************************
** Function: Linear_Interpolation
** Description: 线性插值
** Others:*Ptemp：数组的起始指针，
** End_Row：一共进行多少行
******************************************************/
void Linear_Interpolation(short int *Ptemp,uint8 End_Row)
{
    uint8 i = 0,j = 0,k = 0;
    for(i = 0;i < End_Row;i++)
    {
        if(*(Ptemp + i) != 0)
        {
            for(j=i+1;j < End_Row ;j++)
            {
                if(*(Ptemp + j) == 0)
                {
                    for(k=j+1;k < End_Row;k++)
                    {
                        if(*(Ptemp + k)!=0)
                        {
                            *(Ptemp + j) = (int)(*(Ptemp + j - 1) + (*(Ptemp + k) - *(Ptemp + j - 1))/((k-j+1) * 1.0));
                            break;
                        }
                    }
                }
            }
            break;
        }
    }
}

/*************************************************
Function: Get_Theta
Description: 求直线夹角
Calls:   无
Called By: GetInfor.c   control.c
Table Accessed: 无
Table Updated: 无
Input: K1
       K2
       Type: 1锐角 2钝角

Return: Theta
Others:无
*************************************************/
uint8 Get_Theta(float K1, float K2, uint8 Type)
{
    float Tan = 0.0;
    int Up = 0.0;
    int Down = 0.0;

    uint8 Theta = 0;
//    k1 = 1000 * K1;
//    k2 = 1000 * K2;
    Up = 1000 * (K2 - K1);
    Down = 1000 * (1 + K1 * K2);

    Tan =  ABS(1.0 * Up / Down) ;

    Theta = atan(Tan) * 57;

    Theta = Type == 1 ? Theta : (180 - Theta);
    return Theta;
}

/*************************************************
Function: Get_ExpSlope
Description: 求已知斜率与夹角，求另外一条直线的斜率
Calls:   无
Called By: GetInfor.c   control.c
Table Accessed: 无
Table Updated: 无
Input: K1
       Theta
       Type: 1锐角 2钝角

Return: ThetaExp
Others:无
*************************************************/
float Get_ExpSlope(float K1, int Theta, uint8 Type)
{
    float Tan = tan(Theta / 57.0);    //弧度转角度
    float ThetaExp = 0.0;

    float Up = Tan + K1;
    float Down = 1 - Tan * K1;

    ThetaExp = Up / Down;
    return ThetaExp;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数名称     m_sqrt
// 函数简介     正整数开根
// 参数说明     x         被开根数
// 使用示例     ans = m_sqrt(16);
// 备注信息
// Author    zxx
//-------------------------------------------------------------------------------------------------------------------
//unsigned int m_sqrt(unsigned int x)
//{
//   unsigned char ans = 0,p = 0x80;
//   while(p!=0)
//  {
//     ans+=p;
//     if(ans*ans>x)
//     {
//       ans-=p;
//     }
//     p=(unsigned char)(p/2);
//   }
//   return(ans);
//}
//-------------------------------------------------------------------------------------------------------------------
// 函数名称     SquareRootFloat
// 函数简介     浮点型开根
// 参数说明     number         被开根数
// 使用示例     ans = SquareRootFloat(16);
// 备注信息
// Author    zxx
//-------------------------------------------------------------------------------------------------------------------
float SquareRootFloat(float number)
{
    long i;
    float x, y;
    const float f = 1.5F;

    x = number * 0.5F;
    y = number;
    i = * ( long * ) &y;
    i = 0x5f3759df - ( i >> 1 );
    y = * ( float * ) &i;
    y = y * ( f - ( x * y * y ) );
    y = y * ( f - ( x * y * y ) );
    return number * y;
}


boolean Buffercmp(uint8_t *Buf1, uint8_t *Buf2, uint16_t BufLength)
{
    while(BufLength--)
    {
        if(*Buf1 != *Buf2)
        {
            return FALSE;
        }
        Buf1++;
        Buf2++;
    }
    return TRUE;
}
