/*************************************************
oled.show
**************************************************/
#include "OLEDkeyboard.h"

/* ========= 全局变量定义 ========== */
//const uint8 *menu_1[12] = {"Speed"    ,"OffsetR"    ,"OffsetP"      ,"gyro_Z"   ,
//                          "Duty_Ser"  ,"Duty_fly"   ,"Duty_back"    ,"Null"     ,
//                          "NULL"      ,"0_Spd"      ,"0_dir"        ,"0_Ang"    ,
//                          };
//
//const uint8 *menu_2[12] = {"BackWheel","Ser_Switch","Duty_test"  ,"Yaw_Ctrl",
//                           "RCctrl"   ,"0Test"     ,"0use"   ,"Big_Ctrl",
//                           "Switch9"  ,"Switch10"  ,"Switch11"  ,"Switch12"};
//
//const uint8 *menu_6[12] = {"k","d","c1","c2",
//                          "Max", "Normal", "Min", "NULL",
//                          "Cir_L", "Cir_R", "Spd_Cir", "Spd_Ram"};
//
//
//const uint8 *menu_7[12] = {"1.Speed"    ,"3.PID"    ,"5.RC",  "7.RMCmsg", "9.Markers", "11.Elements",
//                          "2.Angle"    ,"4.Vpp"    ,"6.Run", "8.GPSdata", "10.RUN"};


uint8 oled_display_option = 0;

/* ========= 内部函数声明  ========== */
static void Load_PID_Flash(void);
static void Load_Show_Flash(void);
static void Load_Switch_Flash(void);
static void Load_Config_Flash(void);
static void Load_Angle_Offset(void);
static void Load_ALL(void);
/*************************************************
Function: PID_Config
Description:PID初始化结构体参数修改
Details：结构体中 index 用于标记结构体对应的PID的参数存在flash中的哪个地方，一个index对应十个字的空间，使用分布如下
        高页数-->                                                                    -->低页数
        ------------------------------------------------------------------------------------------
        | kp    | ki    | kd    | iOutMax | outMax  | ZeroOutFlag  | NULL  | NULL  | 验证    | NULL  |
        --------------------------------------------------------------------------------------------

        存入flash里的是各个参数的输入值 如ki = 100 为输入100 实际起作用为0.1

*************************************************/
void PID_Config(PID_InitTypeDef *PID_InitStruct)
{
    if(PID_InitStruct == NULL)
    {
        return;
    }

    int16 headpage;                                                                     //flash读写基础值
    PID_InitTypeDef tempBuffer;

    headpage = 1023 - ((PID_InitStruct->index - 1) * 10);
    if(headpage < 0)
    {
        return;
    }

    //读取之前存在flash里的数据
    tempBuffer.kp           = flash_read(Backup_Sector, headpage - 0, float);
    tempBuffer.ki           = flash_read(Backup_Sector, headpage - 1, float);
    tempBuffer.kd           = flash_read(Backup_Sector, headpage - 2, float);
    tempBuffer.iOutMax      = flash_read(Backup_Sector, headpage - 3, float);
    tempBuffer.outMax       = flash_read(Backup_Sector, headpage - 4, float);
    tempBuffer.ZeroOutFlag  = flash_read(Backup_Sector, headpage - 5, float);
    //界面显示
    OLED_CLS();

    OLED_Show_Str(0, 0, (PID_InitStruct->name), TextSize_F6x8);                        //显示当前调整的pid的名称

    OLED_Show_Str(0, 2, "kp"        , TextSize_F6x8);
    OLED_Show_Str(0, 3, "ki"        , TextSize_F6x8);
    OLED_Show_Str(0, 4, "kd"        , TextSize_F6x8);
    OLED_Show_Str(0, 5, "iOutMax"   , TextSize_F6x8);
    OLED_Show_Str(0, 6, "outMax"    , TextSize_F6x8);
    OLED_Show_Str(0, 7, "ZeroOut"   , TextSize_F6x8);

    OLED_Show_Numbers(First_X, 2, tempBuffer.kp          , TextSize_F6x8);
    OLED_Show_Numbers(First_X, 3, tempBuffer.ki          , TextSize_F6x8);
    OLED_Show_Numbers(First_X, 4, tempBuffer.kd          , TextSize_F6x8);
    OLED_Show_Numbers(First_X, 5, tempBuffer.iOutMax     , TextSize_F6x8);
    OLED_Show_Numbers(First_X, 6, tempBuffer.outMax      , TextSize_F6x8);
    OLED_Show_Numbers(First_X, 6, tempBuffer.outMax      , TextSize_F6x8);
    OLED_Show_Numbers(First_X, 7, tempBuffer.ZeroOutFlag , TextSize_F6x8);

    KeyboardInput_with_Flash(Second_X, 2, TextSize_F6x8, 1.0, PID_Sector, headpage - 0);
    KeyboardInput_with_Flash(Second_X, 3, TextSize_F6x8, 1.0, PID_Sector, headpage - 1);
    KeyboardInput_with_Flash(Second_X, 4, TextSize_F6x8, 1.0, PID_Sector, headpage - 2);
    KeyboardInput_with_Flash(Second_X, 5, TextSize_F6x8, 1.0, PID_Sector, headpage - 3);
    KeyboardInput_with_Flash(Second_X, 6, TextSize_F6x8, 1.0, PID_Sector, headpage - 4);
    KeyboardInput_with_Flash(Second_X, 7, TextSize_F6x8, 1.0, PID_Sector, headpage - 5);

//    所有的参数都正常输完之后则向倒数第二个位写入验证码 8741，表示该pid的参数输入完毕
//    所有的参数都正常输完之后则向倒数第二个位写入验证码0923，表示该pid的参数输入完毕
    EEPROM_Write_32Bit(PID_Sector, headpage - 8, 8741);

}


