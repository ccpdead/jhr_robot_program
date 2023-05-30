; Auto-generated. Do not edit!


(cl:in-package jhr_type_2023-srv)


;//! \htmlinclude SetRobot-request.msg.html

(cl:defclass <SetRobot-request> (roslisp-msg-protocol:ros-message)
  ((type
    :reader type
    :initarg :type
    :type cl:integer
    :initform 0)
   (msg
    :reader msg
    :initarg :msg
    :type cl:string
    :initform ""))
)

(cl:defclass SetRobot-request (<SetRobot-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetRobot-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetRobot-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name jhr_type_2023-srv:<SetRobot-request> is deprecated: use jhr_type_2023-srv:SetRobot-request instead.")))

(cl:ensure-generic-function 'type-val :lambda-list '(m))
(cl:defmethod type-val ((m <SetRobot-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader jhr_type_2023-srv:type-val is deprecated.  Use jhr_type_2023-srv:type instead.")
  (type m))

(cl:ensure-generic-function 'msg-val :lambda-list '(m))
(cl:defmethod msg-val ((m <SetRobot-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader jhr_type_2023-srv:msg-val is deprecated.  Use jhr_type_2023-srv:msg instead.")
  (msg m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetRobot-request>) ostream)
  "Serializes a message object of type '<SetRobot-request>"
  (cl:let* ((signed (cl:slot-value msg 'type)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'msg))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'msg))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetRobot-request>) istream)
  "Deserializes a message object of type '<SetRobot-request>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'type) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'msg) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'msg) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetRobot-request>)))
  "Returns string type for a service object of type '<SetRobot-request>"
  "jhr_type_2023/SetRobotRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetRobot-request)))
  "Returns string type for a service object of type 'SetRobot-request"
  "jhr_type_2023/SetRobotRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetRobot-request>)))
  "Returns md5sum for a message object of type '<SetRobot-request>"
  "7cbfb8a0467c30430a839a7c40eb6982")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetRobot-request)))
  "Returns md5sum for a message object of type 'SetRobot-request"
  "7cbfb8a0467c30430a839a7c40eb6982")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetRobot-request>)))
  "Returns full string definition for message of type '<SetRobot-request>"
  (cl:format cl:nil "int32 type~%string msg~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetRobot-request)))
  "Returns full string definition for message of type 'SetRobot-request"
  (cl:format cl:nil "int32 type~%string msg~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetRobot-request>))
  (cl:+ 0
     4
     4 (cl:length (cl:slot-value msg 'msg))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetRobot-request>))
  "Converts a ROS message object to a list"
  (cl:list 'SetRobot-request
    (cl:cons ':type (type msg))
    (cl:cons ':msg (msg msg))
))
;//! \htmlinclude SetRobot-response.msg.html

(cl:defclass <SetRobot-response> (roslisp-msg-protocol:ros-message)
  ((type
    :reader type
    :initarg :type
    :type cl:integer
    :initform 0)
   (msg
    :reader msg
    :initarg :msg
    :type cl:string
    :initform ""))
)

(cl:defclass SetRobot-response (<SetRobot-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetRobot-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetRobot-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name jhr_type_2023-srv:<SetRobot-response> is deprecated: use jhr_type_2023-srv:SetRobot-response instead.")))

(cl:ensure-generic-function 'type-val :lambda-list '(m))
(cl:defmethod type-val ((m <SetRobot-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader jhr_type_2023-srv:type-val is deprecated.  Use jhr_type_2023-srv:type instead.")
  (type m))

(cl:ensure-generic-function 'msg-val :lambda-list '(m))
(cl:defmethod msg-val ((m <SetRobot-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader jhr_type_2023-srv:msg-val is deprecated.  Use jhr_type_2023-srv:msg instead.")
  (msg m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetRobot-response>) ostream)
  "Serializes a message object of type '<SetRobot-response>"
  (cl:let* ((signed (cl:slot-value msg 'type)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'msg))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'msg))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetRobot-response>) istream)
  "Deserializes a message object of type '<SetRobot-response>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'type) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'msg) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'msg) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetRobot-response>)))
  "Returns string type for a service object of type '<SetRobot-response>"
  "jhr_type_2023/SetRobotResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetRobot-response)))
  "Returns string type for a service object of type 'SetRobot-response"
  "jhr_type_2023/SetRobotResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetRobot-response>)))
  "Returns md5sum for a message object of type '<SetRobot-response>"
  "7cbfb8a0467c30430a839a7c40eb6982")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetRobot-response)))
  "Returns md5sum for a message object of type 'SetRobot-response"
  "7cbfb8a0467c30430a839a7c40eb6982")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetRobot-response>)))
  "Returns full string definition for message of type '<SetRobot-response>"
  (cl:format cl:nil "int32 type~%string msg~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetRobot-response)))
  "Returns full string definition for message of type 'SetRobot-response"
  (cl:format cl:nil "int32 type~%string msg~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetRobot-response>))
  (cl:+ 0
     4
     4 (cl:length (cl:slot-value msg 'msg))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetRobot-response>))
  "Converts a ROS message object to a list"
  (cl:list 'SetRobot-response
    (cl:cons ':type (type msg))
    (cl:cons ':msg (msg msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'SetRobot)))
  'SetRobot-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'SetRobot)))
  'SetRobot-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetRobot)))
  "Returns string type for a service object of type '<SetRobot>"
  "jhr_type_2023/SetRobot")