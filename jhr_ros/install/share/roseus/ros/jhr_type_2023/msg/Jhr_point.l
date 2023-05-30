;; Auto-generated. Do not edit!


(when (boundp 'jhr_type_2023::Jhr_point)
  (if (not (find-package "JHR_TYPE_2023"))
    (make-package "JHR_TYPE_2023"))
  (shadow 'Jhr_point (find-package "JHR_TYPE_2023")))
(unless (find-package "JHR_TYPE_2023::JHR_POINT")
  (make-package "JHR_TYPE_2023::JHR_POINT"))

(in-package "ROS")
;;//! \htmlinclude Jhr_point.msg.html


(defclass jhr_type_2023::Jhr_point
  :super ros::object
  :slots (_X _Y _A ))

(defmethod jhr_type_2023::Jhr_point
  (:init
   (&key
    ((:X __X) 0.0)
    ((:Y __Y) 0.0)
    ((:A __A) 0.0)
    )
   (send-super :init)
   (setq _X (float __X))
   (setq _Y (float __Y))
   (setq _A (float __A))
   self)
  (:X
   (&optional __X)
   (if __X (setq _X __X)) _X)
  (:Y
   (&optional __Y)
   (if __Y (setq _Y __Y)) _Y)
  (:A
   (&optional __A)
   (if __A (setq _A __A)) _A)
  (:serialization-length
   ()
   (+
    ;; float32 _X
    4
    ;; float32 _Y
    4
    ;; float32 _A
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _X
       (sys::poke _X (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _Y
       (sys::poke _Y (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _A
       (sys::poke _A (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _X
     (setq _X (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _Y
     (setq _Y (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _A
     (setq _A (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get jhr_type_2023::Jhr_point :md5sum-) "14206843863907ab243efb1949dfadae")
(setf (get jhr_type_2023::Jhr_point :datatype-) "jhr_type_2023/Jhr_point")
(setf (get jhr_type_2023::Jhr_point :definition-)
      "float32 X
float32 Y
float32 A
")



(provide :jhr_type_2023/Jhr_point "14206843863907ab243efb1949dfadae")


