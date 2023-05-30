/**
 * 工作任务
 */
let jhr_task = {
    //任务工作点
    task_points:[
        {
            name:'点1',
            X:0,
            Y:0
        },
        {
            name:'点2',
            X:8.6,
            Y:-0.0
        },
        {
            name:'点3',
            X:7.2,
            Y:4.1
        },
        {
            name:'点4',
            X:0.0,
            Y:3.4
        },
        {
            name:'点0',
            X:0,
            Y:0
        }
    ],
    //是否启动工作线程
    enable:false,
    //是否重复
    repeat:false,
    //正在运行的点序号
    curr_point:0,
    //是否正在运行当前点
    is_run_curr:false,
    //循环次数
    count: 0,
    //启动任务
    start:function(repeat)
    {
        if(this.task_points.length > 0){
            this.repeat = repeat;
            this.curr_point = 0;
            this.is_run_curr = false;
            this.enable = true;
            this.loop();
        }else{
            this.enable = false;
        }
        //this.count  = 0;
    },
    loop:function()
    {
        if(this.enable){
            if(this.curr_point >= this.task_points.length)
            {
                this.count += 1;
                
                if(this.repeat && this.task_points.length > 0){
                    this.curr_point = 0;
                    this.is_run_curr = false;
                    $("#status_2").text("第 "+ this.count +" 次任务:");
                }else{
                    $("#status_2").text("完成任务:" + this.count);
                    this.enable = false;
                    return;
                }
            }
            if(!this.is_run_curr){
                this.is_run_curr = true;
                jhr_ros_work.publish_move_base_simple(
                    this.task_points[this.curr_point].X,this.task_points[this.curr_point].Y,0
                );
            }else{
                let X0 = this.task_points[this.curr_point].X;
                let Y0 = this.task_points[this.curr_point].Y;
                let X1 = jhr_ros_tf.tf_curr_pose.X;
                let Y1 = jhr_ros_tf.tf_curr_pose.Y;
                let len = Math.sqrt((X0-X1)*(X0-X1)+(Y0-Y1)*(Y0-Y1));
                if(len < 3){
                    this.curr_point ++;
                    this.is_run_curr = false;
                }
            }
        }
    }
}