/*************************************
** Function: Oled_Input
** Description: 开机显示
** Others:无 state
*************************************/
void Oled_Input(void)
{
    unsigned char SectorNum = 0;    //初始化扇区
    int KeyNumber_Flash = 0;
    uint16 Flash_value = 0;
    uint16 Oled_menu_choose = 0;

    OLED_CLS(); //清屏
/******************************开机电压检测***************************************************/

    int lfBattery_v = 0;

    for(char i = 0;i<5;i++)
    {
        lfBattery_v += adc_convert(Battery_Power_Pin);
    }
    lfBattery_v =lfBattery_v / 5;

    OLED_Show_Numbers(40, 0, lfBattery_v,TextSize_F8x16);
    if(lfBattery_v > 2640)
    {
        OLED_Show_Str(20, 2, "High Power", TextSize_F8x16);

    }
    else if(lfBattery_v>2400)//还能降到2400
    {
        OLED_Show_Str(20, 2, "Medium Power", TextSize_F8x16);
    }
    else
    {
        OLED_Show_Str(20, 2, "Error!!!", TextSize_F8x16);
        OLED_Show_Str(20, 4, "LOW Power", TextSize_F8x16);
    }


    KeyboardInput(88, 6, TextSize_F8x16, 1.0);
    OLED_CLS(); //清屏
/******************************显示除零漂结果***************************************************/


    //打印主菜单
      OLED_CLS();
      /* 第一列 */                                                             /* 第二列 */


      OLED_Show_Str(0, 0, "1 MotorSet", TextSize_F6x8);     OLED_Show_Str(70, 0, "9 PotHand" , TextSize_F6x8);
      OLED_Show_Str(0, 1, "2 Threshold"     , TextSize_F6x8);     OLED_Show_Str(70, 1, "10 Speed", TextSize_F6x8);
      OLED_Show_Str(0, 2, "3 ShowSend", TextSize_F6x8);     OLED_Show_Str(70, 2, "11 ReOff", TextSize_F6x8);
      OLED_Show_Str(0, 3, "4 Balance" , TextSize_F6x8);
      OLED_Show_Str(0, 4, "5 PID"     , TextSize_F6x8);
      OLED_Show_Str(0, 5, "6 Reoffset", TextSize_F6x8);
      OLED_Show_Str(0, 6, "7 TurnSet" , TextSize_F6x8);
      OLED_Show_Str(0, 7, "8 PotInpu" , TextSize_F6x8);

      Oled_menu_choose = KeyboardInput(88, 6, TextSize_F6x8, 1.0);
      OLED_CLS();

      SectorNum = Oled_menu_choose;//扇区号

      switch(Oled_menu_choose)
      {
          case 1:                //Motor_set
          {
              Flash_Data_Move(SectorNum, Backup_Sector);          //将此扇区数据备份到备份扇区
              EEPROM_Write_32Bit(Backup_Sector, 0, SectorNum);    //记录开始输入数据标志
              EEPROM_EraseSector(SectorNum);                      //擦除

              OLED_CLS(); //清屏

              OLED_Show_Str(0,0,"forwspd",TextSize_F6x8);      OLED_Show_Numbers(First_X, 0, flash_read(Backup_Sector, 1023, uint32),TextSize_F6x8);
              OLED_Show_Str(0,1,"forwdir",TextSize_F6x8);      OLED_Show_Numbers(First_X, 1, flash_read(Backup_Sector, 1022, uint32),TextSize_F6x8);
              OLED_Show_Str(0,2,"backspd",TextSize_F6x8);      OLED_Show_Numbers(First_X, 2, flash_read(Backup_Sector, 1021, uint32),TextSize_F6x8);
              OLED_Show_Str(0,3,"backdir",TextSize_F6x8);      OLED_Show_Numbers(First_X, 3, flash_read(Backup_Sector, 1020, uint32),TextSize_F6x8);
              OLED_Show_Str(0,4,"footspd",TextSize_F6x8);      OLED_Show_Numbers(First_X, 4, flash_read(Backup_Sector, 1019, uint32),TextSize_F6x8);
              OLED_Show_Str(0,5,"footdir",TextSize_F6x8);      OLED_Show_Numbers(First_X, 5, flash_read(Backup_Sector, 1018, uint32),TextSize_F6x8);

              hCtrl.Debug.OK_ForwardWheel_spd     = KeyboardInput_with_Flash(Second_X, 0,TextSize_F6x8,1.0,SectorNum, 1023);
              hCtrl.Debug.OK_ForwardWheel_dir     = KeyboardInput_with_Flash(Second_X, 1,TextSize_F6x8,1.0,SectorNum, 1022);
              hCtrl.Debug.OK_BackwardWheel_spd    = KeyboardInput_with_Flash(Second_X, 2,TextSize_F6x8,1.0,SectorNum, 1021);
              hCtrl.Debug.OK_BackwardWheel_dir    = KeyboardInput_with_Flash(Second_X, 3,TextSize_F6x8,1.0,SectorNum, 1020);
              hCtrl.Debug.OK_FootWheel_spd        = KeyboardInput_with_Flash(Second_X, 4,TextSize_F6x8,1.0,SectorNum, 1019);
              hCtrl.Debug.OK_FootWheel_dir        = KeyboardInput_with_Flash(Second_X, 5,TextSize_F6x8,1.0,SectorNum, 1018);

              hCtrl.Debug.speed_debug = 1;
              EEPROM_Write_32Bit(Backup_Sector, 1, SectorNum);//记录结束输入数据标志
              OLED_CLS();
                break;
          }
          case 2:     //Threshold
          {
              Flash_Data_Move(SectorNum, Backup_Sector);          //将此扇区数据备份到备份扇区
              EEPROM_Write_32Bit(Backup_Sector, 0, SectorNum);    //记录开始输入数据标志
              EEPROM_EraseSector(SectorNum);                      //擦除

              OLED_Show_Str(0,0,"NewThreshold",TextSize_F6x8);
              OLED_Show_Numbers(0,1,(flash_read(Backup_Sector, 1023, uint32)),TextSize_F6x8);
              OLED_Show_Str(0,2,"Weight",TextSize_F6x8);
              OLED_Show_Numbers(0,3,(flash_read(Backup_Sector, 1022, uint32)),TextSize_F6x8);
              OLED_Show_Str(0,4,"Delay",TextSize_F6x8);
              OLED_Show_Numbers(0,5,(flash_read(Backup_Sector, 1021, uint32)),TextSize_F6x8);

              hCtrl.Start_Run.Delay_Limit = KeyboardInput_with_Flash(Second_X,6, TextSize_F6x8, 1.0, SectorNum, 1021);
              OLED_CLS();
              EEPROM_Write_32Bit(Backup_Sector, 1, SectorNum);//记录结束输入数据标志
              break;

          }
          case 3: //Show and Send
          {
              Flash_Data_Move(SectorNum, Backup_Sector);          //将数据备份到备份扇区
              EEPROM_Write_32Bit(Backup_Sector, 0, SectorNum);    //记录开始输入数据标志
              EEPROM_EraseSector(SectorNum);     //擦除

              OLED_Show_Str(6, 0, "Show What", TextSize_F6x8);   OLED_Show_Numbers(Second_X, 0, flash_read(Backup_Sector, 1023, uint32),TextSize_F6x8);
              OLED_Show_Str(0, 2, "1 speed"  , TextSize_F6x8);   OLED_Show_Str(Second_X, 2, "4 IMU"  , TextSize_F6x8);
              OLED_Show_Str(0, 4, "2 image"    , TextSize_F6x8);   OLED_Show_Str(Second_X, 4, "5 pot"     , TextSize_F6x8);
              OLED_Show_Str(0, 6, "3 image2", TextSize_F6x8);
              hCtrl.Debug.Oled_Show = KeyboardInput_with_Flash(Second_X,6,TextSize_F6x8, 1.0,SectorNum,1023);

              OLED_CLS();
              OLED_Show_Str(0, 0, "Send What", TextSize_F6x8);     OLED_Show_Numbers(Second_X, 0, flash_read(Backup_Sector, 1022, uint32),TextSize_F6x8);
              OLED_Show_Str(0, 2, "1 Pitch"  , TextSize_F6x8);
              OLED_Show_Str(0, 3, "2 Roll"   , TextSize_F6x8);
              OLED_Show_Str(0, 4, "3 Yaw"    , TextSize_F6x8);
              OLED_Show_Str(0, 5, "4 IMU", TextSize_F6x8);
              OLED_Show_Str(0, 6, "5 Odo", TextSize_F6x8);
              OLED_Show_Str(0, 7, "6 Speed", TextSize_F6x8);  hCtrl.Debug.Param_send=KeyboardInput_with_Flash(Second_X,7,TextSize_F6x8, 1.0,SectorNum,1022);
              OLED_CLS();
              EEPROM_Write_32Bit(Backup_Sector, 1, SectorNum);//记录结束输入数据标志
              break;
          }
          case 4://Balance_Point
          {
              Flash_Data_Move(SectorNum, Backup_Sector);          //将数据备份到备份扇区
              EEPROM_Write_32Bit(Backup_Sector, 0, SectorNum);    //记录开始输入数据标志
              EEPROM_EraseSector(SectorNum);     //擦除
              hCtrl.Pitch.BalanceSign = flash_read(Backup_Sector, 1023, uint32);
              hCtrl.Pitch.BalancePoint = (hCtrl.Pitch.BalanceSign == 0 ? (1):(-1)) * EEPROM_Read_Float(Backup_Sector,1022);

              hCtrl.Roll.BalanceSign = flash_read(Backup_Sector, 1021, uint32);
              hCtrl.Roll.DynamicZero_T = (hCtrl.Roll.BalanceSign == 0 ? (1):(-1)) * EEPROM_Read_Float(Backup_Sector,1020);


              OLED_Show_Str(0, 0, "PitchBalan", TextSize_F6x8); OLED_Show_float(First_X-20, 0, hCtrl.Pitch.BalancePoint,4,TextSize_F6x8);

              OLED_Show_Str(0, 4, "RollBalan", TextSize_F6x8);  OLED_Show_float(First_X-20, 4, hCtrl.Roll.DynamicZero_T,4,TextSize_F6x8);


              hCtrl.Pitch.BalanceSign  = (float) KeyboardInput_with_Flash(Second_X,0,TextSize_F6x8, 1.0,SectorNum,1023);
              hCtrl.Pitch.BalancePoint = (float) KeyboardInput_with_Flash_Float(Second_X,2,TextSize_F6x8, 0.001,SectorNum,1022);

              hCtrl.Roll.BalanceSign   = (float) KeyboardInput_with_Flash(Second_X,4,TextSize_F6x8, 1.0,SectorNum,1021);
              hCtrl.Roll.DynamicZero_T = (float) KeyboardInput_with_Flash_Float(Second_X,6,TextSize_F6x8, 0.001,SectorNum,1020);


              OLED_CLS();
              EEPROM_Write_32Bit(Backup_Sector, 1, SectorNum);//记录结束输入数据标志
              break;
          }
          case 5: //offset   新核心板此扇区坏了
          {

              uint16 headpage = 1023;
              uint16 pid_choose = 0;
              uint8 EditFlag[8] = {0};                            //编辑标志，若某一个pid参数被更改，则将对应的标志位置 1 [第0位为总标志，每次检查其后的几位是否为1，若为1则跳出，否则继续循环]

              Flash_Data_Move(SectorNum, Backup_Sector);          //将数据备份到备份扇区
              EEPROM_Write_32Bit(Backup_Sector, 0, SectorNum);    //记录开始输入数据标志
              EEPROM_EraseSector(SectorNum);     //擦除

              do
              {
                  OLED_CLS();

                  //打印列表
                  for(uint8 i = 0; i < PID_Num; i++)
                  {
                      OLED_Show_OneNumber(0, i, PID_init_list[i]->index, TextSize_F6x8);  OLED_Show_Char(8, i, '.', TextSize_F6x8);
                      OLED_Show_Str(12, i, PID_init_list[i]->name, TextSize_F6x8);
                  }
                  //输入要更改的pid的标号
                  pid_choose = KeyboardInput(88, 6, TextSize_F8x16, 1.0);

                  if(EditFlag[pid_choose] == 1)   //检查是否已经更改过
                  {
                      continue;
                  }
                  if(pid_choose == 0)//手动退出
                  {
                      EditFlag[0] = 1;
                  }
                  else if(pid_choose <= PID_Num)
                  {
                      PID_Config(PID_init_list[pid_choose-1]);
  //                    //检查是否PID参数正常写入
  //                    if(PID_InputCheck(PID_init_list[pid_choose-1]))
  //                    {
                      EditFlag[pid_choose] = 1;
  //                    }
                  }

                  //若所有的标志位都置1或手动跳过则进入下一个界面
                  if(EditFlag[1] == 1 && EditFlag[2] == 1 && EditFlag[3] == 1 && EditFlag[4] == 1 && EditFlag[5] == 1 && EditFlag[6] == 1 && EditFlag[7] == 1)
                  {
                      EditFlag[0] = 1;
                  }

                  pid_choose = 0;
              }while(EditFlag[0] == 0);

              for(uint8 i = 0; i < PID_Num; i++)
              {
                  if(EditFlag[i+1] == 0)
                  {
                      headpage = PAGE_NUM - ((PID_init_list[i]->index - 1) * 10);
                      //读取之前存在flash里的数据
                      EEPROM_Write_32Bit(PID_Sector, headpage - 0, flash_read(Backup_Sector, headpage - 0, uint32));
                      EEPROM_Write_32Bit(PID_Sector, headpage - 1, flash_read(Backup_Sector, headpage - 1, uint32));
                      EEPROM_Write_32Bit(PID_Sector, headpage - 2, flash_read(Backup_Sector, headpage - 2, uint32));
                      EEPROM_Write_32Bit(PID_Sector, headpage - 3, flash_read(Backup_Sector, headpage - 3, uint32));
                      EEPROM_Write_32Bit(PID_Sector, headpage - 4, flash_read(Backup_Sector, headpage - 4, uint32));
                      EEPROM_Write_32Bit(PID_Sector, headpage - 5, flash_read(Backup_Sector, headpage - 5, uint32));
                  }
              }
              OLED_CLS();
              EEPROM_Write_32Bit(Backup_Sector, 1, SectorNum);//记录结束输入数据标志
              break;
          }
          case 6://除零票
          {

              Flash_Data_Move(SectorNum, Backup_Sector);          //将数据备份到备份扇区
              EEPROM_Write_32Bit(Backup_Sector, 0, SectorNum);    //记录开始输入数据标志
              EEPROM_EraseSector(SectorNum);     //擦除

              system_delay_ms(500);               // 等待0.5s静止

//              icm20602_offset();
              OLED_CLS(); //清屏
              if(IMUData.offsetErrCount == 0)
              {
                  OLED_Show_Str(10, 2, "offset perfect", TextSize_F6x8);
              }
              else
              {
                  OLED_Show_Str(10, 2, "offset Problem", TextSize_F6x8);
                  OLED_Show_Numbers(Second_X, 4, IMUData.offsetErrCount,TextSize_F6x8);
              }
              OLED_Show_float(10,5,IMUData.gxOffset,6,TextSize_F6x8);
              OLED_Show_float(10,6,IMUData.gyOffset,6,TextSize_F6x8);
              OLED_Show_float(10,7,IMUData.gzOffset,6,TextSize_F6x8);
              KeyboardInput(88, 6, TextSize_F8x16, 1.0);

              EEPROM_Write_Float(SectorNum,1023,IMUData.gxOffset);
              EEPROM_Write_Float(SectorNum,1022,IMUData.gyOffset);
              EEPROM_Write_Float(SectorNum,1021,IMUData.gzOffset);

              EEPROM_Write_32Bit(Backup_Sector, 1, SectorNum);//记录结束输入数据标志
              break;
          }
          case 7://手动转向
          {

          }
          case 8:
          {
            Flash_Data_Move(SectorNum, Backup_Sector);          //将数据备份到备份扇区
            EEPROM_Write_32Bit(Backup_Sector, 0, SectorNum);    //记录开始输入数据标志
            EEPROM_EraseSector(SectorNum);     //擦除

            for (int i = 0; i < 7; i++)
            {
                OLED_Show_Str(0, i, "T1", TextSize_F6x8);
                OLED_Show_Numbers(25, i, flash_read(Backup_Sector, 1023 - i, uint32),TextSize_F6x8);
            }

            for (int i = 0; i < 7; i++)
            {
                Point[i] = (int)KeyboardInput_with_Flash(Second_X,i,TextSize_F6x8, 1.0,SectorNum,1023 - i);
            }
//            Point[0] = (int)KeyboardInput_with_Flash(Second_X,0,TextSize_F6x8, 1.0,SectorNum,1023);
//            Point[1] = (int)KeyboardInput_with_Flash(Second_X,1,TextSize_F6x8, 1.0,SectorNum,1022);
//            Point[2] = (int)KeyboardInput_with_Flash(Second_X,2,TextSize_F6x8, 1.0,SectorNum,1021);
//            Point[3] = (int)KeyboardInput_with_Flash(Second_X,3,TextSize_F6x8, 1.0,SectorNum,1020);
//            Point[4] = (int)KeyboardInput_with_Flash(Second_X,4,TextSize_F6x8, 1.0,SectorNum,1019);
//            Point[5] = (int)KeyboardInput_with_Flash(Second_X,5,TextSize_F6x8, 1.0,SectorNum,1018);
//            Point[6] = (int)KeyboardInput_with_Flash(Second_X,6,TextSize_F6x8, 1.0,SectorNum,1017);

            OLED_CLS();

            for (int i = 7; i < 14; i++)
            {
                OLED_Show_Str(0, i - 7, "T2", TextSize_F6x8);
                OLED_Show_Numbers(25, i - 7, flash_read(Backup_Sector, 1023 - i, uint32),TextSize_F6x8);
            }

            for (int i = 7; i < 14; i++)
            {
                Point[i] = (int)KeyboardInput_with_Flash(Second_X,i - 7,TextSize_F6x8, 1.0,SectorNum,1023 - i);
            }

            OLED_CLS();

            for (int i = 14; i < 21; i++)
            {
                OLED_Show_Str(0, i - 14, "T3", TextSize_F6x8);
                OLED_Show_Numbers(25, i - 14, flash_read(Backup_Sector, 1023 - i, uint32),TextSize_F6x8);
            }

            for (int i = 14; i < 21; i++)
            {
                Point[i] = (int)KeyboardInput_with_Flash(Second_X,i - 14,TextSize_F6x8, 1.0,SectorNum,1023 - i);
            }

            OLED_CLS();

            EEPROM_Write_32Bit(Backup_Sector, 1, SectorNum);//记录结束输入数据标志
          }
          case 9://PotHand手打点
          {
//              OLED_Show_Str(40, 2, "Sure?" , TextSize_F6x8);
//              KeyboardInput(88, 6, TextSize_F6x8, 1.0);
//
//              Navigation.MarkPot.Mode = Hand_MarkMode;
//              EEPROM_EraseSector(MP_sector);

              break;
          }
          case 10://Speed
          {
              Flash_Data_Move(SectorNum, Backup_Sector);          //将数据备份到备份扇区
              EEPROM_Write_32Bit(Backup_Sector, 0, SectorNum);    //记录开始输入数据标志
              EEPROM_EraseSector(SectorNum);     //擦除

              OLED_Show_Str(0, 0, "omega", TextSize_F6x8);   OLED_Show_float(25, 0, EEPROM_Read_Float(Backup_Sector, 1023),3,TextSize_F6x8);
              OLED_Show_Str(0, 1, "Turn", TextSize_F6x8);    OLED_Show_Numbers(25, 1, flash_read(Backup_Sector, 1022, uint32),TextSize_F6x8);
              OLED_Show_Str(0, 2, "s2", TextSize_F6x8);    OLED_Show_float(25, 2, EEPROM_Read_Float(Backup_Sector, 1021),3,TextSize_F6x8);
              OLED_Show_Str(0, 3, "S0", TextSize_F6x8);    OLED_Show_float(25, 3, EEPROM_Read_Float(Backup_Sector, 1020),3,TextSize_F6x8);
              OLED_Show_Str(0, 4, "S1", TextSize_F6x8);    OLED_Show_float(25, 4, EEPROM_Read_Float(Backup_Sector, 1019),3,TextSize_F6x8);
              OLED_Show_Str(0, 5, "Dk", TextSize_F6x8);    OLED_Show_float(25, 5, EEPROM_Read_Float(Backup_Sector, 1018),3,TextSize_F6x8);
              OLED_Show_Str(0, 6, "SS", TextSize_F6x8);    OLED_Show_float(25, 6, EEPROM_Read_Float(Backup_Sector, 1017),3,TextSize_F6x8);

              hCtrl.Turn.Omega = (float)KeyboardInput_with_Flash_Float(Second_X,0,TextSize_F6x8, 0.1,SectorNum,1023);
              hCtrl.Turn.Row = (int)KeyboardInput_with_Flash(Second_X,1,TextSize_F6x8, 1.0,SectorNum,1022);
              hCtrl.Pitch.ExpectSpeed_Input_Fast = (float)KeyboardInput_with_Flash_Float(Second_X,2,TextSize_F6x8, 1,SectorNum,1021);
              hCtrl.Pitch.ExpectSpeed_Input_Find = (float)KeyboardInput_with_Flash_Float(Second_X,3,TextSize_F6x8, 1,SectorNum,1020);
              hCtrl.Pitch.ExpectSpeed_Input_Turn = (float)KeyboardInput_with_Flash_Float(Second_X,4,TextSize_F6x8, 1,SectorNum,1019);
              hCtrl.Roll.Dynamic_k  = (float)KeyboardInput_with_Flash_Float(Second_X,5,TextSize_F6x8, 0.001,SectorNum,1018);
              hCtrl.Pitch.ExpectSpeed_Input_Start = (float)KeyboardInput_with_Flash_Float(Second_X,6,TextSize_F6x8,1,SectorNum,1017);

              OLED_CLS();
              EEPROM_Write_32Bit(Backup_Sector, 1, SectorNum);//记录结束输入数据标志
          }
          case 11:
          {
              break;
          }

          default :
          {
              break;
          }
      }
      OLED_CLS(); //清屏
      OLED_Show_Str(40, 2, "Ready?" , TextSize_F6x8);
      KeyboardInput(88, 6, TextSize_F6x8, 1.0);
      OLED_CLS(); //清屏
      hCtrl.GlobalFlag.CarStart = 1;
      Load_ALL();
}
/*************************************
** Function: Oled_Display
** Description: oled参数显示
** Others:无
*************************************/
void Oled_Display(void)
{

    switch(hCtrl.Debug.Oled_Show)
    {
        case 1:
        {
            OLED_Show_float(0,0,hCtrl.Speed.Foot_Ctrl[0],4,TextSize_F6x8);
            OLED_Show_float(0,1,hCtrl.Speed.Forward[0],4,TextSize_F6x8);
            OLED_Show_float(0,2,hCtrl.Speed.Backward[0],4,TextSize_F6x8);
            break;
        }
        case 2://二值化图像部分显示
        {
            Image_Display();
            break;
        }
        case 3://状态显示，有无找见灯
        {
            break;
        }
        case 4:
        {
            OLED_Show_float(0,0,IMUData.ax,4,TextSize_F6x8);
            OLED_Show_float(0,1,IMUData.ay,4,TextSize_F6x8);
            OLED_Show_float(0,2,IMUData.az,4,TextSize_F6x8);
            OLED_Show_float(0,3,IMUData.gx,2,TextSize_F6x8); OLED_Show_float(60,3,IMUData.gxOffset,4,TextSize_F6x8);
            OLED_Show_float(0,4,IMUData.gy,2,TextSize_F6x8); OLED_Show_float(60,4,IMUData.gyOffset,4,TextSize_F6x8);
            OLED_Show_float(0,5,IMUData.gz,2,TextSize_F6x8); OLED_Show_float(60,5,IMUData.gzOffset,4,TextSize_F6x8);
            break;
        }
        case 5:
        {
            break;
        }
        default :
        {

            break;
        }
    }
}

