#include "OLEDkeyboard_Config.h"
#include "UI.h"


/*************************************************
Function: KeyboardInput
Description:键盘输入    (最多5位)
Details：factor 系数，输入的数在返回时将会乘的系数，1.0为不变
*************************************************/
int32 KeyboardInput(uint16 x,uint16 y, TextSize_TypeDef TextSize, float factor) //（without Flash）
{
    int KeyValue = KEY_BLANK;   //输入的新数字
    int KeyValue_old;
    int NewVlaue = 0;           //输入区显示出来的数字
    
    /*先在要输入信息的位置显示一行0*/
    OLED_Show_Numbers(x, y, 0, TextSize);

    while(KeyValue != KEY_ENTER)
    {
        KeyValue_old = KeyValue;
        KeyValue = CH455_GetOneKey();
        
        /*当前不对长按进行特殊处理*/
        if(KeyValue > 0x0F && KeyValue != KEY_BLANK)
        {
            KeyValue = (KeyValue - 0x0F) >> 4;
        }
        
        /* 直接跳过的情况取 0 */
        if(KeyValue_old == KEY_BLANK && (KeyValue == KEY_ENTER || KeyValue == KEY_ENTER_Long))
        {
            NewVlaue = 0;
        }
        
        /****************************输入数字可退格****************************/
        if(KeyValue != KEY_BACK && KeyValue != KEY_ENTER && KeyValue != KEY_BLANK)   //输入数值
        {
            if(NewVlaue / 10000 != 0)       //只保留四位
            {
                NewVlaue = NewVlaue % 10000;
            }
            
            NewVlaue = NewVlaue * 10 + KeyValue;      //新输入的数字放到个位
        }
        else if(KeyValue == KEY_BACK)    //退格
        {
            NewVlaue = NewVlaue / 10;     //最后一位去掉
        }
        
        OLED_Show_Numbers(x, y, NewVlaue, TextSize);   //显示当前值
    }
    
    NewVlaue *= factor;
    
    return NewVlaue;
}

/*************************************************
Function: KeyboardInput_with_Flash
Description:键盘输入并存入Flash    (最多5位)
Details：大号字体显示四位数，小号字体显示五位
*************************************************/
int32 KeyboardInput_with_Flash(uint16 x,uint16 y, TextSize_TypeDef TextSize, float factor, uint16 sector, uint16 page)
{
    int KeyValue = KEY_BLANK;    //输入的新数字
    int KeyValue_old;
    int NewVlaue = 0;           //输入区显示出来的数字
    
    /*先在要输入信息的位置显示一行0*/
    OLED_Show_Numbers(x, y, 0, TextSize);
    
    while(KeyValue != KEY_ENTER)
    {
        KeyValue_old = KeyValue;
        KeyValue = CH455_GetOneKey();
        
        /* 当前不对长按进行特殊处理 */
        if(KeyValue > 0x0F && KeyValue != KEY_BLANK)
        {
            KeyValue = (KeyValue - 0x0F) >> 4;
        }
        
        /* 直接跳过的情况保留原值 */
        if(KeyValue_old == KEY_BLANK && (KeyValue == KEY_ENTER || KeyValue == KEY_ENTER_Long))
        {
            NewVlaue = flash_read(Backup_Sector, page, int32);
        }
        
        
        
        /****************************输入数字可退格****************************/
        if(KeyValue != KEY_BACK && KeyValue != KEY_ENTER && KeyValue != KEY_BLANK)   //输入数值
        {
            if(NewVlaue / 10000 != 0)       //只保留5位
            {
                NewVlaue = NewVlaue % 10000;
            }

            NewVlaue = NewVlaue * 10 + KeyValue;      //新输入的数字放到个位
        }
        else if(KeyValue == KEY_BACK)    //退格
        {
            NewVlaue = NewVlaue / 10;     //最后一位去掉
        }

        OLED_Show_Numbers(x, y, NewVlaue, TextSize);   //显示当前值
    }

    NewVlaue *= factor;

    EEPROM_Write_32Bit(sector, page, NewVlaue);//以uint32类型向指定扇区的指定页写入NewVlaue);

    return NewVlaue;
}


