/**
 * @file jhr_point_cruise.cpp
 * @author lly
 * @brief 
 * @version 0.1
 * @date 2023-03-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include<vector>
#include <string>
#include "cJSON.h"
#include "jhr_point_cruise.h"
#include "jhr_tf_client.h"
#include "jhr_cleanbao.h"
#include "jhr_uart.h"
#include <iostream> 

typedef struct{
    float X;
    float Y;
    float A;
    float reg[4];
    char name[32];
}Cls_point_crurise;
//巡航点位数据
std::vector <Cls_point_crurise> data_crurise;
float distance = 1.0f;  //判断到达
bool j_pause = false;
//是否启用
bool enable = false;
//重复次数,小于等于0表示无限重复，大于0表示巡航指定次数
int repeat = -1;
//当前运行的点位序号
int curr_point_id = 0;
/** 当前运行点位状态 
0：初始,10:发送到达点位命令，20:等待到达点位,
30:发送开始消毒命令,31:等待消毒完成,32:消毒完成,发送停止消毒命令 并且转到 40
40: 点位序号加一，转到0
*/
int curr_point_state = 0;
//当前巡航次数
int curr_count = 0;

/**
 * @brief 发布巡航 topic
 * 
 */
void public_message()
{
    cJSON *root = cJSON_CreateObject();
    cJSON *obj_enable, *obj_pause, *obj_repeat, * obj_count,*obj_point;
    cJSON *obj_point_id, *obj_point_name, *obj_point_state,*obj_point_x,*obj_point_y,*obj_point_a;
    cJSON *obj_plc,*obj_plc_reg;

    obj_plc = cJSON_CreateObject();
    char buff[10];
    for(int i=0; i< 8; i++){
        sprintf(buff,"reg%d",21+i);
        obj_plc_reg = cJSON_CreateNumber(cleanbao_reg_21[i]);
        cJSON_AddItemToObject(obj_plc,buff,obj_plc_reg);
    }

    float X = 0,Y = 0,A = 0;
    if(curr_point_id >=0 && curr_point_id < data_crurise.size()){
        X = data_crurise[curr_point_id].X;
        Y = data_crurise[curr_point_id].Y;
        A = data_crurise[curr_point_id].A;
        obj_point_name = cJSON_CreateString(data_crurise[curr_point_id].name);    
    }else{
        obj_point_name = cJSON_CreateString("p1"); 
    }
    obj_point_id = cJSON_CreateNumber(curr_point_id);
    obj_point_x = cJSON_CreateNumber(X);
    obj_point_y = cJSON_CreateNumber(Y);
    obj_point_a = cJSON_CreateNumber(A);
    obj_point_state = cJSON_CreateNumber(curr_point_state);

    obj_point = cJSON_CreateObject();
    cJSON_AddItemToObject(obj_point,"id",obj_point_id);
    cJSON_AddItemToObject(obj_point,"state",obj_point_state);
    cJSON_AddItemToObject(obj_point,"X",obj_point_x);
    cJSON_AddItemToObject(obj_point,"Y",obj_point_y);
    cJSON_AddItemToObject(obj_point,"A",obj_point_a);
    cJSON_AddItemToObject(obj_point,"name",obj_point_name);

    obj_count = cJSON_CreateNumber(curr_count);
    obj_repeat = cJSON_CreateNumber(repeat);
    if(enable)obj_enable = cJSON_CreateTrue(); else obj_enable = cJSON_CreateFalse();
    if(j_pause)obj_pause = cJSON_CreateTrue(); else obj_pause = cJSON_CreateFalse();

    cJSON_AddItemToObject(root,"enable",obj_enable);
    cJSON_AddItemToObject(root,"pause",obj_pause);
    cJSON_AddItemToObject(root,"repeat",obj_repeat);
    cJSON_AddItemToObject(root,"count",obj_count);
    cJSON_AddItemToObject(root,"point",obj_point);
    cJSON_AddItemToObject(root,"plc_reg",obj_plc);

    //printf("001: %s\n",cJSON_Print(root));
    //printf("002: %s\n",cJSON_PrintUnformatted(root));
    public_jhr_cruise(cJSON_PrintUnformatted(root));
    cJSON_Delete(root);
}

