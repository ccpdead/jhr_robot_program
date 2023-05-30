/**
 * @file jhr_service.h
 * @author lly
 * @brief 
 * @version 0.1
 * @date 2023-03-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __JHR_SERVICE_H__
#define __JHR_SERVICE_H__
#include "jhr_type_2023/SetRobot.h"

bool jhr_manage_srv(jhr_type_2023::SetRobot::Request &req, jhr_type_2023::SetRobot::Response &res);
#endif
