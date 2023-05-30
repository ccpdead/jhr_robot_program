;; Auto-generated. Do not edit!


(when (boundp 'jhr_type_2023::SetRobot)
  (if (not (find-package "JHR_TYPE_2023"))
    (make-package "JHR_TYPE_2023"))
  (shadow 'SetRobot (find-package "JHR_TYPE_2023")))
(unless (find-package "JHR_TYPE_2023::SETROBOT")
  (make-package "JHR_TYPE_2023::SETROBOT"))
(unless (find-package "JHR_TYPE_2023::SETROBOTREQUEST")
  (make-package "JHR_TYPE_2023::SETROBOTREQUEST"))
(unless (find-package "JHR_TYPE_2023::SETROBOTRESPONSE")
  (make-package "JHR_TYPE_2023::SETROBOTRESPONSE"))

(in-package "ROS")





(defclass jhr_type_2023::SetRobotRequest
  :super ros::object
  :slots (_type _msg ))

(defmethod jhr_type_2023::SetRobotRequest
  (:init
   (&key
    ((:type __type) 0)
    ((:msg __msg) "")
    )
   (send-super :init)
   (setq _type (round __type))
   (setq _msg (string __msg))
   self)
  (:type
   (&optional __type)
   (if __type (setq _type __type)) _type)
  (:msg
   (&optional __msg)
   (if __msg (setq _msg __msg)) _msg)
  (:serialization-length
   ()
   (+
    ;; int32 _type
    4
    ;; string _msg
    4 (length _msg)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _type
       (write-long _type s)
     ;; string _msg
       (write-long (length _msg) s) (princ _msg s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _type
     (setq _type (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; string _msg
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _msg (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;;
   self)
  )

(defclass jhr_type_2023::SetRobotResponse
  :super ros::object
  :slots (_type _msg ))

(defmethod jhr_type_2023::SetRobotResponse
  (:init
   (&key
    ((:type __type) 0)
    ((:msg __msg) "")
    )
   (send-super :init)
   (setq _type (round __type))
   (setq _msg (string __msg))
   self)
  (:type
   (&optional __type)
   (if __type (setq _type __type)) _type)
  (:msg
   (&optional __msg)
   (if __msg (setq _msg __msg)) _msg)
  (:serialization-length
   ()
   (+
    ;; int32 _type
    4
    ;; string _msg
    4 (length _msg)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _type
       (write-long _type s)
     ;; string _msg
       (write-long (length _msg) s) (princ _msg s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _type
     (setq _type (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; string _msg
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _msg (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;;
   self)
  )

(defclass jhr_type_2023::SetRobot
  :super ros::object
  :slots ())

(setf (get jhr_type_2023::SetRobot :md5sum-) "7cbfb8a0467c30430a839a7c40eb6982")
(setf (get jhr_type_2023::SetRobot :datatype-) "jhr_type_2023/SetRobot")
(setf (get jhr_type_2023::SetRobot :request) jhr_type_2023::SetRobotRequest)
(setf (get jhr_type_2023::SetRobot :response) jhr_type_2023::SetRobotResponse)

(defmethod jhr_type_2023::SetRobotRequest
  (:response () (instance jhr_type_2023::SetRobotResponse :init)))

(setf (get jhr_type_2023::SetRobotRequest :md5sum-) "7cbfb8a0467c30430a839a7c40eb6982")
(setf (get jhr_type_2023::SetRobotRequest :datatype-) "jhr_type_2023/SetRobotRequest")
(setf (get jhr_type_2023::SetRobotRequest :definition-)
      "int32 type
string msg
---
int32 type
string msg
")

(setf (get jhr_type_2023::SetRobotResponse :md5sum-) "7cbfb8a0467c30430a839a7c40eb6982")
(setf (get jhr_type_2023::SetRobotResponse :datatype-) "jhr_type_2023/SetRobotResponse")
(setf (get jhr_type_2023::SetRobotResponse :definition-)
      "int32 type
string msg
---
int32 type
string msg
")



(provide :jhr_type_2023/SetRobot "7cbfb8a0467c30430a839a7c40eb6982")


