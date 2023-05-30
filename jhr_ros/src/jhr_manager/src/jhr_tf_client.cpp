/**
 * @file jhr_tf_client.cpp
 * @author lly
 * @brief 
 * @version 0.1
 * @date 2023-03-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "jhr_tf_client.h"
Jhr_tf_data jhr_curr_pose;
Jhr_tf_data tf_map_odom;
Jhr_tf_data tf_odom_base;
Jhr_tf_data tf_map_rtaodom;
Jhr_tf_data tf_rtaodom_base;
#include <vector>
#ifndef MATH_PI
#define MATH_PI 3.1415926535897931
#endif
void get_curr_pose(Jhr_tf_data* map_odom,Jhr_tf_data*odom_base);
float quadruple_eulerian(float x,float y,float z,float w);
void eulerian_quadruple(float roll,float pitch,float yaw,
    float *x,float *y,float *z,float *w);

void tf_callback(const tf2_msgs::TFMessage &tf)
{
    const std_msgs::Header *header;
    const std::string *child_frame_id;
    const geometry_msgs::Transform *transform;
    const std::string *frame_id;
    const geometry_msgs::Vector3 *translation;
    const geometry_msgs::Quaternion *rotation;
    float X,Y,A;
    int iLen = tf.transforms.size();
    for(int i=0;i<iLen ; i++){
        header = &tf.transforms[i].header;
        child_frame_id = &tf.transforms[i].child_frame_id;
        transform = &tf.transforms[i].transform;
        frame_id = &header->frame_id;
        translation = &transform->translation;
        rotation = &transform->rotation;
        A = quadruple_eulerian(rotation->x,rotation->y,rotation->z,rotation->w);
        X = translation->x;
        Y = translation->y;
        if(frame_id->compare("map") == 0){
            if(child_frame_id->compare("wheel_odom_link") == 0){
                tf_map_odom.X = X;
                tf_map_odom.Y = Y;
                tf_map_odom.A = A;
                get_curr_pose(&tf_map_odom,&tf_odom_base);
            }
            if(child_frame_id->compare("rtabmap_odom") == 0){
                tf_map_rtaodom.X = X;
                tf_map_rtaodom.Y = Y;
                tf_map_rtaodom.A = A;
                get_curr_pose(&tf_map_rtaodom,&tf_rtaodom_base);
            }
        }
        if(child_frame_id->compare("base_footprint") == 0){
            if(frame_id->compare("wheel_odom_link") == 0){
                tf_odom_base.X = X;
                tf_odom_base.Y = Y;
                tf_odom_base.A = A;
            }
            if(frame_id->compare("rtabmap_odom") == 0){
                tf_rtaodom_base.X = X;
                tf_rtaodom_base.Y = Y;
                tf_rtaodom_base.A = A;
            }
        }
    }
}

/**
 * 四元组转角度
 * */
float quadruple_eulerian(float x,float y,float z,float w) {
	double fRoll  = atan2(2 * (w * x + y * z) , 1 - 2 * (x * x + y * y));
	double fPitch = asin(2 * (w * y - z * x));
    double fYaw   = atan2(2 * (w * z + x * y) , 1 - 2 * (y * y + z * z));
	return (float) fYaw;
}
/** 角度转四元数
 * */
void eulerian_quadruple(float roll,float pitch,float yaw,
    float *x,float *y,float *z,float *w)
{
    float fCosHRoll = cos(roll * 0.5);
    float fSinHRoll = sin(roll * 0.5);
	float fCosHPitch = cos(pitch * 0.5);
	float fSinHPitch = sin(pitch * 0.5);
    float fCosHYaw = cos(yaw * 0.5);
	float fSinHYaw = sin(yaw * 0.5);
	*w = fCosHRoll * fCosHPitch * fCosHYaw + fSinHRoll * fSinHPitch * fSinHYaw;
	*x = fSinHRoll * fCosHPitch * fCosHYaw - fCosHRoll * fSinHPitch * fSinHYaw;
	*y = fCosHRoll * fSinHPitch * fCosHYaw + fSinHRoll * fCosHPitch * fSinHYaw;
    *z = fCosHRoll * fCosHPitch * fSinHYaw - fSinHRoll * fSinHPitch * fCosHYaw;
}

void get_curr_pose(Jhr_tf_data* map_odom,Jhr_tf_data*odom_base)
{
     float x0 = map_odom->X;
	float y0 = map_odom->Y;
	float a0 = map_odom->A;
	float x1 = odom_base->X;
	float y1 = odom_base->Y;
    float a1 = odom_base->A;
	double dR = sqrt(x1*x1 + y1*y1);
	double dA = atan2(y1,x1);
	double x2 = x0 + dR* cos(a0 + dA);
	double y2 = y0 + dR * sin(a0 + dA);
	float a2 = a1 + a0;
	if(a2 < -MATH_PI) a2 += (MATH_PI * 2);
	if(a2 > MATH_PI) a2 -= (MATH_PI * 2);
    jhr_curr_pose.X = x2;
    jhr_curr_pose.Y = y2;
    jhr_curr_pose.A = a2;
}