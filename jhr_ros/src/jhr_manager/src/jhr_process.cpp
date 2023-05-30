/**
 * @file jhr_process.cpp
 * @author lly
 * @brief 
 * @version 0.1
 * @date 2023-03-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "ros/ros.h"  
#include <sys/types.h>
#include <dirent.h>
#include "jhr_process.h"
/**
 * @brief 修改launch中 第一个 database_path 参数的值
 * 
 * @param fLaunch 需要修改的launch文件
 * @param fMap 需要保存的地图名称
 * @return int 错误返回errno，  否则返回 0
 */
int Jhr_chg_launch(const char* fLaunch,const char*fMap)
{
    const char* key = "\"database_path\"";
    FILE* fp,*fptmp;
    char buff[1024];
    char* ptr;
    int cnt = 0;
    fp = fopen(fLaunch, "r");
    if(fp == NULL){
        perror("fOpem src()");
        return errno;
    }
    fptmp = tmpfile();
    if(fptmp == NULL){
        perror("fOpem tmp()");
        return errno;
    }
    while(fgets(buff,sizeof(buff), fp)){
        ptr = strstr(buff,key);
        if(ptr && (cnt == 0)){
            cnt ++;
            sprintf(buff,"  <arg name=\"database_path\" default=\"%s\"/>\n",fMap);
        } 
        fputs(buff,fptmp);
    }
    fclose(fp);
    fp = fopen(fLaunch, "w");
    if(fptmp == NULL){
        perror("fOpem fp w()");
        return errno;
    }
    fseek(fptmp,0L,SEEK_SET);
    while(fgets(buff,sizeof(buff), fptmp)){
        fputs(buff,fp);
    }
    fclose(fp);
    fclose(fptmp);
    return 0;
}

/**
 * @brief 发现指定的launch线程
 * 
 * @param fName launch名称
 * @param pid 查询到的进程号 
 * @return int 错误返回errno，  否则返回 0
 */
int Jhr_find_process(const char* fLaunch,int *pid)
{
    FILE * fp;
    char* ptr;
    int cnt = 0;
    char buff[1024];
    char buf_usr[256];
    *pid = 0;
    fp = popen("ps -aux | grep roslaunch","r");
    if(fp == NULL){
        perror("fOpem src()");
        return errno;
    }
    while(fgets(buff,sizeof(buff),fp) != NULL)
    {
        ptr = strstr(buff,fLaunch);
        if(ptr && (cnt == 0)){
            sscanf(buff,"%s %d",buf_usr,pid);
            printf("usr:%s,pid:%d\n",buf_usr,*pid);
            cnt ++;
        }
    }
    pclose(fp);
    return 0;
}

/**
 * @brief 
 * 杀死线程
 * @param pid 
 * @return int 
 */
int Jhr_kill_process(int pid){
    FILE * fp;
    char buff[2048];
    sprintf(buff,"kill %d\n",pid);
    fp = popen(buff,"r");
    if(fp == NULL){
        perror("fOpem kill()");
        return errno;
    }
    while(fgets(buff,sizeof(buff),fp) != NULL){
        printf("%s",buff);
    }
    pclose(fp);
    return 0;
}

/**
 * @brief 
 * 运行程序
 * @param pid 
 * @return int 
 */
int Jhr_run_process(char*fName){
    FILE * fp;
    char buff[2048];
    int cnt = 0;
    sprintf(buff,"%s &\n",fName);
    fp = popen(buff,"r");
    if(fp == NULL){
        perror("fOpem run()");
        return errno;
    }
    while(fgets(buff,sizeof(buff),fp) != NULL){
        printf("%s",buff);
        if(cnt++ > 10)break;
    }
    pclose(fp);
    return 0;
}


/**********************************************************/
const char* LANCH_PATH = "/home/jhr/jhr_launch/";    //launch路径
const char* LANCH_NAVIGATION = "rgbd_location_with_odom.launch"; //导航
const char* LANCH_CREATE_MAP = "rgbd_infra.launch"; //建图
const char* MAP_PATH = "/home/jhr/.ros/";//"~/.ros/";  //地图所在的路径