/*************************************************
Function: KeyboardInput_with_Flash
Description:键盘输入并存入Flash    (最多5位)
Details：大号字体显示四位数，小号字体显示五位
*************************************************/
float KeyboardInput_with_Flash_Float(uint16 x,uint16 y, TextSize_TypeDef TextSize, float factor, uint16 sector, uint16 page)
{
    int KeyValue = KEY_BLANK;    //输入的新数字
    int KeyValue_old;
    float NewVlaue = 0;           //输入区显示出来的数字

    /*先在要输入信息的位置显示一行0*/
    OLED_Show_Numbers(x, y, 0, TextSize);

    while(KeyValue != KEY_ENTER)
    {
        KeyValue_old = KeyValue;
        KeyValue = CH455_GetOneKey();

        /* 当前不对长按进行特殊处理 */
        if(KeyValue > 0x0F && KeyValue != KEY_BLANK)
        {
            KeyValue = (KeyValue - 0x0F) >> 4;
        }

        /* 直接跳过的情况保留原值 */
        if(KeyValue_old == KEY_BLANK && (KeyValue == KEY_ENTER || KeyValue == KEY_ENTER_Long))
        {
            NewVlaue = EEPROM_Read_Float(Backup_Sector, page)/factor;
        }


        /****************************输入数字可退格****************************/
        if(KeyValue != KEY_BACK && KeyValue != KEY_ENTER && KeyValue != KEY_BLANK)   //输入数值
        {
            if(NewVlaue / 10000 != 0)       //只保留5位
            {
                NewVlaue = (int)NewVlaue % 10000;
            }
            
            NewVlaue = NewVlaue * 10 + KeyValue;      //新输入的数字放到个位
        }
        else if(KeyValue == KEY_BACK)    //退格
        {
            NewVlaue = NewVlaue / 10;     //最后一位去掉
        }
        
        OLED_Show_Numbers(x, y, NewVlaue, TextSize);   //显示当前值
    }
    
    NewVlaue *= factor;
    
    
    EEPROM_Write_Float(sector, page, NewVlaue);//以float类型向指定扇区的指定页写入NewVlaue);

    return NewVlaue;
}


/*************************************************
Function: ShowSwitch
Description:显示开关量的状态
Details：无
*************************************************/
uint8 ShowSwitch(uint16 x,uint16 y, TextSize_TypeDef TextSize, uint16 sector, uint16 page)
{
    uint8 switch_status;              //变量开关标志
    switch_status = flash_read(sector, page, boolean) ? Switch_ON : Switch_OFF;

    switch(TextSize)
    {
        case TextSize_GUI_switch_16x8:  /*小号*/
        {
            OLED_SetPos(x,y);       //给定坐标
            for(int i=0;i<16;i++)   //先显示上半部分
                OLED_Dat(GUI_switch_16x8[switch_status][i]);
            break;
        }
        case TextSize_GUI_switch_22x16: /*大号*/
        {
            OLED_SetPos(x,y);       //给定坐标（上半部分）
            for(int i=0;i<22;i++)   //先显示上半部分
                OLED_Dat(GUI_switch_22x16[switch_status*2 + 0][i]);
            OLED_SetPos(x,y+1);     //给定坐标（下半部分）
            for(int i=0;i<22;i++)   //再显示下半部分
                OLED_Dat(GUI_switch_22x16[switch_status*2 + 1][i]);
            break;
        }
        default:
        {
            OLED_SetPos(x,y);       //给定坐标
            for(int i=0;i<16;i++)   //先显示上半部分
                OLED_Dat(GUI_switch_16x8[switch_status][i]);
            break;
        }
    }
    
    
    return switch_status;
}

/*************************************************
Function: ShowSwitch_with_Flash
Description:更改并保存开关变量的状态
Details：无
*************************************************/
uint8 ShowSwitch_with_Flash(uint16 x,uint16 y, TextSize_TypeDef TextSize, uint16 sector, uint16 page)
{
                     
    uint8 KeyNum = KEY_BLANK;         //键盘检测
    uint8 switch_status = Switch_OFF;        //变量开关标志

    switch_status = flash_read(Backup_Sector, page, boolean) ? Switch_ON : Switch_OFF;


    while(KeyNum != KEY_ENTER && KeyNum != KEY_ENTER_Long)
    {
        /*******************************状态显示*******************************/
        switch(TextSize)
        {
            case TextSize_GUI_switch_16x8:  /*小号*/
            {
                OLED_SetPos(x,y);       //给定坐标
                for(int i=0;i<16;i++)   //先显示上半部分
                    OLED_Dat(GUI_switch_16x8[switch_status][i]);
                break;
            }
            case TextSize_GUI_switch_22x16: /*大号*/
            {
                OLED_SetPos(x,y);       //给定坐标（上半部分）
                for(int i=0;i<22;i++)   //先显示上半部分
                    OLED_Dat(GUI_switch_22x16[switch_status*2 + 0][i]);
                OLED_SetPos(x,y+1);     //给定坐标（下半部分）
                for(int i=0;i<22;i++)   //再显示下半部分
                    OLED_Dat(GUI_switch_22x16[switch_status*2 + 1][i]);
                break;
            }
            default:
            {
                OLED_SetPos(x,y);       //给定坐标
                for(int i=0;i<16;i++)   //先显示上半部分
                    OLED_Dat(GUI_switch_16x8[switch_status][i]);
                break;
            }
        }
        /*******************************按键识别*******************************/
        
        KeyNum = CH455_GetOneKey();
        
        /* 确认键 */
        if(KeyNum != KEY_ENTER && KeyNum != KEY_ENTER_Long)
        {
            switch_status = 1 - switch_status;
        }
        
    }/* 按键控制 */
    
    EEPROM_Write_32Bit(sector, page, switch_status);

    return switch_status;
}



