
(cl:in-package :asdf)

(defsystem "ethercat_hardware-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "SoftProcessorFirmwareWrite" :depends-on ("_package_SoftProcessorFirmwareWrite"))
    (:file "_package_SoftProcessorFirmwareWrite" :depends-on ("_package"))
    (:file "SoftProcessorReset" :depends-on ("_package_SoftProcessorReset"))
    (:file "_package_SoftProcessorReset" :depends-on ("_package"))
    (:file "SoftProcessorFirmwareRead" :depends-on ("_package_SoftProcessorFirmwareRead"))
    (:file "_package_SoftProcessorFirmwareRead" :depends-on ("_package"))
  ))