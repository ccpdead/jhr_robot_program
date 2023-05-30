; Auto-generated. Do not edit!


(cl:in-package jhr_type_2023-msg)


;//! \htmlinclude Jhr_points.msg.html

(cl:defclass <Jhr_points> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (points
    :reader points
    :initarg :points
    :type (cl:vector jhr_type_2023-msg:Jhr_point)
   :initform (cl:make-array 0 :element-type 'jhr_type_2023-msg:Jhr_point :initial-element (cl:make-instance 'jhr_type_2023-msg:Jhr_point))))
)

(cl:defclass Jhr_points (<Jhr_points>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Jhr_points>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Jhr_points)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name jhr_type_2023-msg:<Jhr_points> is deprecated: use jhr_type_2023-msg:Jhr_points instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <Jhr_points>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader jhr_type_2023-msg:header-val is deprecated.  Use jhr_type_2023-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'points-val :lambda-list '(m))
(cl:defmethod points-val ((m <Jhr_points>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader jhr_type_2023-msg:points-val is deprecated.  Use jhr_type_2023-msg:points instead.")
  (points m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Jhr_points>) ostream)
  "Serializes a message object of type '<Jhr_points>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'points))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'points))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Jhr_points>) istream)
  "Deserializes a message object of type '<Jhr_points>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'points) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'points)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'jhr_type_2023-msg:Jhr_point))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Jhr_points>)))
  "Returns string type for a message object of type '<Jhr_points>"
  "jhr_type_2023/Jhr_points")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Jhr_points)))
  "Returns string type for a message object of type 'Jhr_points"
  "jhr_type_2023/Jhr_points")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Jhr_points>)))
  "Returns md5sum for a message object of type '<Jhr_points>"
  "b5a347b507bfdfb23842aa0f4df79f03")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Jhr_points)))
  "Returns md5sum for a message object of type 'Jhr_points"
  "b5a347b507bfdfb23842aa0f4df79f03")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Jhr_points>)))
  "Returns full string definition for message of type '<Jhr_points>"
  (cl:format cl:nil "Header header~%jhr_type_2023/Jhr_point[] points~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: jhr_type_2023/Jhr_point~%float32 X~%float32 Y~%float32 A~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Jhr_points)))
  "Returns full string definition for message of type 'Jhr_points"
  (cl:format cl:nil "Header header~%jhr_type_2023/Jhr_point[] points~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: jhr_type_2023/Jhr_point~%float32 X~%float32 Y~%float32 A~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Jhr_points>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'points) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Jhr_points>))
  "Converts a ROS message object to a list"
  (cl:list 'Jhr_points
    (cl:cons ':header (header msg))
    (cl:cons ':points (points msg))
))