///*************************************************
//Function: PID_Config
//Description:PID初始化结构体参数修改
//Details：结构体中 index 用于标记结构体对应的PID的参数存在flash中的哪个地方，一个index对应十个字的空间，使用分布如下
//        高页数-->                                                                    -->低页数
//        -------------------------------------------------------------------------------------
//        | kp    | ki    | kd    | iOutMax | outMax  | NULL  | NULL  | NULL  | 验证    | NULL  |
//        -------------------------------------------------------------------------------------
//
//        存入flash里的是各个参数的输入值 如ki = 100 为输入100 实际起作用为0.1
//
//*************************************************/
//void PID_Config(PID_InitTypeDef *PID_InitStruct)
//{
//    if(PID_InitStruct == NULL)
//    {
//        return;
//    }
//
//    int16 headpage;                                                                     //flash读写基础值
//    PID_InitTypeDef tempBuffer;
//
//    headpage = 1023 - ((PID_InitStruct->index - 1) * 10);
//    if(headpage < 0)
//    {
//        return;
//    }
//
//    //读取之前存在flash里的数据
//    tempBuffer.kp           = flash_read(Backup_Sector, headpage - 0, float);
//    tempBuffer.ki           = flash_read(Backup_Sector, headpage - 1, float);
//    tempBuffer.kd           = flash_read(Backup_Sector, headpage - 2, float);
//    tempBuffer.iOutMax      = flash_read(Backup_Sector, headpage - 3, float);
//    tempBuffer.outMax       = flash_read(Backup_Sector, headpage - 4, float);
//
//    //界面显示
//    OLED_CLS();
//
//    OLED_Show_Str(0, 0, (PID_InitStruct->name), TextSize_F6x8);                        //显示当前调整的pid的名称
//
//    OLED_Show_Str(0, 2, "kp"        , TextSize_F6x8);
//    OLED_Show_Str(0, 3, "ki"        , TextSize_F6x8);
//    OLED_Show_Str(0, 4, "kd"        , TextSize_F6x8);
//    OLED_Show_Str(0, 5, "iOutMax"   , TextSize_F6x8);
//    OLED_Show_Str(0, 6, "outMax"    , TextSize_F6x8);
//
//    OLED_Show_Numbers(First_X, 2, tempBuffer.kp     , TextSize_F6x8);
//    OLED_Show_Numbers(First_X, 3, tempBuffer.ki     , TextSize_F6x8);
//    OLED_Show_Numbers(First_X, 4, tempBuffer.kd     , TextSize_F6x8);
//    OLED_Show_Numbers(First_X, 5, tempBuffer.iOutMax, TextSize_F6x8);
//    OLED_Show_Numbers(First_X, 6, tempBuffer.outMax , TextSize_F6x8);
//
//    KeyboardInput_with_Flash(Second_X, 2, TextSize_F6x8, 1.0, 2, headpage - 0);
//    KeyboardInput_with_Flash(Second_X, 3, TextSize_F6x8, 1.0, 2, headpage - 1);
//    KeyboardInput_with_Flash(Second_X, 4, TextSize_F6x8, 1.0, 2, headpage - 2);
//    KeyboardInput_with_Flash(Second_X, 5, TextSize_F6x8, 1.0, 2, headpage - 3);
//    KeyboardInput_with_Flash(Second_X, 6, TextSize_F6x8, 1.0, 2, headpage - 4);
//
////    所有的参数都正常输完之后则向倒数第二个位写入验证码 8741，表示该pid的参数输入完毕
////    所有的参数都正常输完之后则向倒数第二个位写入验证码0923，表示该pid的参数输入完毕
//    EEPROM_Write_32Bit(2, headpage - 8, 8741);
//
//}

