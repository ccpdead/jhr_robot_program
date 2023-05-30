/**
 * @file jhr_pwr.h
 * @author lly
 * @brief 
 * @version 0.1
 * @date 2023-03-23
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef __JHR_COULOMETER_H__
#define __JHR_COULOMETER_H__
#include "jhr_uart.h"

#pragma pack(1)
//数据报头
typedef struct{
    uint16_t head; //0xA55A,低字节在前
    int8_t type;  //功能码
}Pwr_head;
//3字节长度数据
typedef struct{
    uint8_t dat1;
    uint8_t dat2;
    uint8_t dat3;
}Pwr_dat_3;
//基础数据类型
typedef struct{
    uint8_t percent;  //电量百分比
    int16_t voltage;  //电压 0.01v
    int16_t current;  //电流 0.01A
    int16_t capacity; //额定容量 0.1AH
    int16_t temperature;  //温度 0.1度
    int8_t direction; //0：放电,1:充电
}Pwd_basic_data;
//设定数据类型
typedef struct{
    int8_t alarm;  //电量报警值
    int16_t underVoltage;  //电池欠压值 0.01V
    int16_t fullVoltage;  //电池满电电压 0.01V
    int32_t usedTimes; //电池已使用次数 0.01
    int16_t currentRange;  //电流量程
    int8_t backlight; //背光模式
    int8_t software_version; //软件版本
    int8_t reserved;  //预留
}Pwd_setting_data;
//设定数据类型
typedef struct{
    int alarm;  //电量报警值
    int underVoltage;  //电池欠压值 0.01V
    int fullVoltage;  //电池满电电压 0.01V
    int currentRange;  //电流量程
    int capacity; //额定容量 0.1AH
}Pwd_setting_wr;

typedef struct{
    Pwr_head head;
    Pwd_basic_data data;
    uint8_t id;
    int8_t sum;
}Pwr_rcv_basic;
typedef struct{
    Pwr_head head;
    Pwd_setting_data data;
    uint8_t id;
    int8_t sum;
}Pwr_rcv_setting;
typedef struct{
    Pwr_head head;
    Pwr_dat_3 data;//三字节长度
    uint8_t id;
    int8_t sum;
}Pwr_send_ask;
#pragma pack()

class Jhr_pwr
{
public:
    static void loop();
    static void init();
private:
    static Jhr_uart *jhr_uart;
    static int uart_rcv_check(const uint8_t*buf,int len);
    static int16_t big_endian_conversion(int16_t data);
    static int32_t big_endian_conversion(int32_t data);
    static int uart_write_pack(int8_t type,Pwr_dat_3 dat);
    static int rdSettingData(); //串口读取设定数据
    static int rdBascData() ;   //串口读取基础数据
    static int wrCurrentRange();  //单位A，   7.5A->3000,75A -> 300
    static int wrFullVoltage();  //电池满电电压 0.01V
    static int wrUnderVoltage();  //电池欠压值 0.01V
    static int wrCapacity();    //设置额定容量，0.1AH
    static int wrAlam();    //设置报警
    static int work_state;
    static void public_msg();
    static Pwd_basic_data pwd_basic_data;   //从模块读出的电量数据
    static Pwd_setting_data pwd_setting_data_r;   //从模块读出的设定值
    static Pwd_setting_wr pwd_setting_data_w;   //系统设定的设定值
};
#endif