void OLED_Runing_show(void)
{
    uint8_t key = CH455_QueryOneKey(60);
}

void OLED_RuningDBG(void)
{

}

/***************************************************
** Function: Load_Config_Flash
** Description: 读取速度
** Others:无
****************************************************/
static void Load_Config_Flash(void)
{

}
/***************************************
 ** Function: Load_Switch_Flash
 ** Description: 读取Flash
 ** Others:无
 ***************************************/
static void Load_Switch_Flash(void)
{

}
/***************************************
 ** Function: Get_Show_Flash
 ** Description: 读取Flash
 ** Others:无
 ***************************************/

static void Load_Balan_Flash(void)
{
    hCtrl.Pitch.BalanceSign  = flash_read(4, 1023, uint32);
    hCtrl.Pitch.BalancePoint = (hCtrl.Pitch.BalanceSign == 0 ? (1):(-1)) * EEPROM_Read_Float(4,1022);

    hCtrl.Roll.BalanceSign   = flash_read(4, 1021, uint32);
    hCtrl.Roll.DynamicZero_T = (hCtrl.Roll.BalanceSign == 0 ? (1):(-1)) * EEPROM_Read_Float(4,1020);
}
/***************************************
** Function: Load_PID_Flash
** Description: 装载PID参数
** Others:无
***************************************/
static void Load_PID_Flash(void)
{
    uint16 headpage = 0;

    for(uint8 i = 0; i < PID_Num; i++)
    {
        headpage = PAGE_NUM - ((PID_init_list[i]->index - 1) * 10);

        PID_init_list[i]->kp              = flash_read(PID_Sector, headpage - 0, float);
        PID_init_list[i]->ki              = flash_read(PID_Sector, headpage - 1, float);
        PID_init_list[i]->kd              = flash_read(PID_Sector, headpage - 2, float);
        PID_init_list[i]->iOutMax         = flash_read(PID_Sector, headpage - 3, float);
        PID_init_list[i]->outMax          = flash_read(PID_Sector, headpage - 4, float);
        PID_init_list[i]->ZeroOutFlag     = flash_read(PID_Sector, headpage - 5, float);
    }
}

