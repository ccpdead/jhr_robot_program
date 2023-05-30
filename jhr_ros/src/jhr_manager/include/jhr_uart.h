/**
 * @file jhr_uart.h
 * @author lly
 * @brief 
 * @version 0.1
 * @date 2023-03-23
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef __JHR_UART_H__
#define __JHR_UART_H__
#include <string>

class Jhr_uart
{
public:
    Jhr_uart();
    Jhr_uart(std::string device,int band);
    virtual ~Jhr_uart();
    int uart_open(std::string device,int band = 115200,
              char parity = 'N',int data_bit = 8,int stop_bit = 1);
    int uart_open();
    int uart_close();
    int uart_isOpen();
    int getFd();
    int uart_write(const uint8_t *array,int len);
    int uart_read(uint8_t*array,int len);
private:
    int uart_fd;
    int band;
    char parity;
    int data_bit;
    int stop_bit;
    std::string device;
};
#endif
