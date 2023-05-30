/**
 * @file jhr_pwr.cpp
 * @author lly
 * @brief 库仑计数据处理程序
 * @version 0.1
 * @date 2023-03-23
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <iostream>
#include "jhr_pwr.h"


Jhr_uart *Jhr_pwr::jhr_uart = NULL;
Pwd_basic_data Jhr_pwr::pwd_basic_data; //从模块读出的电量数据
Pwd_setting_data Jhr_pwr::pwd_setting_data_r;   //从模块读出的设定值
Pwd_setting_wr Jhr_pwr::pwd_setting_data_w;   //系统设定的设定值
/**
 * @brief 工作状态
 * 1：读取配置参数
 * 
 */
int Jhr_pwr::work_state;
void Jhr_pwr::init()
{
    pwd_setting_data_w.alarm = 10;  //电量报警值
    pwd_setting_data_w.underVoltage = 1960;  //电池欠压值 0.01V
    pwd_setting_data_w.fullVoltage = 2520;  //电池满电电压 0.01V
    pwd_setting_data_w.currentRange = 7500;  //电流量程
    pwd_setting_data_w.capacity = 400; //额定容量 0.1AH
}
void public_jhr_pwr(const char* data);
void Jhr_pwr::public_msg()
{
    char buff[256];
    sprintf(buff,"{\"percent\":%d,\"voltage\":%d,\"current\":%d,\"direction\":%d}",
        (int)pwd_basic_data.percent,
        (int)pwd_basic_data.voltage,
        (int)pwd_basic_data.current,
        (int)pwd_basic_data.direction );
    public_jhr_pwr(buff);
}
void Jhr_pwr::loop()
{
    static uint8_t buff[256];
    static int curr_len = 0;
    static time_t tim_start = 0;

    if(jhr_uart == NULL){
        jhr_uart = new Jhr_uart("/dev/ttyCoulometer",9600);//实例化串口对象
        work_state = 1;
    }
    if(!jhr_uart->uart_isOpen()){
        curr_len = 0;
        tim_start = 0;
        jhr_uart->uart_open();
        return;
    }
    if(tim_start == 0)tim_start = time(NULL);
    time_t tim_now = time(NULL);
    if(curr_len >= sizeof(buff)) curr_len = 0;
    int len = jhr_uart->uart_read(buff + curr_len, sizeof(buff) - curr_len);//串口读函数
    bool is_success = false;
    if(len > 0){
        curr_len += len;
        if(curr_len < sizeof(Pwr_head))return;
        Pwr_head * pwr_head= (Pwr_head *)buff;
        if(pwr_head->head != 0xa55a){//检测数据头
            curr_len = 0;
            return;
        }
        switch(pwr_head->type)
        {
            case 0x10:  //基础数据
            if(curr_len >= 15 && uart_rcv_check(buff,curr_len)==0){
                Pwr_rcv_basic *r_s = (Pwr_rcv_basic *)buff;
                pwd_basic_data.percent = r_s->data.percent;
                pwd_basic_data.voltage = big_endian_conversion(r_s->data.voltage);
                pwd_basic_data.current = big_endian_conversion(r_s->data.current);
                pwd_basic_data.capacity = big_endian_conversion(r_s->data.capacity);
                pwd_basic_data.temperature = big_endian_conversion(r_s->data.temperature);
                pwd_basic_data.direction = r_s->data.direction;
                public_msg();
                std::cout<<" 电量百分比:"<< (int)pwd_basic_data.percent
                <<" 电压:"<< (int)pwd_basic_data.voltage
                <<" 电流:"<< (int)pwd_basic_data.current
                <<" 额定容量:"<< (int)pwd_basic_data.capacity
                <<" 温度:"<<(int)pwd_basic_data.temperature
                <<" 充放电:" << (int)pwd_basic_data.direction << std::endl;
                is_success = true;
                switch(work_state)
                {
                    case 1:rdSettingData();//读取设定数据
                        break;
                    case 2:if((char)pwd_setting_data_w.alarm != pwd_setting_data_r.alarm){
                            wrAlam();  work_state = 1;
                        }else if((short)pwd_setting_data_w.capacity != pwd_basic_data.capacity){
                            wrCapacity(); work_state = 1;
                        }else if((short)pwd_setting_data_w.currentRange != pwd_setting_data_r.currentRange){
                            wrCurrentRange(); work_state = 1;
                        }else if((short)pwd_setting_data_w.fullVoltage != pwd_setting_data_r.fullVoltage){
                            wrFullVoltage(); work_state = 1;
                        }else if((short)pwd_setting_data_w.underVoltage != pwd_setting_data_r.underVoltage){
                            wrUnderVoltage(); work_state = 1;
                        }else{
                            work_state = 3;
                        }
                        break;
                    default: ;
                }
            }
            break;
            case 0x09:  //读取设置信息
            if(curr_len >= 19 && uart_rcv_check(buff,curr_len)==0){
                Pwr_rcv_setting *r_s = (Pwr_rcv_setting *)buff;
                pwd_setting_data_r.underVoltage = big_endian_conversion(r_s->data.underVoltage);
                pwd_setting_data_r.fullVoltage = big_endian_conversion(r_s->data.fullVoltage);
                pwd_setting_data_r.usedTimes = big_endian_conversion(r_s->data.usedTimes);
                pwd_setting_data_r.currentRange = big_endian_conversion(r_s->data.currentRange);
                pwd_setting_data_r.currentRange = 2250000 / pwd_setting_data_r.currentRange;
                pwd_setting_data_r.backlight = r_s->data.backlight;
                pwd_setting_data_r.software_version = r_s->data.software_version;
                pwd_setting_data_r.alarm = r_s->data.alarm;
                std::cout<<" 电量报警值:"<< (int)pwd_setting_data_r.alarm
                    <<" 电池欠压值:"<< (int)pwd_setting_data_r.underVoltage
                    <<" 电池满电电压:"<< (int)pwd_setting_data_r.fullVoltage
                    <<" 电池已使用次数:"<< (int)pwd_setting_data_r.usedTimes
                    <<" 电流量程:"<<(int)pwd_setting_data_r.currentRange
                    <<" 背光模式:" << (int)pwd_setting_data_r.backlight
                    <<" 软件版本:"<<(int)pwd_setting_data_r.software_version<< std::endl;
                is_success = true;
                work_state = 2;
            }
            break;
            case 0x1a:  //设置电流值
            {
                is_success = true;
                std::cout<< "设置电流值" <<std::endl;
            }break;
            case 0x15:  //设置额定容量
            {
                is_success = true;
                std::cout<< "设置额定容量" <<std::endl;
            }break;
            case 0x16: //设置电量报警值
            {
                is_success = true;
                std::cout<< "设置电量报警值" <<std::endl;
            }break;
            case 0x17:   //设置欠电压值
            {
                is_success = true;
                std::cout<< "设置欠电压值" <<std::endl;
            }break;
            case 0x18:  //电池满电电压
            {
                is_success = true;
                std::cout<< "电池满电电压" <<std::endl;
            }break;
        }
    }
    if(is_success){
        curr_len = 0;
        tim_start = tim_now;
    }
    if(tim_now - tim_start > 5 || tim_now < tim_start){
        curr_len = 0;
        tim_start = 0; 
        jhr_uart->uart_close();
    }
}
//串口写函数
int Jhr_pwr::uart_write_pack(int8_t type,Pwr_dat_3 dat)
{
    uint8_t buf_data[10];
    Pwr_send_ask *send_buf =(Pwr_send_ask *)buf_data;
    send_buf->head.head = 0xA55A;
    send_buf->head.type = type;
    send_buf->data = dat;
    send_buf->id = 0;
    uint8_t sum = 0;
    int iLen = sizeof(send_buf->head) + sizeof(send_buf->data) + sizeof(send_buf->id);
    for(int i=0; i < iLen; i++ )
    {
        sum += buf_data[i];
    }
    send_buf->sum = sum;

    jhr_uart->uart_write(buf_data,sizeof(Pwr_send_ask));
    return sizeof(Pwr_send_ask);
}
/**
 * @brief 检验校验码是否正确
 * 
 * @param buf 
 * @param len 
 * @return int 
 */
