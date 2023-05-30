/**
 * @file jhr_uart.cpp
 * @author lly
 * @brief 
 * @version 0.1
 * @date 2023-03-23
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <iostream>
#include     <stdio.h>      /*标准输入输出定义*/
#include     <stdlib.h>     /*标准函数库定义*/
#include     <unistd.h>     /*Unix 标准函数定义*/
#include     <sys/types.h>  /*数据类型，比如一些XXX_t的那种*/
#include     <sys/stat.h>   /*定义了一些返回值的结构，没看明白*/
#include     <fcntl.h>      /*文件控制定义*/
#include     <termios.h>    /*PPSIX 终端控制定义*/
#include     <errno.h>      /*错误号定义*/

#include "jhr_uart.h"
Jhr_uart::Jhr_uart(): uart_fd(-1),
    device("/dev/ttyCleanBao"),band(115200),
    parity('N'),data_bit(8),stop_bit(1)
{
}
Jhr_uart::Jhr_uart(std::string _device,int _band): 
    uart_fd(-1),device("/dev/ttyCleanBao"),band(115200),
    parity('N'),data_bit(8),stop_bit(1)
{
    Jhr_uart();
    device = _device;
    band = _band;
}
Jhr_uart::~Jhr_uart()
{

}

int Jhr_uart::uart_open()
{
    const int arr_bps[]={
        B0,B50,B75,B110,B134,B150,B200,B300,
        B600,B1200,B1800,B2400,B4800,B9600,B19200,B38400,
        B57600,B115200,B230400};
    const int arr_bps_in[]={
        0,50,75,110,134,150,200,300,
        600,1200,1800,2400,4800,9600,19200,38400,
        57600,115200,230400};
    uart_fd = open(device.c_str(),O_RDWR | O_NOCTTY |O_NDELAY);
    if(-1 == uart_fd){
        perror(device.c_str());
        return -1;
    }
    tcflush(uart_fd, TCIOFLUSH);//设置前flush
    struct termios Opt;
    if(tcgetattr(uart_fd,&Opt) != 0)
    {
        perror("SetupSerial 2");
        close(uart_fd);
        uart_fd = -1;
        return -1;
    }
    //设置波特率
    int iBps = B19200;
    int iLen = sizeof( arr_bps_in) / sizeof( arr_bps_in[0]);
    for(int i1=0;i1 < iLen;i1++){
        if(band == arr_bps_in[i1]){
            iBps = arr_bps[i1];
            break;
        }
    }
    cfsetispeed(&Opt,iBps);
    cfsetospeed(&Opt,iBps);

    Opt.c_cflag &= ~CSIZE;
    switch(data_bit){
        case 7:Opt.c_cflag |= CS7;break;
        default:Opt.c_cflag |= CS8;
    }
    switch(parity){
        case 'o':
        case 'O':
            Opt.c_cflag |= PARENB;
            Opt.c_cflag |=PARODD;
            Opt.c_iflag |=(INPCK | ISTRIP);
            break;
        case 'E':
        case 'e':
            Opt.c_iflag |=(INPCK | ISTRIP);
            Opt.c_cflag |=PARENB;
            Opt.c_cflag &= ~PARODD;
            break;
        default:
            Opt.c_cflag &= ~PARENB; /* Clear parity enable */
            Opt.c_iflag = IGNPAR;
    }
    Opt.c_cflag &= ~CSTOPB;
    if(stop_bit == 1){ //设置停止位
        Opt.c_cflag &= ~CSTOPB;
    }else{
        Opt.c_cflag |= CSTOPB;
    }
    Opt.c_oflag = 0;
    Opt.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);//不经处理直接发送。
    int   status;
    status = tcsetattr(uart_fd, TCSANOW, &Opt);
    if(status != 0){
        perror("tcsetattr fd1");
        close(uart_fd);
        uart_fd = -1;
        return -1;
    }
    tcflush(uart_fd,TCIOFLUSH);  //设置后flush
    int flags = fcntl(uart_fd, F_GETFL, 0);   //获取文件的flags值
    fcntl(uart_fd, F_SETFL, flags | O_NONBLOCK); //设置成非阻塞模式
    //std::cout<<"串口打开成功："<< uart_fd <<std::endl;
    return 0;
}

int Jhr_uart::uart_open(std::string _device,int _band,char _parity,int _data_bit,int _stop_bit)
{
    device = _device;
    band = _band;
    parity = _parity;
    data_bit = _data_bit;
    stop_bit = _stop_bit;
    return uart_open();
}

/** 关闭串口
 * @brief uart_close
 * @return
 */
int Jhr_uart::uart_close(){
    //std::cout<<" 关闭串口:" << uart_fd;
    if(uart_fd<=0)return 0;
    close(uart_fd);
    uart_fd = -1;
    return 0;
}
int Jhr_uart::getFd()
{
    return uart_fd;
}
/**
 * @brief 
 * 
 * @return int 
 */
int Jhr_uart::uart_isOpen()
{
    if(uart_fd <= 0){
        return 0;
    }else{
        return 1;
    }   
}

/**
 * @brief 
 * 
 * @param array 
 * @param len 
 * @return int 
 */
int Jhr_uart::uart_write(const uint8_t *array,int len){
    //std::cout <<"串口发送:" << uart_fd <<" " << len;
    if(uart_fd<0)return -1;
    len = write(uart_fd,array,len);
    //std::cout <<"串口发送:" << uart_fd <<" " << len;
    return len;
}

/**
 * @brief 
 * 
 * @param array 
 * @param len 
 * @return int 
 */
int Jhr_uart::uart_read(uint8_t*array,int len){
    if(uart_fd<0)return -1;
    int rcv_len = read(uart_fd,array,len);
    //if(rcv_len > 0)std::cout<<"串口收到数据："<< rcv_len <<std::endl;
    return rcv_len;
}

