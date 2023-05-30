;; Auto-generated. Do not edit!


(when (boundp 'jhr_type_2023::Jhr_points)
  (if (not (find-package "JHR_TYPE_2023"))
    (make-package "JHR_TYPE_2023"))
  (shadow 'Jhr_points (find-package "JHR_TYPE_2023")))
(unless (find-package "JHR_TYPE_2023::JHR_POINTS")
  (make-package "JHR_TYPE_2023::JHR_POINTS"))

(in-package "ROS")
;;//! \htmlinclude Jhr_points.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass jhr_type_2023::Jhr_points
  :super ros::object
  :slots (_header _points ))

(defmethod jhr_type_2023::Jhr_points
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:points __points) ())
    )
   (send-super :init)
   (setq _header __header)
   (setq _points __points)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:points
   (&rest __points)
   (if (keywordp (car __points))
       (send* _points __points)
     (progn
       (if __points (setq _points (car __points)))
       _points)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; jhr_type_2023/Jhr_point[] _points
    (apply #'+ (send-all _points :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; jhr_type_2023/Jhr_point[] _points
     (write-long (length _points) s)
     (dolist (elem _points)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; jhr_type_2023/Jhr_point[] _points
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _points (let (r) (dotimes (i n) (push (instance jhr_type_2023::Jhr_point :init) r)) r))
     (dolist (elem- _points)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get jhr_type_2023::Jhr_points :md5sum-) "b5a347b507bfdfb23842aa0f4df79f03")
(setf (get jhr_type_2023::Jhr_points :datatype-) "jhr_type_2023/Jhr_points")
(setf (get jhr_type_2023::Jhr_points :definition-)
      "Header header
jhr_type_2023/Jhr_point[] points
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

================================================================================
MSG: jhr_type_2023/Jhr_point
float32 X
float32 Y
float32 A
")



(provide :jhr_type_2023/Jhr_points "b5a347b507bfdfb23842aa0f4df79f03")