int Jhr_pwr::uart_rcv_check(const uint8_t*buf,int len)
{
    uint8_t sum = 0;
    for(int i=0;i < len -1;i++){
        sum += (uint8_t)buf[i];
    }
    if(sum ==(uint8_t)buf[len -1])return 0; else return -1;
}

//大端转换
short Jhr_pwr::big_endian_conversion(short data)
{
    short ret;
    char *bufDst = (char*)&ret;
    char *bufSrc = (char*)&data;
    for(int i=0; i<2; i++){
        bufDst[i] = bufSrc[1-i];
    }
    return ret;
}
int Jhr_pwr::big_endian_conversion(int data){
    int ret;
    char *bufDst = (char*)&ret;
    char *bufSrc = (char*)&data;
    for(int i=0; i<4; i++){
        bufDst[i] = bufSrc[3-i];
    }
    return ret;
}

/**
 * @brief 设置报警
 * 
 * @return int 
 */
int Jhr_pwr::wrAlam()    //设置报警
{
    Pwr_dat_3 data;
    data.dat1 =(uint8_t)pwd_setting_data_w.alarm; 
    data.dat2 = 0; 
    data.dat3 = 0;
    uart_write_pack(0x16,data);
    return 0;
}

/**
 * @brief 设置额定容量 ，0.1AH
 * 
 * @return int 
 */
