/**
 * @file jhr_cleanbao.h
 * @author lly
 * @brief 济南科林宝 接口 
 * @version 0.1
 * @date 2023-03-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef __JHR_CLEANBAO_H__
#define __JHR_CLEANBAO_H__

// 读26开始的3个寄存器
void cleanbao_read_reg(void);
//写25 寄存器
void cleanbao_write_reg_25();
//写 21 开始的四的寄存器
void cleanbao_write_reg_21();
//串口接收处理
void cleanbao_loop();
int cleanbao_serial_isOpen();
void cleanbao_serial_close();
extern uint16_t cleanbao_reg_21[];  //消毒机寄存器的值
extern bool cleanbao_is_21 ;    //是否设置21完成
extern bool cleanbao_is_25 ;    //是否设置25完成
extern bool cleanbao_is_26 ;    //是否读取26完成
#endif