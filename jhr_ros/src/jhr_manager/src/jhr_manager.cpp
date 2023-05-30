/**
 * @file jhr_manager.cpp
 * @author lly
 * @brief 
 * @version 0.1
 * @date 2023-03-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "ros/ros.h"  
#include "actionlib_msgs/GoalID.h"
#include "geometry_msgs/PoseStamped.h"
#include "std_msgs/String.h"
#include <tf/transform_datatypes.h>
#include "jhr_service.h"
#include "jhr_tf_client.h"
#include "jhr_point_cruise.h"
#include "jhr_cleanbao.h"
#include "jhr_pwr.h"
ros::Publisher *move_cancel_ptr = NULL;
ros::Publisher *move_to_pub_ptr = NULL;
ros::Publisher *jhr_cruise_pub_ptr = NULL;
ros::Publisher *jhr_pwr_pub_ptr = NULL;
/** 到达指定位置 **/
void publish_move_base_simple(float X,float Y,float angle)
{
    geometry_msgs::PoseStamped poseA;
    poseA.header.stamp = ros::Time::now();
    poseA.header.frame_id = "map";
    poseA.pose.position.x = X;
    poseA.pose.position.y = Y;
    poseA.pose.position.z = 0.0f;
    poseA.pose.orientation = tf::createQuaternionMsgFromYaw(angle);
    if(move_to_pub_ptr != NULL)move_to_pub_ptr->publish(poseA);
}
//终止导航
void publish_move_cancel(void){
    actionlib_msgs::GoalID p_c;
    p_c.stamp = ros::Time::now();
    p_c.id = "";
    if(move_cancel_ptr != NULL)move_cancel_ptr->publish(p_c);
}
//发布巡航信息
void public_jhr_cruise(const char* data)
{
    std_msgs::String msg;
    std::string str(data);
    msg.data = str;
    if(jhr_cruise_pub_ptr != NULL)jhr_cruise_pub_ptr->publish(msg);
}
//发布电量信息
void public_jhr_pwr(const char* data)
{
    std_msgs::String msg;
    std::string str(data);
    msg.data = str;
    if(jhr_pwr_pub_ptr != NULL)jhr_pwr_pub_ptr->publish(msg);
}

//#include <sstream>  
int main(int argc,char**argv)
{
    ros::init(argc, argv, "jhr_manager");
    ros::NodeHandle n;
    ros::ServiceServer jhr_manage_mapping_service = n.advertiseService("/jhr_ros/JhrManageSrv",jhr_manage_srv);
    ros::Subscriber tf_sub = n.subscribe("/tf",1,tf_callback);  //订阅TF
    
    ros::Publisher move_cancel =  n.advertise<actionlib_msgs::GoalID>("/move_base/cancel", 1); 
    move_cancel_ptr = &move_cancel;
    ros::Publisher move_to_pub = n.advertise<geometry_msgs::PoseStamped>("/move_base_simple/goal", 1); 
    move_to_pub_ptr = &move_to_pub;
    ros::Publisher jhr_cruise_pub =  n.advertise<std_msgs::String>("/jhr_ros/jhr_cruise", 1); 
    jhr_cruise_pub_ptr = &jhr_cruise_pub;

    ros::Publisher jhr_pwr_pub =  n.advertise<std_msgs::String>("/jhr_ros/jhr_pwr", 1); 
    jhr_pwr_pub_ptr = &jhr_pwr_pub;

    ros::Rate loop_rate(50);
    Jhr_pwr::init();
    ROS_INFO("Jhr manager is started");
    while(ros::ok()){
        ros::spinOnce(); 
        loop_rate.sleep();
        jhr_point_curise_loop();
        cleanbao_loop();
        Jhr_pwr::loop();
    }
    return 0;
}