/*
 * */
/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		eeprom(Dflash)
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		tasking v6.3r1
 * @Target core		TC264D
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-3-23
 ********************************************************************************************************************/
 

#include "IfxScuWdt.h"
#include "IfxFlash.h"
#include "zf_assert.h"
#include "zf_eeprom.h"

typedef union//浮点型转长整型共用体
{
  float fdata;
  uint32 ldata;
}FloatLongType;

static void Float_to_Uint32(float F,uint32 * Uint32)//浮点型转4字节
{
    FloatLongType fl;
    fl.fdata = F;
    *Uint32  = fl.ldata;
}
static void Uint32_to_Float(uint32 Uint32,float * f)//浮点型转4字节
{
    FloatLongType fl;
    fl.ldata = Uint32;
    *f = fl.fdata;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      校验FLASH是否有数据
//  @param      sector_num 		需要写入的扇区编号   参数范围0-11
//  @param      page_num	 	当前扇区页的编号     参数范围0-1023
//  @return     				返回1有数据，返回0没有数据，如果需要对有数据的区域写入新的数据则应该对所在扇区进行擦除操作
//  @since      v1.0
//  Sample usage:               flash_check(0,0);//校验0号扇区，第0页是否有数据
//-------------------------------------------------------------------------------------------------------------------
uint8 flash_check(uint32 sector_num, uint32 page_num)
{
	ZF_ASSERT(EEPROM_SECTOR_NUM>sector_num);
	ZF_ASSERT(EEPROM_SECTOR_PAGE_NUM>page_num);
	uint32 sector_addr = IfxFlash_dFlashTableEepLog[sector_num].start;
	uint32 page_addr = sector_addr + page_num * IFXFLASH_DFLASH_PAGE_LENGTH;

	uint32 temp = *(uint32 *)page_addr;
	if(0 != temp)	return 1;

	return 0;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      擦除扇区
//  @param      sector_num 		需要写入的扇区编号   参数范围0-11
//  @return     void
//  @since      v1.0
//  Sample usage:               eeprom_erase_sector(0);
//-------------------------------------------------------------------------------------------------------------------
void eeprom_erase_sector(uint32 sector_num)
{
	ZF_ASSERT(EEPROM_SECTOR_NUM>sector_num);

	uint32 flash = 0;
	uint16 end_init_sfty_pw;
	uint32 sector_addr = IfxFlash_dFlashTableEepLog[sector_num].start;

	end_init_sfty_pw = IfxScuWdt_getSafetyWatchdogPassword();

	IfxScuWdt_clearSafetyEndinit(end_init_sfty_pw);
    IfxFlash_eraseSector(sector_addr);
    IfxScuWdt_setSafetyEndinit(end_init_sfty_pw);

    IfxFlash_waitUnbusy(flash, IfxFlash_FlashType_D0);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      编程一页
//  @param      sector_num 		需要写入的扇区编号   参数范围0-11
//  @param      page_num 		需要写入的页编号     参数范围0-1023
//  @param      buf 		   	需要写入的数据地址   传入的数组类型必须为uint32
//  @return     void
//  @since      v1.0
//  Sample usage:				eeprom_page_program(0,0, &buf);
//-------------------------------------------------------------------------------------------------------------------
void eeprom_page_program(uint32 sector_num, uint32 page_num, uint32 *buf)
{
	ZF_ASSERT(EEPROM_SECTOR_NUM>sector_num);
	ZF_ASSERT(EEPROM_SECTOR_PAGE_NUM>page_num);

	uint32 errors = 0;
	uint32 flash = 0;
	uint16 end_init_sfty_pw;
	uint32 sector_addr = IfxFlash_dFlashTableEepLog[sector_num].start;

	end_init_sfty_pw = IfxScuWdt_getSafetyWatchdogPassword();

	uint32 page_addr = sector_addr + page_num * IFXFLASH_DFLASH_PAGE_LENGTH;
	errors = IfxFlash_enterPageMode(page_addr);
	ZF_ASSERT(0 == errors);

	IfxFlash_waitUnbusy(flash, IfxFlash_FlashType_D0);

	IfxFlash_loadPage(page_addr, buf[0], 0);

	IfxScuWdt_clearSafetyEndinit(end_init_sfty_pw);
	IfxFlash_writePage(page_addr);
	IfxScuWdt_setSafetyEndinit(end_init_sfty_pw);

	IfxFlash_waitUnbusy(flash, IfxFlash_FlashType_D0);
}

/*************************************************************************
*  函数名称：uint32  EEPROM_Read_32Bit(unsigned char sector, unsigned short page)
*  功能说明：eeprom读取某页低 32位数据
*  参数说明：
  * @param    sector   ：  扇区   范围  0-11
  * @param    page     ：  页     范围  0-1023
*  函数返回：uint32
*  修改时间：2020年6月4日
*************************************************************************/
uint32  EEPROM_Read_32Bit(unsigned char sector, unsigned short page)
{
    unsigned long buff[2];
//  EEPROM_Read(sector, page, buff, 1);
//  return buff[0];
    /* 计算扇区起始地址 */
    unsigned long sector_addr = IfxFlash_dFlashTableEepLog[sector].start;

    /* 要读页地址 */
    volatile unsigned long * pageAddr = (unsigned long*)(sector_addr + page * IFXFLASH_DFLASH_PAGE_LENGTH);

    buff[0] = *(pageAddr);

    return buff[0];
}

/*************************************************************************
*  函数名称：uint32  EEPROM_Read_32Bit(unsigned char sector, unsigned short page)
*  功能说明：eeprom以float格式读取某页低 32位数据
*  参数说明：
  * @param    sector   ：  扇区   范围  0-11
  * @param    page     ：  页     范围  0-1023
*  函数返回：uint32
*  修改时间：2024年4月24日
*************************************************************************/
float EEPROM_Read_Float(unsigned char sector, unsigned short page)
{
    float Value = 0;
    Uint32_to_Float(EEPROM_Read_32Bit(sector,page),&Value);
    return Value;
}

/*************************************************************************
*  函数名称：void  EEPROM_Write_32Bit(unsigned char sector, unsigned short page, unsigned long value)
*  功能说明：eeprom写入某页低 32位数据
*  参数说明：
  * @param    sector   ：  扇区   范围  0-11
  * @param    page     ：  页     范围  0-1023
  * @param    value     ：  存放写入数据
*  函数返回：无
*  修改时间：2020年6月4日
*************************************************************************/
void  EEPROM_Write_32Bit(unsigned char sector, unsigned short page, unsigned long value)
{
    unsigned long buff[2] = {value, 0};
    /* 计算扇区起始地址 */
    unsigned long sector_addr = IfxFlash_dFlashTableEepLog[sector].start;

    unsigned short endinitSfty_pw;

    endinitSfty_pw = IfxScuWdt_getSafetyWatchdogPassword();

    /* 要写入页地址 */
    unsigned long pageAddr = sector_addr + (page)* IFXFLASH_DFLASH_PAGE_LENGTH;

    IfxFlash_enterPageMode(pageAddr);

    /* 察忙 */
    IfxFlash_waitUnbusy(0, IfxFlash_FlashType_D0);

    /* 写入缓冲区  */
    IfxFlash_loadPage2X32(pageAddr, buff[0], buff[1]);

    /* 写入eeprom  */
    IfxScuWdt_clearSafetyEndinit(endinitSfty_pw);
    IfxFlash_writePage(pageAddr);
    IfxScuWdt_setSafetyEndinit(endinitSfty_pw);

    IfxFlash_waitUnbusy(0, IfxFlash_FlashType_D0);
}





/*************************************************************************
*  函数名称：void  EEPROM_Write_Float(unsigned char sector, unsigned short page, float value)
*  功能说明：eeprom以float格式写入某页低 32位数据
*  参数说明：
  * @param    sector   ：  扇区   范围  0-11
  * @param    page     ：  页     范围  0-1023
  * @param    value     ：  存放写入数据
*  函数返回：无
*  修改时间：2024年4月24日
*************************************************************************/
void  EEPROM_Write_Float(unsigned char sector, unsigned short page, float value)
{
    uint32 Temp_Uint32 = 0;
    Float_to_Uint32(value,&Temp_Uint32);
    EEPROM_Write_32Bit(sector,page,Temp_Uint32);
}

/*************************************************************************
*  函数名称：void Flash_Data_Move(unsigned char sector, unsigned char BackupSector)
*  功能说明：将源扇区里的所有数据转移到目的扇区
  * @param    srcSector   ：  扇区   范围  0-11
  * @param    desSector   ：  扇区   范围  0-11, 默认11
*  函数返回：无
*  修改时间：2020年6月6日
*************************************************************************/
void Flash_Data_Move(unsigned char srcSector, unsigned char desSector)
{
    unsigned long buff[2*MAX_PAGE_NUM] = {0};
    EEPROM_Read(srcSector, 1024-MAX_PAGE_NUM, buff, 2*MAX_PAGE_NUM);
    EEPROM_EraseSector(desSector);
    EEPROM_Write(desSector, 1024-MAX_PAGE_NUM, buff, 2*MAX_PAGE_NUM);
}

/*************************************************************************
*  函数名称：void EEPROM_EraseSector(unsigned char sector)
*  功能说明：eeprom擦出扇区
*  参数说明：sector   ：  扇区范围  0-11
*  函数返回：无
*  修改时间：2020年3月10日
*  备    注：EEPROM_EraseSector(0);   //擦出扇区0
*************************************************************************/
void EEPROM_EraseSector(unsigned char sector)
{
    /* 计算扇区起始地址 */
    unsigned long sector_addr = IfxFlash_dFlashTableEepLog[sector].start;

    unsigned short endinitSfty_pw;

    endinitSfty_pw = IfxScuWdt_getSafetyWatchdogPassword();

    /* 擦出扇区 */
    IfxScuWdt_clearSafetyEndinit(endinitSfty_pw);
    IfxFlash_eraseSector(sector_addr);
    IfxScuWdt_setSafetyEndinit(endinitSfty_pw);

    IfxFlash_waitUnbusy(0, IfxFlash_FlashType_D0);
}

/*************************************************************************
*  函数名称：void EEPROM_EraseSector(unsigned char sector)
*  功能说明：eeprom写入数据
*  参数说明：
  * @param    sector   ：  扇区   范围  0-11
  * @param    page     ：  页     范围  0-1023
  * @param    buff     ：  存放写入数据
  * @param    len      ：  写入数据个数
*  函数返回：无
*  修改时间：2020年3月10日
*  备    注：EEPROM_Write(0, 0, u32wBuff, 24);   //向扇区0  第0页  写入24个unsigned long数据
*************************************************************************/
void EEPROM_Write(unsigned char sector, unsigned short page, unsigned long * buff, unsigned short len)
{
    int i;
    /* 计算扇区起始地址 */
    unsigned long sector_addr = IfxFlash_dFlashTableEepLog[sector].start;

    unsigned short endinitSfty_pw;

    endinitSfty_pw = IfxScuWdt_getSafetyWatchdogPassword();

    for(i = 0; i < len/2; i++)
    {
        /* 要写入页地址 */
        unsigned long pageAddr = sector_addr + (page + i)* IFXFLASH_DFLASH_PAGE_LENGTH;

        IfxFlash_enterPageMode(pageAddr);

        /* 察忙 */
        IfxFlash_waitUnbusy(0, IfxFlash_FlashType_D0);

        /* 写入缓冲区  */
        IfxFlash_loadPage2X32(pageAddr, buff[2*i], buff[2*i + 1]);

        /* 写入eeprom  */
        IfxScuWdt_clearSafetyEndinit(endinitSfty_pw);
        IfxFlash_writePage(pageAddr);
        IfxScuWdt_setSafetyEndinit(endinitSfty_pw);

        IfxFlash_waitUnbusy(0, IfxFlash_FlashType_D0);
    }

    if(len%2)
    {
        /* 要写入页地址 */
        unsigned long pageAddr = sector_addr + (page + len/2)* IFXFLASH_DFLASH_PAGE_LENGTH;

        IfxFlash_enterPageMode(pageAddr);

        /* 察忙 */
        IfxFlash_waitUnbusy(0, IfxFlash_FlashType_D0);

        /* 写入缓冲区  */
        IfxFlash_loadPage2X32(pageAddr, buff[len], 0);

        /* 写入eeprom  */
        IfxScuWdt_clearSafetyEndinit(endinitSfty_pw);
        IfxFlash_writePage(pageAddr);
        IfxScuWdt_setSafetyEndinit(endinitSfty_pw);

        IfxFlash_waitUnbusy(0, IfxFlash_FlashType_D0);

    }
}


/*************************************************************************
*  函数名称：void EEPROM_Read(unsigned char sector, unsigned short page, unsigned long * rbuff, unsigned short len)
*  功能说明：eeprom读取
*  参数说明：
  * @param    sector   ：  扇区   范围  0-11
  * @param    page     ：  页     范围  0-1023
  * @param    buff     ：  存放写入数据
  * @param    len      ：  写入数据个数
*  函数返回：无
*  修改时间：2020年3月10日
*  备    注：EEPROM_Read(0, 0, u32rBuff, 24);   //读取扇区0  第0页  开始的24个unsigned long数据
*************************************************************************/
void EEPROM_Read(unsigned char sector, unsigned short page, unsigned long * rbuff, unsigned short len)
{
    int i;
    /* 计算扇区起始地址 */
    unsigned long sector_addr = IfxFlash_dFlashTableEepLog[sector].start;

    /* 要读页地址 */
    volatile unsigned long * pageAddr = (unsigned long*)(sector_addr + page * IFXFLASH_DFLASH_PAGE_LENGTH);

    for(i = 0; i < len; i++)
    {

        rbuff[i] = *(pageAddr+i);
    }
}

