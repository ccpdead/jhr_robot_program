let jhr_ros_tf = {
    tf_obj : {},
    tf_map_odom:null,
    tf_map_rtabodom:null,
    tf_odom_base:null,
    tf_rtabodom_base:null,

    tf_curr_pose:{X:0,Y:0,A:0},
    //机器人返回TF处理
    jhr_rcv_tf:function(obj_1){
        let obj = obj_1.transforms[0];
        let frame_id = obj.header.frame_id;
        let child_id = obj.child_frame_id;
        let X = obj.transform.translation.x;
        let Y = obj.transform.translation.y;
        let A = this.ros_quadruple_eulerian(obj.transform.rotation).yaw;
        let obj_val = {X:X,Y:Y,A:A};
        if(obj.header.frame_id == "map"){
            if(obj.child_frame_id == "wheel_odom_link"){
                this.tf_map_odom = obj_val;
                if(this.tf_odom_base != null)this.jhr_get_pose(this.tf_map_odom,this.tf_odom_base);
            }
            if(obj.child_frame_id == "rtabmap_odom"){
                this.tf_map_rtabodom = obj_val;
                if(this.tf_rtabodom_base != null)this.jhr_get_pose(this.tf_map_rtabodom,this.tf_rtabodom_base);
            }
        }
        else if(obj.child_frame_id == "base_footprint"){
            if(obj.header.frame_id == "wheel_odom_link"){
                this.tf_odom_base = obj_val;
            }
            if(obj.header.frame_id == "rtabmap_odom"){
                this.tf_rtabodom_base = obj_val;
            }
        }
        
        /*let key = obj.header.frame_id + "_|_" + obj.child_frame_id;
        this.tf_obj[key] = {X:X,Y:Y,A:A};
        let i = 0;
        for(item in this.tf_obj) {
            //$('#tf_0' + i).html(item + " " + JSON.stringify(this.tf_obj[item]));
            $('#tf_0' + i).html(item );
            i++;
        }*/
    },
    jhr_get_pose:function(map_odom,odom_base){
        if(map_odom == null || odom_base == null)return;
        let x0 = map_odom.X;
        let y0 = map_odom.Y;
        let a0 = map_odom.A;
        let x1 = odom_base.X;
        let y1 = odom_base.Y;
        let a1 = odom_base.A;
        let dR = Math.sqrt(x1*x1 + y1*y1);
        let dA = Math.atan2(y1,x1);
        let x2 = x0 + dR* Math.cos(a0 + dA);
        let y2 = y0 + dR * Math.sin(a0 + dA);
        let a2 = a1 + a0;
        if(a2 < -Math.PI) a2 += (Math.PI * 2);
        if(a2 > Math.PI) a2 -= (Math.PI * 2);
        this.tf_curr_pose = {X:x2.toFixed(3), Y:y2.toFixed(3), A:a2.toFixed(3)};
        $("#status_3").text("X:"+ this.tf_curr_pose.X + " Y:"+ this.tf_curr_pose.Y + " A:"+ parseInt(this.tf_curr_pose.A * 180 / Math.PI));
        jhr_ros_work.rcv_pose(this.tf_curr_pose);
        //$('#tf_00').html(JSON.stringify(this.tf_curr_pose));
    },
    /** 弧度转四元组 */
    ros_eulerian_quadruple:function(fRoll,fPitch,fYaw){
        let fCosHRoll = Math.cos(fRoll * 0.5);
	    let fSinHRoll = Math.sin(fRoll * 0.5);
	    let fCosHPitch = Math.cos(fPitch * 0.5);
	    let fSinHPitch = Math.sin(fPitch * 0.5);
        let fCosHYaw = Math.cos(fYaw * 0.5);
	    let fSinHYaw = Math.sin(fYaw * 0.5);

	    let w = fCosHRoll * fCosHPitch * fCosHYaw + fSinHRoll * fSinHPitch * fSinHYaw;
	    let x = fSinHRoll * fCosHPitch * fCosHYaw - fCosHRoll * fSinHPitch * fSinHYaw;
	    let y = fCosHRoll * fSinHPitch * fCosHYaw + fSinHRoll * fCosHPitch * fSinHYaw;
        let z = fCosHRoll * fCosHPitch * fSinHYaw - fSinHRoll * fSinHPitch * fCosHYaw;
        return {"y": y, "x": x, "z":z, "w": w };
    },
    //四元组转弧度
    ros_quadruple_eulerian:function(obj){
	    let x = obj.x; let y = obj.y; let z = obj.z; let w = obj.w;
	    let fRoll  = Math.atan2(2 * (w * x + y * z) , 1 - 2 * (x * x + y * y));
	    let fPitch = Math.asin(2 * (w * y - z * x));
        let fYaw   = Math.atan2(2 * (w * z + x * y) , 1 - 2 * (y * y + z * z));
        return {"roll": fRoll, "pitch": fPitch, "yaw":fYaw};
    },
};