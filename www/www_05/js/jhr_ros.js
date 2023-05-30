let jhr_ros={
    ws_url : "ws://192.168.11.70:9090",
    ros_obj:null,
    ros_init:function(){
        if(this.ros_obj == null){
            this.ros_obj = new ROSLIB.Ros({url : this.ws_url});
            this.ros_obj.on('connection', function() {
                jhr_ros_work.ros_topic_init();
                console.log('Connected to websocket server.');
                $("#status_1").text("连接成功");
            });
            this.ros_obj.on('error', function(error) {
                console.log('Error connecting to websocket server: ', error);
                $("#status_1").text("连接错误:" + error);
            });
            this.ros_obj.on('close', function() {
                console.log('Connection to websocket server closed.');
                $("#status_1").text("连接关闭");
            });
        }
    },
}
