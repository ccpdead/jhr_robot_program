; Auto-generated. Do not edit!


(cl:in-package jhr_type_2023-msg)


;//! \htmlinclude Jhr_point.msg.html

(cl:defclass <Jhr_point> (roslisp-msg-protocol:ros-message)
  ((X
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
    :initform 0.0))
)

(cl:defclass Jhr_point (<Jhr_point>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Jhr_point>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Jhr_point)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name jhr_type_2023-msg:<Jhr_point> is deprecated: use jhr_type_2023-msg:Jhr_point instead.")))

(cl:ensure-generic-function 'X-val :lambda-list '(m))
(cl:defmethod X-val ((m <Jhr_point>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader jhr_type_2023-msg:X-val is deprecated.  Use jhr_type_2023-msg:X instead.")
  (X m))

(cl:ensure-generic-function 'Y-val :lambda-list '(m))
(cl:defmethod Y-val ((m <Jhr_point>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader jhr_type_2023-msg:Y-val is deprecated.  Use jhr_type_2023-msg:Y instead.")
  (Y m))

(cl:ensure-generic-function 'A-val :lambda-list '(m))
(cl:defmethod A-val ((m <Jhr_point>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader jhr_type_2023-msg:A-val is deprecated.  Use jhr_type_2023-msg:A instead.")
  (A m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Jhr_point>) ostream)
  "Serializes a message object of type '<Jhr_point>"
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
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Jhr_point>) istream)
  "Deserializes a message object of type '<Jhr_point>"
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
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Jhr_point>)))
  "Returns string type for a message object of type '<Jhr_point>"
  "jhr_type_2023/Jhr_point")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Jhr_point)))
  "Returns string type for a message object of type 'Jhr_point"
  "jhr_type_2023/Jhr_point")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Jhr_point>)))
  "Returns md5sum for a message object of type '<Jhr_point>"
  "14206843863907ab243efb1949dfadae")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Jhr_point)))
  "Returns md5sum for a message object of type 'Jhr_point"
  "14206843863907ab243efb1949dfadae")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Jhr_point>)))
  "Returns full string definition for message of type '<Jhr_point>"
  (cl:format cl:nil "float32 X~%float32 Y~%float32 A~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Jhr_point)))
  "Returns full string definition for message of type 'Jhr_point"
  (cl:format cl:nil "float32 X~%float32 Y~%float32 A~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Jhr_point>))
  (cl:+ 0
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Jhr_point>))
  "Converts a ROS message object to a list"
  (cl:list 'Jhr_point
    (cl:cons ':X (X msg))
    (cl:cons ':Y (Y msg))
    (cl:cons ':A (A msg))
))
