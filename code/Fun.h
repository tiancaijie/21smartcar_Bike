#ifndef __FUN_H
#define __FUN_H

#include "zf_common_headfile.h"

/* =========== 宏定义 ============= */
#define ABS(x)                          (((x) >= (0.0f)) ? (x) : (-(x)))
#define Data_Limit(Value,Dowm,Up)       ((Value) < (Dowm) ? (Dowm) : ((Value) > (Up) ? (Up) : (Value)))
#define Amplitude_Limit(Value,Dowm,Up)  ((Value) < (Dowm) ? (Dowm) : ((Value) > (Up) ? (Up) : (Value)));
#define Step_Limit(New,Old,Range)       (New > (Old + Range) ? (Old + Range) : (New < (Old - Range) ? (Old - Range) : (New)))
#define Increase_Limit(var, limit)      var = (++var) > limit ? (limit+1) : var

#define Deg2Rad(deg)                    ((double)(deg) * 0.0174532925)
#define Rad2Deg(rad)                    ((double)(rad) * 57.295779513))
#define parasent_uart                   UART_1
/* ========= 全局变量声明 ========== */


/* =========== 函数声明 ============ */

void Get_BackSpeed(void);
void CheckVoltage(void);
void Shift_int(int *Ptemp,int num);
void Shift_short_int(short int *Ptemp,short int num);
void Shift_float(float *Ptemp,int num);
void ClearArrayChar(unsigned char *PTemp, unsigned char *PEnd);
void ClearArraySignedChar(signed char *PTemp,signed char *PEnd);
void ClearArrayInt(int *PTemp, int *PEnd);
void ClearArrayShortInt(short int *PTemp,short int *PEnd);
void ClearArrayfloat(float *PTemp, float *PEnd);
void VOFA_ParameterSent(void);

float SquareRootFloat(float number);

#endif /* __FUN_H */
