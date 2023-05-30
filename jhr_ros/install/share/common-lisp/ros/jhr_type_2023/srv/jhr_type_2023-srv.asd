
(cl:in-package :asdf)

(defsystem "jhr_type_2023-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "SetRobot" :depends-on ("_package_SetRobot"))
    (:file "_package_SetRobot" :depends-on ("_package"))
  ))