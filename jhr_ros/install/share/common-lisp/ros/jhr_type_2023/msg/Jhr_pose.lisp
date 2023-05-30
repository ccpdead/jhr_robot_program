; Auto-generated. Do not edit!


(cl:in-package jhr_type_2023-msg)


;//! \htmlinclude Jhr_pose.msg.html

(cl:defclass <Jhr_pose> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (X
    :reader X
    :initarg :X
    :type cl:float
    :initform 0.0)
   (Y
    :reader Y
    :initarg :Y
    :type cl:float
    :initform 0.0)
   (A
    :reader A
    :initarg :A
    :type cl:float
    :initform 0.0)
   (map
    :reader map
    :initarg :map
    :type cl:string
    :initform ""))
)

(cl:defclass Jhr_pose (<Jhr_pose>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Jhr_pose>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Jhr_pose)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name jhr_type_2023-msg:<Jhr_pose> is deprecated: use jhr_type_2023-msg:Jhr_pose instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <Jhr_pose>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader jhr_type_2023-msg:header-val is deprecated.  Use jhr_type_2023-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'X-val :lambda-list '(m))
(cl:defmethod X-val ((m <Jhr_pose>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader jhr_type_2023-msg:X-val is deprecated.  Use jhr_type_2023-msg:X instead.")
  (X m))

(cl:ensure-generic-function 'Y-val :lambda-list '(m))
(cl:defmethod Y-val ((m <Jhr_pose>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader jhr_type_2023-msg:Y-val is deprecated.  Use jhr_type_2023-msg:Y instead.")
  (Y m))

(cl:ensure-generic-function 'A-val :lambda-list '(m))
(cl:defmethod A-val ((m <Jhr_pose>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader jhr_type_2023-msg:A-val is deprecated.  Use jhr_type_2023-msg:A instead.")
  (A m))

(cl:ensure-generic-function 'map-val :lambda-list '(m))
(cl:defmethod map-val ((m <Jhr_pose>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader jhr_type_2023-msg:map-val is deprecated.  Use jhr_type_2023-msg:map instead.")
  (map m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Jhr_pose>) ostream)
  "Serializes a message object of type '<Jhr_pose>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'X))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'Y))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'A))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'map))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'map))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Jhr_pose>) istream)
  "Deserializes a message object of type '<Jhr_pose>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'X) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'Y) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'A) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'map) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'map) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Jhr_pose>)))
  "Returns string type for a message object of type '<Jhr_pose>"
  "jhr_type_2023/Jhr_pose")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Jhr_pose)))
  "Returns string type for a message object of type 'Jhr_pose"
  "jhr_type_2023/Jhr_pose")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Jhr_pose>)))
  "Returns md5sum for a message object of type '<Jhr_pose>"
  "8f8c2ab4000c121b27dee893afca3646")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Jhr_pose)))
  "Returns md5sum for a message object of type 'Jhr_pose"
  "8f8c2ab4000c121b27dee893afca3646")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Jhr_pose>)))
  "Returns full string definition for message of type '<Jhr_pose>"
  (cl:format cl:nil "Header header~%float32 X~%float32 Y~%float32 A~%string map~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Jhr_pose)))
  "Returns full string definition for message of type 'Jhr_pose"
  (cl:format cl:nil "Header header~%float32 X~%float32 Y~%float32 A~%string map~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Jhr_pose>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     4
     4
     4
     4 (cl:length (cl:slot-value msg 'map))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Jhr_pose>))
  "Converts a ROS message object to a list"
  (cl:list 'Jhr_pose
    (cl:cons ':header (header msg))
    (cl:cons ':X (X msg))
    (cl:cons ':Y (Y msg))
    (cl:cons ':A (A msg))
    (cl:cons ':map (map msg))
))
