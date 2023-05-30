


let jhr_storage={
    search_param:{
        start:'2021-01-01',
        end:'2021-01-01'
    },
    /** 机器人参数 */
    robot_param : {
        r_name:"机器人",    //样品名称
        time_start_delay:1.23,  //启动延时
        time_back_delay:2.45,   //返回延时
        speed:1.3,          //最大速度
        distance:5.0        //最远行驶距离
    },
    /** 运行记录 */
    operation_record :{
        r_name:"机器人",//机器人名称
        time_start:"0:0:0",//起始时间
        time_stop:"0:0:0",//结束时间
        is_collision:false,//是否碰撞
        speed:"0.0",    //运行速度
        distance:"0.0", //碰撞距离
        time_work:"10.0"    //碰撞时间
    },
    timestampToTime:function(tim){
        let times=tim.toLocaleString('en-US',{hour12: false}).split(" ");
        let time = times[1]
        let mdy = times[0]
        mdy = mdy.split('/')
        let month = parseInt(mdy[0]);
        let day = parseInt(mdy[1]);
        let year = parseInt(mdy[2])
        if(month <10) month = "0" + month;
        if(day < 10) day = "0" + day;
        return year + '-' + month + '-' + day + ' ' + time;
    },
    timestampToTime_1:function(tim){
        var tim_1 = new Date(tim);
        let times=tim_1.toLocaleString('en-US',{hour12: false}).split(" ");
        let time = times[1].split(":");
        let mdy = times[0]
        mdy = mdy.split('/')
        let month = parseInt(mdy[0]);
        let day = parseInt(mdy[1]);
        let year = (parseInt(mdy[2])) % 100;
        if(year < 10) year = '0' + year;
        if(month <10) month = "0" + month;
        if(day < 10) day = "0" + day;
        return year + month + day  + time[0] + time[1];
    },
    /**
     * 记录当前记录
     * start 起始秒数
     * stop 停止秒数
     * is_collision 是否碰撞
     * distance 碰撞距离
     * time_work 碰撞时间单位秒
     */
    operation_record_set:function(start,stop,is_collision,distance,time_work){
        this.operation_record.r_name = this.robot_param.r_name;
        this.operation_record.time_start = this.timestampToTime(new Date((start-stop)*1000+Date.parse(new Date())));
        this.operation_record.time_stop = this.timestampToTime(new Date());
        this.operation_record.is_collision = is_collision;
        this.operation_record.speed = this.robot_param.speed;
        if(is_collision){
            this.operation_record.distance = (distance*1.0).toFixed(3);//(collision_time*1.0).toFixed(2)
            this.operation_record.time_work = (time_work*1.0).toFixed(2);
        }else{
            this.operation_record.distance = 0;
            this.operation_record.time_work = 0;
        }
    },
    /**
     * 保存当前记录
     */
    operation_record_save:function(){
        var date_tick = Date.parse(new Date(this.operation_record.time_start));
        date_tick = parseInt(date_tick / 30 / 1000);
        date_tick = date_tick * 30 * 1000;
        var date_str = this.timestampToTime(new Date(date_tick));
        localStorage.setItem(date_str,JSON.stringify(this.operation_record));
        jhr_index.operation_record_date();  //保存数据后，更新日期数据记录
    },
    /**
     * 遍历数据，找出指定日期的数据
     */
    operation_record_search:function(date_start,date_end){
        let tmp_st = Date.parse(new Date(date_start));
        let tmp_end = Date.parse(new Date(date_end));
        this.search_param.start = date_start;
        this.search_param.end = date_end;
        let tmp_key;
        let i,len,key;
        len = localStorage.length;
        let ret_obj = {};
        for(i=0; i< len; i++)
        {
            key = localStorage.key(i);
            tmp_key = Date.parse(new Date(key));
            if(tmp_key >= tmp_st && tmp_key <= tmp_end) 
                ret_obj[key] = 0;
        }
        let ret_arr= [];
        for(item in ret_obj) {
            ret_arr.push(item);
        }
        return ret_arr.sort();
    },
    /**
     * 遍历数据，找出具有记录的日期
     * @returns 
     */
    operation_record_date:function(){
        let i,len,key;
        len = localStorage.length;
        let ret_obj = {};
        for(i=0; i< len; i++)
        {
            key = localStorage.key(i).slice(0,10);
            ret_obj[key] = 0;
        }
        let ret_arr= [];
        for(item in ret_obj) {
            ret_arr.push(item);
        }
        return ret_arr.reverse();   //反向排序
    },
    /**
     * 
     * @returns 导出json字符串
     */
    operation_record_download:function(){
        let arr_obj = jhr_storage.operation_record_search(this.search_param.start,this.search_param.end);
        var i_len = arr_obj.length;
        if(i_len < 1){
            $("#status_2").text("没有数据");
            return;
        }
        var arr_out=[];
        for(i=0; i< i_len; i++){
            //var j_rec = JSON.parse(localStorage.getItem(arr_obj[i]));
            arr_out.push(localStorage.getItem(arr_obj[i]));
        }
        var f_name = this.timestampToTime(new Date)+ ".txt";
        f_name = f_name.replace(/ /g,"");
        f_name = f_name.replace(/:/g,"");
        f_name = f_name.replace(/-/g,"");
        var file = new File([arr_out.join("\r\n")], f_name, { type: "text/plain;charset=utf-8" });
        saveAs(file);
        $("#status_2").text("导出 "+ i_len +" 条记录");
    },
    operation_record_excel:function(){
        let arr_obj = jhr_storage.operation_record_search(this.search_param.start,this.search_param.end);
        var i_len = arr_obj.length;
        if(i_len < 1){
            $("#status_2").text("没有数据");
            return;
        }
        let excelList = [];
        excelList.push("名称,");
        excelList.push("起始时间,");
        excelList.push("停止时间,");
        excelList.push("速度,");
        excelList.push("是否碰撞,");
        excelList.push("碰撞距离,");
        excelList.push("碰撞时间,");
        excelList.push("\n");
        var name_date_st = "2000-01-01";
        var name_date_end =  name_date_st;
        for(i=0; i< i_len; i++){
            var j_rec = JSON.parse(localStorage.getItem(arr_obj[i]));
            excelList.push(j_rec.r_name), excelList.push(", ");
            excelList.push(j_rec.time_start), excelList.push(", ");
            excelList.push(j_rec.time_stop), excelList.push(",");
            excelList.push(j_rec.speed), excelList.push(",");
            excelList.push(j_rec.is_collision), excelList.push(",");
            excelList.push((j_rec.distance*1.0).toFixed(3)), excelList.push(",");
            excelList.push((j_rec.time_work*1.0).toFixed(2)), excelList.push(",\n");

            if(i == 0){
                name_date_st = j_rec.time_start;
            }
            name_date_end =  j_rec.time_start;
        }

        $("#status_2").text("开始导出EXCEL");
        var merged = excelList.join("");
	    let uri = 'data:text/csv;charset=utf-8,\ufeff' + encodeURIComponent(merged);
	    let link = document.createElement("a");
	    link.href = uri;
        var f_name = this.timestampToTime_1(name_date_st) + "_" + this.timestampToTime_1(name_date_end) + ".csv";
        //console.log("save_name  " + f_name);
        //f_name = this.timestampToTime(new Date)+ ".csv";
        f_name = f_name.replace(/ /g,"");
        f_name = f_name.replace(/:/g,"");
        f_name = f_name.replace(/-/g,"");
	    link.download = f_name;
	    document.body.appendChild(link);
	    link.click();
	    document.body.removeChild(link);
        $("#status_2").text("导出 "+ i_len + " 条记录");
    },
}