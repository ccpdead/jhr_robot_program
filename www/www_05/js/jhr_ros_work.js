/**
 *  /usr/bin/python3 /opt/ros/noetic/bin/roslaunch jhr_bringup jhrobot_bringup.launch
    /usr/bin/python3 /opt/ros/noetic/bin/roslaunch jhr_navigation rgbd_location_with_odom.launch
    /usr/bin/python3 /opt/ros/noetic/bin/roslaunch rosbridge_server rosbridge_websocket.launch
 */
let jhr_ros_work={
    linear : 0.0,
    angular : 0.0,
    gridClient:null,
    mapViewer : null,   //地图Viewer
    navigationArrow : null,  //机器人箭头
    polygon : null, 
    path_scan_points: null, //画激光点
    cmd_vel:null,               //设置速度话题
    pathShape_nav: null,
    
    robot_msg_pub:null,         //运行一次返回的话题
    map_param:{
        hasMap : false, //是否具有一个地图
        mapWidth : 620, //图片宽度
        mapHeight: 450, //图片高度
        X0: 0,  //图片左下角坐标
        Y0: 0
    },
    map_click:{x:0,y:0},    //地图点击坐标地址
    map_flush: function () {
        if (jhr_ros.ros_obj == null) return;
        if (this.gridClient == null) {
            this.gridClient = new ROS2D.OccupancyGridClient({
                ros : jhr_ros.ros_obj,
                topic: '/rtabmap/grid_map',  //地图 topic
                rootObject : this.mapViewer.scene,
                continuous: true      //
            });
            this.gridClient.on('change', function () { 
                jhr_ros_work.rcv_map();
                jhr_ros_work.rcv_pose(jhr_ros_tf.tf_curr_pose);
            });
            console.log("首次创建地图");
        } else {
            this.gridClient.subscribe(jhr_ros.ros_obj, '/rtabmap/grid_map', true);
            console.log("重复创建地图");
        }
    },
    //话题初始化
    ros_topic_init:function(){
        this.cmd_vel = new ROSLIB.Topic({
            ros: jhr_ros.ros_obj,
            name:'/cmd_vel_movebase',
            //messageType : 'geometry_msgs/Twist'
        });
        this.robot_msg_pub = new ROSLIB.Topic({
            ros: jhr_ros.ros_obj,
            name:'/robot_msg_pub',
            //messageType : '/jhr_control' 
        });
        this.robot_msg_pub.subscribe(function(msg){
            
        });
        this.mapViewer = new ROS2D.Viewer({
            divID : 'map',
            width : this.map_param.mapWidth,
            height :this.map_param.mapHeight,
            background:'#7f7f7f'    //默认背景色
        });
        //地图点击
        this.mapViewer.scene.addEventListener('stagemousedown', function (event) {
            jhr_ros_work.map_click = jhr_ros_work.mapViewer.scene.globalToRos(event.stageX, event.stageY);
            $('#map_point_sel').text("( " + jhr_ros_work.map_click.x.toFixed(3) + " , " + jhr_ros_work.map_click.y.toFixed(3) + " )");
        });
        this.polygon = new ROS2D.PolygonMarker({
			lineSize:0.1,
            lineColor : createjs.Graphics.getRGB(100, 100, 255, 0),
            pointSize : 0.1,
            pointColor: createjs.Graphics.getRGB(255, 0, 0, 1),
			pointCallBack : null,
			lineCallBack : null
		});
        this.mapViewer.scene.addChild(this.polygon);
        this.polygon.addPoint({x:1,y:1,z:0});
        this.polygon.addPoint({x:10,y:2,z:0});
        this.polygon.addPoint({x:2,y:1,z:0});

        // Setup the map client.
        this.map_flush();

        this.tfClient = new ROSLIB.Topic({
            ros: jhr_ros.ros_obj,
            name:'/tf',
        });
        this.tfClient.subscribe(function(msg){
            jhr_ros_tf.jhr_rcv_tf(msg);
        });

        //激光topic
        this.topic_scan_points = new ROSLIB.Topic({
            ros: jhr_ros.ros_obj,
            name: '/scan',
            messageType: 'sensor_msgs/LaserScan'
        });
        if (this.path_scan_points == null) {
            this.path_scan_points = new ROS2D.PointShape({
                pointSize: 0.1,
                pointColor: createjs.Graphics.getRGB(255, 0, 0),
            });
            this.mapViewer.scene.addChild(this.path_scan_points);
        }
        this.topic_scan_points.subscribe(function (msg) {
            jhr_ros_work.rcv_scan(msg);
        });
        //导航topic
        this.pathShape_nav = new ROS2D.PathShape({
            strokeSize: 0.1,
            strokeColor: createjs.Graphics.getRGB(0, 255, 0),
        });
        this.mapViewer.scene.addChild(this.pathShape_nav);
        //导航路径
        var topic_nav_plan = new ROSLIB.Topic({
            ros: jhr_ros.ros_obj,
            name: '/move_base/GlobalPlanner/plan',
            messageType: 'nav_msgs/Path'
        });
        topic_nav_plan.subscribe(function (msg) {
             jhr_ros_work.rcv_nav_plan(msg); 
        });
        //定点巡航
        var topic_jhr_cruise = new ROSLIB.Topic({
            ros: jhr_ros.ros_obj,
            name: '/jhr_ros/jhr_cruise',
            messageType: 'std_msgs/String'
        });
        topic_jhr_cruise.subscribe(function (msg) {
            jhr_ros_work.rcv_jhr_cruise(msg.data);
        });
        //定点巡航
        var topic_jhr_pwr = new ROSLIB.Topic({
            ros: jhr_ros.ros_obj,
            name: '/jhr_ros/jhr_pwr',
            messageType: 'std_msgs/String'
        });
        topic_jhr_pwr.subscribe(function (msg) {
            jhr_ros_work.rcv_jhr_pwr(msg.data);
        });
    },
    rcv_jhr_pwr:function(msg)
    {
        let obj = JSON.parse(msg);
        let c_out=[];
        c_out.push(obj.voltage/100); c_out.push("V ");
        c_out.push(obj.current/100); c_out.push("A ");
        c_out.push(obj.percent); c_out.push("% ");
        if(obj.direction==0)c_out.push("放电"); else c_out.push("充电");
        $("#status_4").text(c_out.join(''));
        //console.log(obj);
    },
    rcv_jhr_cruise:function(msg)
    {
        let obj = JSON.parse(msg);
        //console.log(obj)
        if(!obj.enable){
            $("#status_2").text("巡航完成");
        }else if(obj.pause){
            $("#status_2").text("暂停巡航");
        }else{
            $("#status_2").text("巡航:" + obj.count + " 点:" + obj.point.id 
                + " 状态:" + obj.point.state + "_" + obj.plc_reg.reg28);
        }
    },
    /**
     * 收到导航路径话题
     * @param {*} msg 
     */
    rcv_nav_plan:function(msg){
        if (msg.poses.length < 1) {
            msg.poses.push({ pose: { position: { x: 0, y: 0, z: 0 } } });
            msg.poses.push({ pose: { position: { x: 0, y: 0, z: 0 } } });
        }
        this.pathShape_nav.setPath(msg);
    },
    //导航到达指定位置
    publish_move_base_simple:function(x,y,angle){
        if(!jhr_ros.ros_obj.isConnected)return;
        console.log("go:",x,y,angle)
        var cmdGO = new ROSLIB.Topic({
            ros: jhr_ros.ros_obj,
            name : '/move_base_simple/goal',
            messageType : 'geometry_msgs/PoseStamped'
        });
        var msg = new ROSLIB.Message({
            "header": {"frame_id": "map"}, 
                "pose": {"position": {"y": parseFloat(y), "x": parseFloat(x), "z": 0.0}, 
                    "orientation": jhr_ros_tf.ros_eulerian_quadruple(0,0,angle * Math.PI / 180)
                }
        });
        cmdGO.publish(msg);
    },
    publish_move_cancel:function(){
        if(!jhr_ros_ws.isConnected())return;
        var cmdCancel = new ROSLIB.Topic({
            ros: jhr_ros.ros_obj,
            name : '/move_base/cancel',
            messageType : 'actionlib_msgs/GoalID'
        });
        var msg = new ROSLIB.Message({
            "id": ""
        });
        cmdCancel.publish(msg);
    },
    /**
     * 收到激光雷达话题
     * @param {} msg 
     */
    rcv_scan:function(msg)
    {
        var scan_points = { poses: [] };
        let len = msg.ranges.length;
        let jd_c =parseFloat(msg.angle_min) +  parseFloat(jhr_ros_tf.tf_curr_pose.A);  
        for(let i=0; i< len; i++){
            let r = msg.ranges[i];
            let x = r * Math.cos(jd_c) + parseFloat(jhr_ros_tf.tf_curr_pose.X);
            let y = r * Math.sin(jd_c) + parseFloat(jhr_ros_tf.tf_curr_pose.Y);
            scan_points.poses.push({ pose: { position: { x: x, y: y, z: 0 } } });
            jd_c += parseFloat(msg.angle_increment);
        }
        if (scan_points.poses.length > 0) {
            this.path_scan_points.setPath(scan_points);
        }
    },
    /**
     * 收到地图话题
     */
    rcv_map:function()
    {
        this.mapViewer.width = this.gridClient.currentGrid.width / this.gridClient.currentGrid.scaleX;
        this.mapViewer.height = this.gridClient.currentGrid.height / this.gridClient.currentGrid.scaleY;
        this.mapViewer.scaleToDimensions(this.gridClient.currentGrid.width,this.gridClient.currentGrid.height);
        /*let X0 = this.gridClient.currentGrid.pose.position.x;
        let Y0 = this.gridClient.currentGrid.pose.position.y;
        this.mapViewer.shift(X0 - this.map_param.X0,Y0 - this.map_param.Y0);
        this.map_param.X0 = X0;
        this.map_param.Y0 = Y0;
        */
        this.map_param.hasMap = true;
    },
    /**
     * TF计算出坐标信息后调用
     * @param {} msg 
     * @returns 
     */
    rcv_pose:function(msg){
        if (this.mapViewer == null) return;
        if(this.navigationArrow == null){
            this.navigationArrow = new ROS2D.NavigationArrow({
                size : 0.5,
                strokeSize : 0.1,
                strokeColor : createjs.Graphics.getRGB(255, 0, 0),
                fillColor : createjs.Graphics.getRGB(255, 0, 0),
                pulse:false
            });
            this.mapViewer.scene.addChild(this.navigationArrow);
        }
        if(this.map_param.hasMap){
            var X0 = msg.X - this.map_param.mapWidth /2 * this.gridClient.currentGrid.scaleX ;
            var Y0 = msg.Y - this.map_param.mapHeight /2 * this.gridClient.currentGrid.scaleY ;
            this.mapViewer.shift(X0 - this.map_param.X0,Y0 - this.map_param.Y0);
            this.map_param.X0 = X0;
            this.map_param.Y0 = Y0;

            this.navigationArrow.x = msg.X;
            this.navigationArrow.y = msg.Y * -1;
            this.navigationArrow.rotation = msg.A * -180 / Math.PI;
        }
    },
    /** 发布速度话题 */
    publish_cmdVel:function(linear,angular){
        this.linear = linear; this.angular = angular;
        if(jhr_ros.ros_obj !=null && jhr_ros.ros_obj.isConnected){
            var twist = new ROSLIB.Message({
                linear : {
                  x : linear,
                  y : 0.0,
                  z : 0.0
                },
                angular : {
                  x : 0.0,
                  y : 0.0,
                  z : angular
                }
            });
            this.cmd_vel.publish(twist);
        }
    },
    //参数信息
    ros_param_init:function(){
        this.param_max_distance= new ROSLIB.Param({
            ros : jhr_ros.ros_obj,
            name : '/jhr_control/max_distance'
        });
    },
    //收到地图列表处理
    result_map_list:function(msg){
        let dd = JSON.parse(msg);
        $('#mapCombobox_sp').text("");
        let opt = [];
        let len = dd.length;
        for(let i=0; i< len; i++){
            opt.push('<span style="display: block;cursor:pointer;">');
            opt.push(dd[i]);
            opt.push('</span>')
        }
        $('#mapCombobox_sp').html(opt.join(''));
        jhr_index.mapCombobox_sp_click();
    },
    call_manager_srv:function(type,msg){
        var client = new ROSLIB.Service({
            ros : jhr_ros.ros_obj,
            name :  "/jhr_ros/JhrManageSrv",
            serviceType : "jhr_type_2023/SetRobot"
        });
        var request = new ROSLIB.ServiceRequest({type:type,msg:msg});
        client.callService(request, function(result) {
            switch(result.type){
                case 10:$("#status_2").text("创建地图:");break;
                case 20:$("#status_2").text("保存地图");jhr_ros_work.result_map_list(result.msg);break;
                case 30:$("#status_2").text("调入地图");break;
                case 40:$("#status_2").text("读取地图列表");jhr_ros_work.result_map_list(result.msg);break;
                case 50:$("#status_2").text("开始巡航");break;
                case 51:$("#status_2").text("停止巡航");break;
                case 52:$("#status_2").text("暂停巡航");break;
                case 53:$("#status_2").text("继续巡航");break;
                default:
                    console.log("111",result);
            }
            //jhr_ros_work.map_flush();
        });
    },
    
   
    
   
    
}