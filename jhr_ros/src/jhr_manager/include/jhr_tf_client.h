/**
 * @file jhr_tf_client.h
 * lly
 * @brief 
 * @version 0.1
 * @date 2023-03-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __JHR_TF_CLIENT_H__
#define __JHR_TF_CLIENT_H__
#include "ros/ros.h"
#include <tf2_msgs/TFMessage.h>
void tf_callback(const tf2_msgs::TFMessage &tf);
typedef struct{
    float X = 0.0f;
    float Y = 0.0f;
    float A = 0.0f;
}Jhr_tf_data;
extern Jhr_tf_data jhr_curr_pose;
#endif