int Jhr_pwr::wrCapacity()    //设置额定容量，0.1AH
{
    Pwr_dat_3 data;
    short s1 = pwd_setting_data_w.capacity;
    data.dat1 = s1 >> 8; 
    data.dat2 = s1 & 0xff;
    data.dat3 = 0;
    uart_write_pack(0x15,data);
    //uart_rcv_print();
    return 0;
}

/**
 * @brief 电池欠压值 0.01V
 * 
 * @return int 
 */
int Jhr_pwr::wrUnderVoltage()  
{
    Pwr_dat_3 data;
    short s1 = pwd_setting_data_w.underVoltage;
    data.dat1 = s1 >> 8; 
    data.dat2 = s1 & 0xff;
    data.dat3 = 0;
    uart_write_pack(0x17,data);
    //uart_rcv_print();
    return 0;
}

/**
 * @brief 
 * 
 * @return int 
 */
int Jhr_pwr::wrFullVoltage()  //电池满电电压 0.01V
{
    Pwr_dat_3 data;
    short s1 = pwd_setting_data_w.fullVoltage;
    data.dat1 = s1 >> 8; 
    data.dat2 = s1 & 0xff;
    data.dat3 = 0;
    uart_write_pack(0x18,data);
    //uart_rcv_print();
    return 0;
}

/**
 * @brief 单位A，   7.5A->3000,75A -> 300
 * 
 * @return int 
 */
int Jhr_pwr::wrCurrentRange()  //单位A，   7.5A->3000,75A -> 300
{
    Pwr_dat_3 data;
    short s1 = 2250000 / pwd_setting_data_w.currentRange;
    data.dat1 = s1 >> 8; 
    data.dat2 = s1 & 0xff;
    data.dat3 = 0;
    uart_write_pack(0x1A,data);
    //uart_rcv_print();
    return 0;
}

/**
 * @brief 串口读取基础数据
 * 
 * @return int 
 */
int Jhr_pwr::rdBascData() 
{
    Pwr_dat_3 data;
    data.dat1 = 0; data.dat2 = 0; data.dat3 = 0;
    uart_write_pack(0x10,data);
    return 0;
}

/**
 * @brief 串口读取设定数据
 * 
 * @return int 
 */
int Jhr_pwr::rdSettingData()
{
    Pwr_dat_3 data;
    data.dat1 = 0; data.dat2 = 0; data.dat3 = 0;
    uart_write_pack(0x09,data);
    return 0;
}




