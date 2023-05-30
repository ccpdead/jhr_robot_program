/**
 * @file jhr_process.h
 * @author lly
 * @brief 
 * @version 0.1
 * @date 2023-03-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __JHR_PROCESS_H__
#define __JHR_PROCESS_H__
#include <string>
//修改launch中 第一个 database_path 参数的值
int Jhr_chg_launch(const char* fLaunch,const char*fMap);
//发现指定的launch线程
int Jhr_find_process(const char* fLaunch,int *pid);
//杀死线程
int Jhr_kill_process(int pid);
//运行程序
int Jhr_run_process(char*fName);

void create_map(const char* map);
void save_map();
std::string get_map_list();
void j_navigation(const char* map);
#endif
