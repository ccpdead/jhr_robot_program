$(function(){
    $("#time_start").datetimebox({
        //value: "01/01/2000",
        required: true,
        showSeconds: false
    });
    $("#time_end").datetimebox({
        //value: "01/01/2000",
        required: true,
        showSeconds: false
    });
    setInterval(function(){
        $("#status_5").text(jhr_storage.timestampToTime(new Date()));
        jhr_task.loop();
    },1000);
    $("#img_detect").attr("src","http://10.10.10.178/image/detect.jpg");
    jhr_ros.ros_init();
    jhr_index.btn_listen();
    jhr_index.btn_data_test();
    jhr_index.operation_record_date();
    jhr_index.btn_data_import();
    jhr_ctrl.init();
    
    jhr_storage.operation_record_set(1000,1120,true,2.5,12.3);

    
});
let jhr_index={
    //按钮监听事件
    btn_listen:function(){
        //到达指定坐标
        $("#cmdGO").click(function(){
            jhr_ros_work.publish_move_base_simple(jhr_ros_work.map_click.x,jhr_ros_work.map_click.y,0);
        });
        
        //创建地图
        $("#cmdCreateMap").click(function(){
            jhr_ros_work.call_manager_srv(10,$('#map_name_create').val());
        });
        //保存地图
        $("#cmdSaveMap").click(function(){
            jhr_ros_work.call_manager_srv(20,'');
        });
        //调入地图
        $("#cmdLoadMap").click(function(){
            var map = $('#mapCombobox').combobox('getValue');
            if(map.length > 0){
                jhr_ros_work.call_manager_srv(30,$('#mapCombobox').combobox('getValue'));
                console.log($('#mapCombobox').combobox('getValue'));
            }else{
                alert("请选择地图");
            }
        });
        //读取地图列表
        $("#cmdGetMapList").click(function(){
            jhr_ros_work.call_manager_srv(40,'');
        });
        //启动任务
        $("#cmd_task_start").click(function(){
            //jhr_task.start(false);
            let obj={
                enable : true,
                repeat: -1,
                distance:2,
                data:[
                    {X:0  ,Y:0, A:0    ,name:"01",reg21: 30, reg22:10, reg23:5, reg24: 0},
                    {X:8.6,Y:0, A:0    ,name:"02",reg21: 30, reg22:10, reg23:5, reg24: 0},
                    {X:7.2,Y:4.2,A:1.57,name:"03",reg21: 30, reg22:10, reg23:8, reg24: 0},
                    {X:0  ,Y:3.4,A:3.14,name:"04",reg21: 30, reg22:10, reg23:7, reg24: 0},
                    {X:0  ,Y:0, A:-1.57,name:"05",reg21: 30, reg22:10, reg23:8, reg24: 0},
                ]
            }
            jhr_ros_work.call_manager_srv(50,JSON.stringify(obj));
        });
        //停止任务
        $("#cmd_task_stop").click(function(){
            jhr_ros_work.call_manager_srv(51,'');
        });
        //暂停任务
        $("#cmd_task_pause").click(function(){
            jhr_ros_work.call_manager_srv(52,'');
        });
        //继续任务
        $("#cmd_task_continue").click(function(){
            jhr_ros_work.call_manager_srv(53,'');
        });

    },
    /**
     * 把搜索出来的数据记录显示出来
     * @param {} obj 
     */
    record_show:function(arr_obj){
        var arr_out=[];
        var obj_table=document.getElementById("tb_data_record");
        var row_num=obj_table.rows.length;
        console.log("record_show",row_num);
        //删除所有记录
        for(i=1; i< row_num; i++)obj_table.deleteRow(row_num-i);
        console.log("obj_table.rows.length:",obj_table.rows.length,arr_obj.length)
        var i_len = arr_obj.length;
        for(i=0; i< i_len; i++){
            var j_rec = JSON.parse(localStorage.getItem(arr_obj[i]));
            var newRow = obj_table.insertRow(obj_table.rows.length);
            var cell_0 = newRow.insertCell(0); cell_0.innerHTML = j_rec.r_name;
            var cell_1 = newRow.insertCell(1); cell_1.innerHTML = j_rec.time_start;
            var cell_2 = newRow.insertCell(2); cell_2.innerHTML = j_rec.time_stop.slice(11);
            var cell_3 = newRow.insertCell(3); cell_3.innerHTML = j_rec.speed;
            var cell_4 = newRow.insertCell(4); cell_4.innerHTML = j_rec.is_collision;
            var cell_5 = newRow.insertCell(5); cell_5.innerHTML = (j_rec.distance*1.0).toFixed(3);
            var cell_6 = newRow.insertCell(6); cell_6.innerHTML = (j_rec.time_work*1.0).toFixed(2);
        }
    },
    //数据查询点击事件
    btn_search:function(){
        $("#btn_search").click(function(){
            var tmpSt = $("#time_start").val();
            var tmpEnd = $("#time_end").val();
            let t_arr = jhr_storage.operation_record_search(tmpSt,tmpEnd);
            jhr_index.record_show(t_arr);
        });
    },
    btn_data_import:function(){
        $("#btn_data_import").click(function(){
            //jhr_storage.operation_record_download();
            jhr_storage.operation_record_excel();
        });
    },
    //测试添加一个数据
    btn_data_test:function(){
        $("#btn_data_test").click(function(){
            jhr_storage.operation_record_set(1000,1120,true,2.5,12.3);
            jhr_storage.operation_record_save();
        });
    },
    
    cls_span2_click:function(){
        $(".cls_span2").click(function(){
            let date_st = new Date($(this).text());
            let date_end = new Date($(this).text()+ " 23:59:59");
            let t_arr = jhr_storage.operation_record_search(date_st,date_end);
            jhr_index.record_show(t_arr);
            /*var str_out = "";
            var arr_len = t_arr.length;
            for(i=0; i< arr_len; i++)
            {
                str_out += localStorage.getItem(t_arr[i]) + "<br />"
            }
            $("#tmp_001").html(str_out);*/
        })
    },
    //把数据记录的日期列表添加到数据记录里
    operation_record_date:function(){
        var t_arr = jhr_storage.operation_record_date();
        var str_out=[];
        var arr_len = t_arr.length;
        for(i=0; i< arr_len; i++)
        {
            str_out.push('<button class="cls_span2">');
            str_out.push(t_arr[i]);
            str_out.push('</button>');
        }
        $("#data_rec").html(str_out.join(''));
        this.cls_span2_click();
    },
    mapCombobox_sp_click:function(){
        $('#mapCombobox_sp span').click(function(){
            var v = $(this).text();
            $('#mapCombobox').combo('setValue', v).combo('setText', v).combo('hidePanel');
            console.log($('#mapCombobox').combobox('getValue'));
        });
    },
};