;; Auto-generated. Do not edit!


(when (boundp 'jhr_type_2023::Jhr_pose)
  (if (not (find-package "JHR_TYPE_2023"))
    (make-package "JHR_TYPE_2023"))
  (shadow 'Jhr_pose (find-package "JHR_TYPE_2023")))
(unless (find-package "JHR_TYPE_2023::JHR_POSE")
  (make-package "JHR_TYPE_2023::JHR_POSE"))

(in-package "ROS")
;;//! \htmlinclude Jhr_pose.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass jhr_type_2023::Jhr_pose
  :super ros::object
  :slots (_header _X _Y _A _map ))

(defmethod jhr_type_2023::Jhr_pose
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:X __X) 0.0)
    ((:Y __Y) 0.0)
    ((:A __A) 0.0)
    ((:map __map) "")
    )
   (send-super :init)
   (setq _header __header)
   (setq _X (float __X))
   (setq _Y (float __Y))
   (setq _A (float __A))
   (setq _map (string __map))
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:X
   (&optional __X)
   (if __X (setq _X __X)) _X)
  (:Y
   (&optional __Y)
   (if __Y (setq _Y __Y)) _Y)
  (:A
   (&optional __A)
   (if __A (setq _A __A)) _A)
  (:map
   (&optional __map)
   (if __map (setq _map __map)) _map)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; float32 _X
    4
    ;; float32 _Y
    4
    ;; float32 _A
    4
    ;; string _map
    4 (length _map)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; float32 _X
       (sys::poke _X (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _Y
       (sys::poke _Y (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _A
       (sys::poke _A (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; string _map
       (write-long (length _map) s) (princ _map s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; float32 _X
     (setq _X (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _Y
     (setq _Y (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _A
     (setq _A (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; string _map
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _map (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;;
   self)
  )

(setf (get jhr_type_2023::Jhr_pose :md5sum-) "8f8c2ab4000c121b27dee893afca3646")
(setf (get jhr_type_2023::Jhr_pose :datatype-) "jhr_type_2023/Jhr_pose")
(setf (get jhr_type_2023::Jhr_pose :definition-)
      "Header header
float32 X
float32 Y
float32 A
string map
================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
string frame_id

")



(provide :jhr_type_2023/Jhr_pose "8f8c2ab4000c121b27dee893afca3646")


