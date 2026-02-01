#ifndef __UI_H
#define __UI_H

#include "OLEDkeyboard_Config.h"

/*================宏定义================*/


/*===============外部变量===============*/
/*===============函数声明===============*/
int32 KeyboardInput(uint16 x,uint16 y, TextSize_TypeDef TextSize, float factor);
int32 KeyboardInput_with_Flash(uint16 x,uint16 y, TextSize_TypeDef TextSize, float factor, uint16 sector, uint16 page);
float KeyboardInput_with_Flash_Float(uint16 x,uint16 y, TextSize_TypeDef TextSize, float factor, uint16 sector, uint16 page);
uint8 ShowSwitch(uint16 x,uint16 y, TextSize_TypeDef TextSize, uint16 sector, uint16 page);
uint8 ShowSwitch_with_Flash(uint16 x,uint16 y, TextSize_TypeDef TextSize, uint16 sector, uint16 page);
//void PID_Config(PID_InitTypeDef *PID_InitStruct);

#endif /*__UI_H*/

