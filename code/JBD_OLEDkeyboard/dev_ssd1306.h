/*************************************************
Copyright (C), 2016-2020, TYUT JBD TEAM C.
File name: ssd1306.h
Author: TEAM  A B C
Version:0.0               Date: 2016.11.12
Description:  ssd1306.h
Others:      无
Function List:
History:
<author>  <time>      <version > <desc>
JBD       2016.10.21  0.0        初始
AmaZzzing 2016.11.12  1.0        初步完成构架
双车&信标   2020.6.1    儿童节版      兼容英飞凌
**************************************************/
#ifndef __SSD1306_H
#define __SSD1306_H

#include "OLEDkeyboard_Config.h"

/************************************宏定义************************************/
#define num2ascll(x)    ('0'+(x))
#define SignOf(Value)   (((Value) < 0.0) ? (-1.0) : (1.0))

#define OLED_CLS(void)  OLED_Fill(0x00)     //清屏
/*********************************全局变量声明*********************************/

/***********************************函数声明***********************************/
void OLED_Cmd(uint8 cmd);
void OLED_Dat(uint8 data);
void OLED_Init(void);
void OLED_SetPos(uint8 x,uint8 y);
void OLED_Fill(uint8 fill_Data);
void OLED_Show_Char(uint16 x, uint16 y, char str, TextSize_TypeDef TextSize);
void OLED_Show_Str(uint16 x, uint16 y, uint8 ch[], TextSize_TypeDef TextSize);
void OLED_Show_OneNumber(uint16 x,uint16 y, uint8 num, TextSize_TypeDef TextSize);
void OLED_Show_Numbers(uint16 x, uint16 y, int32 Value, TextSize_TypeDef TextSize);
void OLED_Show_float(uint16 x, uint16 y, double dat, uint8 pointnum, TextSize_TypeDef TextSize);

#endif
