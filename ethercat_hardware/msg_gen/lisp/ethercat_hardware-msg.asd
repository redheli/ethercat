
(cl:in-package :asdf)

(defsystem "ethercat_hardware-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :std_msgs-msg
)
  :components ((:file "_package")
    (:file "MotorTraceSample" :depends-on ("_package_MotorTraceSample"))
    (:file "_package_MotorTraceSample" :depends-on ("_package"))
    (:file "MotorTemperature" :depends-on ("_package_MotorTemperature"))
    (:file "_package_MotorTemperature" :depends-on ("_package"))
    (:file "BoardInfo" :depends-on ("_package_BoardInfo"))
    (:file "_package_BoardInfo" :depends-on ("_package"))
    (:file "RawFTDataSample" :depends-on ("_package_RawFTDataSample"))
    (:file "_package_RawFTDataSample" :depends-on ("_package"))
    (:file "MotorTrace" :depends-on ("_package_MotorTrace"))
    (:file "_package_MotorTrace" :depends-on ("_package"))
    (:file "ActuatorInfo" :depends-on ("_package_ActuatorInfo"))
    (:file "_package_ActuatorInfo" :depends-on ("_package"))
    (:file "RawFTData" :depends-on ("_package_RawFTData"))
    (:file "_package_RawFTData" :depends-on ("_package"))
  ))