/**
 * @brief 启动巡航
 * 
 * @param strJson 
 * @return int 
 */
int jhr_point_curise_start(const char* strJson)
{
    data_crurise.clear();
    cJSON * root = cJSON_Parse(strJson);
    if(!root){
        printf("no json\n");
        return 1;
    }
    curr_point_id = 0;
    curr_point_state = 0;
    curr_count = 0;
    enable = false;
    j_pause = false;
    cJSON *obj_enable = cJSON_GetObjectItem(root,"enable");
    cJSON *obj_repeat = cJSON_GetObjectItem(root,"repeat");
    cJSON *obj_data = cJSON_GetObjectItem(root,"data");

    
    if(obj_enable && obj_repeat && obj_data){
        if(cJSON_IsArray(obj_data) && cJSON_IsBool(obj_enable) &&  cJSON_IsNumber(obj_repeat))
        {
            cJSON *obj_distance = cJSON_GetObjectItem(root,"distance");
            if(obj_distance && cJSON_IsNumber(obj_distance)){
                distance = cJSON_GetNumberValue(obj_distance);
            }
            int array_size = cJSON_GetArraySize(obj_data);
        ////{X:0  ,Y:0, A:0    ,name:"01",reg21: 30, reg22:10, reg23:10, reg24: 0},
            Cls_point_crurise c_p_c;
            cJSON * item;
            cJSON * obj_x,*obj_y, *obj_a;
            cJSON * obj_name, *obj_reg21, * obj_reg22,*obj_reg23,*obj_reg24;
            for(int i=0; i< array_size; i++)
            {
                c_p_c.reg[0] = 10;c_p_c.reg[1] = 10;c_p_c.reg[2] = 10;c_p_c.reg[3] = 10;
                item = cJSON_GetArrayItem(obj_data,i);
                if(!(obj_x = cJSON_GetObjectItem(item,"X")))obj_x = cJSON_GetObjectItem(item,"x");
                if(!(obj_y = cJSON_GetObjectItem(item,"Y")))obj_y = cJSON_GetObjectItem(item,"y");
                if(!(obj_a = cJSON_GetObjectItem(item,"A")))obj_a = cJSON_GetObjectItem(item,"a");
                if(obj_x) c_p_c.X = cJSON_GetNumberValue(obj_x);
                if(obj_y) c_p_c.Y = cJSON_GetNumberValue(obj_y);
                if(obj_a) c_p_c.A = cJSON_GetNumberValue(obj_a);
                if((obj_name = cJSON_GetObjectItem(item,"name")))
                    strcpy(c_p_c.name , cJSON_GetStringValue(obj_name));
                else
                    strcpy(c_p_c.name,"p_t");
                if(obj_reg21 = cJSON_GetObjectItem(item,"reg21"))
                    c_p_c.reg[0] = cJSON_GetNumberValue(obj_reg21);
                if(obj_reg22 = cJSON_GetObjectItem(item,"reg22"))
                    c_p_c.reg[1] = cJSON_GetNumberValue(obj_reg22);
                if(obj_reg23 = cJSON_GetObjectItem(item,"reg23"))
                    c_p_c.reg[2] = cJSON_GetNumberValue(obj_reg23);
                if(obj_reg24 = cJSON_GetObjectItem(item,"reg24"))
                    c_p_c.reg[3] = cJSON_GetNumberValue(obj_reg24);

                data_crurise.push_back(c_p_c);
            }
            repeat = obj_repeat -> valueint;
            if(cJSON_IsTrue(obj_enable)) enable = true; else enable = false;
            std::cout << "repeat: " << repeat <<"  enable:" << enable << std::endl;
            for(std::vector<Cls_point_crurise>::iterator it = data_crurise.begin(); it != data_crurise.end(); it ++)
            {
                std::cout << "X:" << it->X << " Y:" << it -> Y << " A:" << it -> A << std::endl;
            }
        }
    }
    cJSON_Delete(root);
    return 0;
}
void jhr_point_curise_stop()
{
    enable = false;
    publish_move_cancel();
    cleanbao_reg_21[4] = 0;
    cleanbao_write_reg_25();
}
void jhr_point_curise_pause()
{
    j_pause = true;
    curr_point_state = 0;
    publish_move_cancel();
    cleanbao_reg_21[4] = 0;
    cleanbao_write_reg_25();
}
void jhr_point_curise_continue()
{
    curr_point_state = 0;
    publish_move_cancel();
    j_pause = false;
}
void jhr_point_curise_loop()
{
    static int last_time = 0;   //剩余时间
    if(!enable || j_pause)return;
    int array_size = data_crurise.size();
    //最后一个点位完成则退出或者下一循环
    if(curr_point_id >= array_size || curr_point_id < 0){
        curr_count ++;
        curr_point_id = 0;
        curr_point_state = 0;
        if(repeat >0 && repeat <= curr_count){
            enable = false;
            public_message();
            std::cout << ":巡航完成" << std::endl;
            return;
        }
        std::cout << ":新的巡航" << std::endl;
    }
    switch(curr_point_state){
        case 0:
        case 10:    //发送到达点位命令
            public_message();
            publish_move_base_simple(data_crurise[curr_point_id].X,
                data_crurise[curr_point_id].Y,data_crurise[curr_point_id].A);
            curr_point_state = 20;
            break;
        case 20:    //等待到达点位
        {
            float x0 = jhr_curr_pose.X;
            float y0 = jhr_curr_pose.Y;
            float x1 = data_crurise[curr_point_id].X;
            float y1 = data_crurise[curr_point_id].Y;
            float len = sqrt((x0-x1)*(x0-x1)+(y0-y1)*(y0-y1));
            if(len < distance){
                public_message();
                curr_point_state =  30;
                cleanbao_is_21 = false;
                cleanbao_is_25 = false;
                cleanbao_is_26 = false;
                cleanbao_serial_close();
                std::cout << "到达位置:"<< curr_point_id <<" x="<< x0 <<" y=" << y0 <<" A=" << jhr_curr_pose.A << std::endl;
            }
        }
            break;
        case 30:    //设置消毒机
            if(cleanbao_is_21){
                curr_point_state = 31;
            }else if(cleanbao_serial_isOpen() <= 0){
                for(int i=0; i< 4; i++)
                    cleanbao_reg_21[i] = data_crurise[curr_point_id].reg[i];
                cleanbao_write_reg_21();
            }
            break;
        case 31:    //发送消毒命令
            if(cleanbao_is_25){
                curr_point_state = 32;
                cleanbao_reg_21[5] = 0; 
            }else if(cleanbao_serial_isOpen() <= 0){
                cleanbao_reg_21[4] = 1;
                cleanbao_write_reg_25();
            }
            break;
        case 32:    //等待消毒完成
            if(cleanbao_is_26){
                if(cleanbao_reg_21[5] == 1)
                    curr_point_state = 33;
                else
                    cleanbao_is_26 = false;
                if(last_time != cleanbao_reg_21[7]){
                    last_time = cleanbao_reg_21[7];
                    public_message();
                }
            }else if(cleanbao_serial_isOpen() <= 0){
                cleanbao_read_reg();
            }
            break;
        case 33:    //等待停止命令完成
            curr_point_state = 40;
            break;
        case 40:    //点位序号加一， 到达下一个点
            curr_point_id ++;
            curr_point_state = 0;
            std::cout << ":巡航下一个点:" << curr_point_id << std::endl;
            break;
    }
}