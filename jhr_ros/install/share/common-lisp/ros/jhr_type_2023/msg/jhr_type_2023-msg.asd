
(cl:in-package :asdf)

(defsystem "jhr_type_2023-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :std_msgs-msg
)
  :components ((:file "_package")
    (:file "Jhr_point" :depends-on ("_package_Jhr_point"))
    (:file "_package_Jhr_point" :depends-on ("_package"))
    (:file "Jhr_points" :depends-on ("_package_Jhr_points"))
    (:file "_package_Jhr_points" :depends-on ("_package"))
    (:file "Jhr_pose" :depends-on ("_package_Jhr_pose"))
    (:file "_package_Jhr_pose" :depends-on ("_package"))
  ))