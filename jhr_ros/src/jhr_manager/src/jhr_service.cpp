/**
 * @file jhr_service.cpp
 * @author lly
 * @brief 
 * @version 0.1
 * @date 2023-03-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "jhr_service.h"
#include "jhr_process.h"
#include "jhr_point_cruise.h"
enum jhr_cmd_type{
    CMD_CREATE_MAP = 10, //创建地图
    CMD_SAVE_MAP = 20,	//保存地图
    CMD_NAVIGATION = 30,  //导航
    CMD_MAP_LIST = 40,  //获取地图名列表
    CMD_POINT_CRUISE_START = 50,   //顶点巡航 启动
    CMD_POINT_CRUISE_STOP = 51,   //顶点巡航 停止
    CMD_POINT_CRUISE_PAUSE = 52,   //顶点巡航 暂停
    CMD_POINT_CRUISE_CONTINTE = 53,   //顶点巡航 继续
};


bool jhr_manage_srv(jhr_type_2023::SetRobot::Request &req, jhr_type_2023::SetRobot::Response &res)
{
    setlocale(LC_CTYPE, "zh_CN.utf8");
    setlocale(LC_ALL, "");
    res.msg = "Hello world";
    switch(req.type)
    {
        case CMD_CREATE_MAP:
            res.type = req.type;
            create_map(req.msg.c_str());
            res.msg = get_map_list();
            break;
        case CMD_SAVE_MAP:
            res.type = req.type;
            save_map();
            res.msg = get_map_list();
            break;
        case CMD_NAVIGATION:
            res.type = req.type;
            j_navigation(req.msg.c_str());
            res.msg = get_map_list();
            break;
        case CMD_MAP_LIST:
            res.type = req.type;
            res.msg = get_map_list();
            break;
        case CMD_POINT_CRUISE_START:
            res.type = req.type;
            jhr_point_curise_start(req.msg.c_str());
            break;
        case CMD_POINT_CRUISE_STOP:
            res.type = req.type;
            jhr_point_curise_stop();
            break;
        case CMD_POINT_CRUISE_PAUSE:
            res.type = req.type;
            jhr_point_curise_pause();
            break;
        case CMD_POINT_CRUISE_CONTINTE:
            res.type = req.type;
            jhr_point_curise_continue();
            break;
        default:res.type = 0;
    }
    return true;
}
