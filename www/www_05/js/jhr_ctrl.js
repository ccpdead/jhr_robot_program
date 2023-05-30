let jhr_ctrl={
    stage : null,
    func_right:function(){
        $("#status_2").text("向右 "+ (new Date()).toLocaleTimeString());
        jhr_ros_work.publish_cmdVel(0.0,-0.5);
    },
    func_down:function(){
        $("#status_2").text("向后 "+ (new Date()).toLocaleTimeString());
        jhr_ros_work.publish_cmdVel(-0.3,0.0);
    },
    func_left:function(){
        $("#status_2").text("向左 "+ (new Date()).toLocaleTimeString());
        jhr_ros_work.publish_cmdVel(0.0,0.5);
    },
    func_up:function(){
        $("#status_2").text("向前 "+ (new Date()).toLocaleTimeString());
        jhr_ros_work.publish_cmdVel(0.3,0.0);
    },
    func_right_up:function(){
        $("#status_2").text("右前 "+ (new Date()).toLocaleTimeString());
        jhr_ros_work.publish_cmdVel(0.3,-0.5);
    },
    func_right_down:function(){
        $("#status_2").text("右后 "+ (new Date()).toLocaleTimeString());
        jhr_ros_work.publish_cmdVel(-0.3,0.5);
    },
    func_left_up:function(){
        $("#status_2").text("左前 "+ (new Date()).toLocaleTimeString());
        jhr_ros_work.publish_cmdVel(0.3,0.5);
    },
    func_left_down:function(){
        $("#status_2").text("左后 "+ (new Date()).toLocaleTimeString());
        jhr_ros_work.publish_cmdVel(-0.3,-0.5);
    },
    func_stop:function(){
        $("#status_2").text("停车 "+ (new Date()).toLocaleTimeString());
        jhr_ros_work.publish_cmdVel(0.0,0.0);
    },
    //初始化
    init:function(){
        var myCanvas=document.getElementById("myCanvas");
        this.stage = new createjs.Stage(myCanvas);
        createjs.Touch.enable(this.stage);   //启动触摸事件
        var x=200, y=200 , r0=200, r1= 70;
        
        
        temp_param = [["#ddd6e5","向右",this.func_right],["#923931","右后",this.func_right_down],
                    ["#95cddc","向后",this.func_down],["#7e649e","左后",this.func_left_down],
                    ["#ddd6e5","向左",this.func_left],["#923931","左前",this.func_left_up],
                    ["#95cddc","向前",this.func_up],["#7e649e","右前",this.func_right_up]];

        var i,cnt = temp_param.length;
        var count_s = [];
        var temp_jd = Math.PI / cnt;
        for(i=0; i< cnt; i++){
            count_s[i] = this.draw_001(x, y, r0,r1,temp_jd * (2 * i - 1) ,temp_jd * (2 * i + 1),temp_param[i][0],temp_param[i][1]);  
            this.stage.addChild(count_s[i]);
            //count_s[i].on("click",temp_param[i][2], null, false, null);
            count_s[i].on("mousedown",temp_param[i][2], null, false, null);
            count_s[i].on("click", this.func_stop , null, false, null);
        }
        var cont_center = this.draw_center(x,y,r1,"停止");
        this.stage.addChild(cont_center);
        cont_center.on("mousedown",this.func_stop, null, false, null);
        this.stage.update();
        setInterval(function(){
            if(jhr_ros_work.linear != 0.0 || jhr_ros_work.angular != 0.0)
            {
                jhr_ros_work.publish_cmdVel(jhr_ros_work.linear,jhr_ros_work.angular);
            }
        },200);
    },

    draw_001:function(x,y,r0,r1,jd_start,jd_stop,color,title){
        var cont = new createjs.Container();
        var c_s = new createjs.Shape();
        var c_1 = c_s.graphics;
        var d_r0 = Math.atan2(2,r0);
        var d_r1 = Math.atan2(2,r1);
        c_1.beginStroke("#00000000");
        c_1.beginFill(color);
        var k_x0 = r0*Math.cos(jd_start+d_r0);
        var k_y0 = r0*Math.sin(jd_start+d_r0);
        //var k_x1 = r1*Math.cos(jd_start+d_r1);
        //var k_y1 = r1*Math.sin(jd_start+d_r1);
        //var k_x2 = r0*Math.cos(jd_stop-d_r0);
        //var k_y2 = r0*Math.sin(jd_stop-d_r0);
        var k_x3 = r1*Math.cos(jd_stop-d_r1);
        var k_y3 = r1*Math.sin(jd_stop-d_r1);
        c_1.moveTo(k_x0, k_y0);
        c_1.arc(0,0,r0,jd_start+d_r0,jd_stop-d_r0,0);
        c_1.lineTo(k_x3,k_y3);
        c_1.arc(0,0,r1,jd_stop-d_r1,jd_start+d_r1,1);
        c_1.lineTo(k_x0, k_y0);
        cont.addChild(c_s);
        
        var title = new createjs.Text(title, "normal 18px microsoft yahei", "#ff0000");
        var jd_1 = (jd_start + jd_stop)/2;
        title.x = (r0+r1)/2 * Math.cos(jd_1)-18;
        title.y = (r0+r1)/2 * Math.sin(jd_1)-9;
        cont.addChild(title);


        cont.x = x;
        cont.y = x;
        return cont;
    },
    draw_center:function(x,y,r,title)
    {
        var cont = new createjs.Container();
        var c_s = new createjs.Shape();
        var c_1 = c_s.graphics;
        c_1.beginStroke("#00000000");
        c_1.beginFill("#ffe080");
        c_1.drawCircle(0,0,r-4);
        cont.addChild(c_s);
        var title = new createjs.Text(title, "normal 18px microsoft yahei", "#ff0000");
        title.x = -18;
        title.y = -9;
        cont.addChild(title);
        cont.x = x;
        cont.y = x;
        return cont;
    },
}