static void Load_Turn_Set(void)
{
    uint16 headpage = 1023;

    for(int i = 0; i < 10; i++)
    {
        Point[i] = flash_read(Led_Sector, headpage - i, uint32);
    }
}
void OdoMeter_load(void)
{
//    Navigation.Map.Point_Num = flash_read(MP_sector, MP_Start_Page, int32);
//
//    //存入(0,0)作为起始点，辅助计算
//    Navigation.Map.MP_Data[0].X       = 0;
//    Navigation.Map.MP_Data[0].Y       = 0;
//    Navigation.Map.MP_Data[0].type    = 0;
//
//    for(uint8 i = 1; i <= Navigation.Map.Point_Num; i++)
//    {
//        Navigation.Map.MP_Data[i].X       = (float)EEPROM_Read_Float(MP_sector, MP_Start_Page-(i-1)*3-1);
//        Navigation.Map.MP_Data[i].Y       = (float)EEPROM_Read_Float(MP_sector, MP_Start_Page-(i-1)*3-2);
//        Navigation.Map.MP_Data[i].type    = (uint8)EEPROM_Read_32Bit(MP_sector, MP_Start_Page-(i-1)*3-3);
//    }
//    Navigation.Map.MP_Data[Navigation.Map.Point_Num+1].X =   0.2;
//    Navigation.Map.MP_Data[Navigation.Map.Point_Num+1].Y = - 0.2;
//    Navigation.Map.MP_Data[Navigation.Map.Point_Num+1].type= 0;
//
////  Navigation.Map.MP_Data[Navigation.Map.Point_Num+1].X = 1;
////  Navigation.Map.MP_Data[Navigation.Map.Point_Num+1].Y = -0.4;
////  Navigation.Map.MP_Data[Navigation.Map.Point_Num+1].type= 0;
////
////  Navigation.Map.MP_Data[Navigation.Map.Point_Num+2].X =  1;
////  Navigation.Map.MP_Data[Navigation.Map.Point_Num+2].Y =- 0.4;
////  Navigation.Map.MP_Data[Navigation.Map.Point_Num+2].type= 0;
}