/** 创建地图
 * @brief Create a map object
 * 
 * @param map 
 */
void create_map(const char* map)
{
    int pid;
    char path[256];
    char map_name[128];
    if(Jhr_find_process(LANCH_CREATE_MAP,&pid) == 0 && pid != 0){
        printf("线程号:%d\n",pid);
        Jhr_kill_process(pid);
    }
    if(Jhr_find_process(LANCH_NAVIGATION,&pid) == 0 && pid != 0){
        printf("线程号:%d\n",pid);
        Jhr_kill_process(pid);
    }
	ros::Duration(5).sleep();
	sprintf(path,"%s%s",LANCH_PATH,LANCH_CREATE_MAP);
    sprintf(map_name,"%s%s.db",MAP_PATH, map);
    Jhr_chg_launch(path,map_name);
    sprintf(path,"roslaunch %s%s",LANCH_PATH,LANCH_CREATE_MAP);
    Jhr_run_process(path);
}

/** 保存地图
 * @brief 
 * 
 */
void save_map()
{
    int pid;
    char path[256];
    char map_name[128];
    if(Jhr_find_process(LANCH_CREATE_MAP,&pid) == 0 && pid != 0){
        printf("线程号:%d\n",pid);
        Jhr_kill_process(pid);
    }
    if(Jhr_find_process(LANCH_NAVIGATION,&pid) == 0 && pid != 0){
        printf("线程号:%d\n",pid);
        Jhr_kill_process(pid);
    }
    ros::Duration(5).sleep();
}


/** 获取地图名称列表
 * @brief Get the map list object
 * 
 * @return std::string 
 */
std::string get_map_list()
{
    DIR    *dir;
    struct    dirent    *ptr;
    dir = opendir(MAP_PATH);
    if(dir == NULL)
    {
        perror("get_map_list opendir:");
        return "[]";
    }
    std::stringstream sstream;
    sstream << "[";
    int index = 0;
    while((ptr = readdir(dir)) != NULL)
    {
        int iLen = strlen(ptr->d_name);
        if(iLen > 3)
        {
            int i1 = 0;
            if(ptr->d_name[iLen -3] == '.')i1 ++;
            if(ptr->d_name[iLen -2] == 'D' || ptr->d_name[iLen -2] == 'd')i1 ++;
            if(ptr->d_name[iLen -1] == 'B' || ptr->d_name[iLen -1] == 'b')i1 ++;
            //std::cout <<"类型:"<< ptr->d_type<< "  文件名:"<< ptr->d_name <<"  tp:" << i1;  
            if(i1 == 3)
            {
                ptr->d_name[iLen - 3] = '\0';
                if(index >0)sstream << ",";
                sstream << "\"" << ptr->d_name << "\"";
                index ++;
                //std::cout << "  文件名:" << ptr->d_name;
            }
            //std::cout << std::endl;
        }
    }
    closedir(dir);
    sstream << "]";
    return sstream.str();
}

/**
 * @brief 进入导航
 * 
 * @param map 
 */
void j_navigation(const char* map)
{
    int pid;
    char path[256];
    char map_name[128];
    if(Jhr_find_process(LANCH_CREATE_MAP,&pid) == 0 && pid != 0){
        printf("线程号:%d\n",pid);
        Jhr_kill_process(pid);
    }
    if(Jhr_find_process(LANCH_NAVIGATION,&pid) == 0 && pid != 0){
        printf("线程号:%d\n",pid);
        Jhr_kill_process(pid);
    }
	ros::Duration(5).sleep();
    sprintf(path,"%s%s",LANCH_PATH,LANCH_NAVIGATION);
    sprintf(map_name,"%s%s.db",MAP_PATH,map);
    Jhr_chg_launch(path,map_name);
    sprintf(path,"roslaunch %s%s",LANCH_PATH,LANCH_NAVIGATION);
    Jhr_run_process(path);
}



