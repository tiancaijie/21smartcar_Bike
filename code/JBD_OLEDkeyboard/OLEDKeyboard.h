/*************************************************
Copyright (C), 2016-2020, TYUT JBD TEAM C.
File name: OLEDKeyboard.h
Author: TEAM  A B C
Version:0.0               Date: 2016.11.12
Description:  OLEDKeyboard.h
Others:      无
Function List:
History:
<author>  <time>      <version > <desc>
JBD       2016.10.21  0.0        初始
AmaZzzing 2016.11.12  1.0        初步完成构架
双车&信标   2020.6.1    儿童节版      兼容英飞凌
**************************************************/
#ifndef __OLEDKEYBOARD_H
#define __OLEDKEYBOARD_H

#include "OLEDkeyboard_Config.h"
#include "pid.h"
#include "zf_common_headfile.h"

/*********************************全局变量声明*********************************/

#define Speed_Sector  10

/***********************************函数声明***********************************/
void Oled_Input(void);
void Oled_Display(void);
void OLED_Runing_show(void);
void OLED_RuningDBG(void);

#endif