static void Load_Show_Flash(void)
{
    hCtrl.Debug.Oled_Show  = (uint8)flash_read(3, 1023, uint32);
    hCtrl.Debug.Param_send = (uint8)flash_read(3, 1022, uint32);
}
static void Load_Speed_Flash(void)
{
    hCtrl.Turn.Omega = EEPROM_Read_Float(Speed_Sector,1023);
    hCtrl.Turn.Row   = (int)flash_read(Speed_Sector, 1022, int);

    hCtrl.Pitch.ExpectSpeed_Input_Fast = EEPROM_Read_Float(Speed_Sector,1021);
    hCtrl.Pitch.ExpectSpeed_Input_Find = EEPROM_Read_Float(Speed_Sector,1020);//   + (120 - Center_ROW) / 2;
    hCtrl.Pitch.ExpectSpeed_Input_Turn = EEPROM_Read_Float(Speed_Sector,1019);

    hCtrl.Roll.Dynamic_k = EEPROM_Read_Float(Speed_Sector,1018);
    hCtrl.Pitch.ExpectSpeed_Input_Start = EEPROM_Read_Float(Speed_Sector,1017);

//    Navigation.SpdExp_Normal = (float)flash_read(Speed_Sector, 1016, uint32);
}
static void Load_Offset_Flash(void)
{
    IMUData.gxOffset =  EEPROM_Read_Float(6,1023);
    IMUData.gyOffset =  EEPROM_Read_Float(6,1022);
    IMUData.gzOffset =  EEPROM_Read_Float(6,1021);
}
static void Load_Camera_Flash(void)
{
    hCtrl.Start_Run.Delay_Limit = flash_read(2, 1021, uint32);
}
/***************************************
** Function: Get_ALL
** Description: 读取Flash
** Others:无
***************************************/
static void Load_ALL(void)
{
    Load_PID_Flash();
    Load_Show_Flash();
    Load_Balan_Flash();
    Load_Speed_Flash();
    Load_Offset_Flash();
    Load_Camera_Flash();
    Load_Turn_Set();
}

