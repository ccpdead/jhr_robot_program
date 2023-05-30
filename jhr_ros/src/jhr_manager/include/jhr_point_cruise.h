/**
 * @file jhr_point_cruise.h
 * @author lly
 * @brief 
 * @version 0.1
 * @date 2023-03-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __JHR_POINT_CRUISE_H__
#define __JHR_POINT_CRUISE_H__

int jhr_point_curise_start(const char* strJson);
void jhr_point_curise_stop();
void jhr_point_curise_pause();
void jhr_point_curise_continue();
void jhr_point_curise_loop();
/** 到达指定位置 **/
void publish_move_base_simple(float X,float Y,float angle);
//终止导航
void publish_move_cancel(void);
//发布巡航信息
void public_jhr_cruise(const char* data);
#endif
