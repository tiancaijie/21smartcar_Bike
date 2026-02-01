#include "Map.h"



Navigation_Handle_TypeDef Navigation = {
                                        .current.MapCount   = 1,
                                        .current.k          = 0.25,
                                        .SpdExp_Far  = 400,
                                        .SpdExp_Near = 200,

                                        .Map.Point_Num      = 1,

                                        .MarkPot.Point_Order = 1,
                                        .MarkPot.Mode       = No_MarkMode,

                                       };

void Hand_PotRecord(void)
{
    KeyValue_enum key;

    OLED_Show_Numbers(First_X,0,Navigation.MarkPot.Point_Order, TextSize_F6x8);
    OLED_Show_float(First_X,2,Navigation.current.X ,4,TextSize_F6x8);
    OLED_Show_float(First_X,4,Navigation.current.Y ,4, TextSize_F6x8);
    OLED_Show_float(First_X,6,Navigation.current.Azimuth,4,TextSize_F6x8);

    key = CH455_QueryOneKey(60);
    if(KEY_1 == key)
    {
        hCtrl.GlobalFlag.Mark_Point_Flag = On;
        EEPROM_Write_Float(MP_sector, MP_Start_Page - (Navigation.MarkPot.Point_Order-1)*3-1, Navigation.current.X);
        EEPROM_Write_Float(MP_sector, MP_Start_Page - (Navigation.MarkPot.Point_Order-1)*3-2, Navigation.current.Y);
        EEPROM_Write_32Bit(MP_sector, MP_Start_Page - (Navigation.MarkPot.Point_Order-1)*3-3, 0);
        Navigation.MarkPot.Point_Order++;
    }
    if(KEY_ENTER == key)
    {
        hCtrl.GlobalFlag.Mark_Point_Flag = On;
        EEPROM_Write_32Bit(MP_sector, MP_Start_Page, Navigation.MarkPot.Point_Order-1);
    }

}


