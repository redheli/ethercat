; Auto-generated. Do not edit!


(cl:in-package ethercat_hardware-msg)


;//! \htmlinclude BoardInfo.msg.html

(cl:defclass <BoardInfo> (roslisp-msg-protocol:ros-message)
  ((description
    :reader description
    :initarg :description
    :type cl:string
    :initform "")
   (product_code
    :reader product_code
    :initarg :product_code
    :type cl:integer
    :initform 0)
   (pcb
    :reader pcb
    :initarg :pcb
    :type cl:integer
    :initform 0)
   (pca
    :reader pca
    :initarg :pca
    :type cl:integer
    :initform 0)
   (serial
    :reader serial
    :initarg :serial
    :type cl:integer
    :initform 0)
   (firmware_major
    :reader firmware_major
    :initarg :firmware_major
    :type cl:integer
    :initform 0)
   (firmware_minor
    :reader firmware_minor
    :initarg :firmware_minor
    :type cl:integer
    :initform 0)
   (board_resistance
    :reader board_resistance
    :initarg :board_resistance
    :type cl:float
    :initform 0.0)
   (max_pwm_ratio
    :reader max_pwm_ratio
    :initarg :max_pwm_ratio
    :type cl:float
    :initform 0.0)
   (hw_max_current
    :reader hw_max_current
    :initarg :hw_max_current
    :type cl:float
    :initform 0.0)
   (poor_measured_motor_voltage
    :reader poor_measured_motor_voltage
    :initarg :poor_measured_motor_voltage
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass BoardInfo (<BoardInfo>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <BoardInfo>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'BoardInfo)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name ethercat_hardware-msg:<BoardInfo> is deprecated: use ethercat_hardware-msg:BoardInfo instead.")))

(cl:ensure-generic-function 'description-val :lambda-list '(m))
(cl:defmethod description-val ((m <BoardInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ethercat_hardware-msg:description-val is deprecated.  Use ethercat_hardware-msg:description instead.")
  (description m))

(cl:ensure-generic-function 'product_code-val :lambda-list '(m))
(cl:defmethod product_code-val ((m <BoardInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ethercat_hardware-msg:product_code-val is deprecated.  Use ethercat_hardware-msg:product_code instead.")
  (product_code m))

(cl:ensure-generic-function 'pcb-val :lambda-list '(m))
(cl:defmethod pcb-val ((m <BoardInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ethercat_hardware-msg:pcb-val is deprecated.  Use ethercat_hardware-msg:pcb instead.")
  (pcb m))

(cl:ensure-generic-function 'pca-val :lambda-list '(m))
(cl:defmethod pca-val ((m <BoardInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ethercat_hardware-msg:pca-val is deprecated.  Use ethercat_hardware-msg:pca instead.")
  (pca m))

(cl:ensure-generic-function 'serial-val :lambda-list '(m))
(cl:defmethod serial-val ((m <BoardInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ethercat_hardware-msg:serial-val is deprecated.  Use ethercat_hardware-msg:serial instead.")
  (serial m))

(cl:ensure-generic-function 'firmware_major-val :lambda-list '(m))
(cl:defmethod firmware_major-val ((m <BoardInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ethercat_hardware-msg:firmware_major-val is deprecated.  Use ethercat_hardware-msg:firmware_major instead.")
  (firmware_major m))

(cl:ensure-generic-function 'firmware_minor-val :lambda-list '(m))
(cl:defmethod firmware_minor-val ((m <BoardInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ethercat_hardware-msg:firmware_minor-val is deprecated.  Use ethercat_hardware-msg:firmware_minor instead.")
  (firmware_minor m))

(cl:ensure-generic-function 'board_resistance-val :lambda-list '(m))
(cl:defmethod board_resistance-val ((m <BoardInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ethercat_hardware-msg:board_resistance-val is deprecated.  Use ethercat_hardware-msg:board_resistance instead.")
  (board_resistance m))

(cl:ensure-generic-function 'max_pwm_ratio-val :lambda-list '(m))
(cl:defmethod max_pwm_ratio-val ((m <BoardInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ethercat_hardware-msg:max_pwm_ratio-val is deprecated.  Use ethercat_hardware-msg:max_pwm_ratio instead.")
  (max_pwm_ratio m))

(cl:ensure-generic-function 'hw_max_current-val :lambda-list '(m))
(cl:defmethod hw_max_current-val ((m <BoardInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ethercat_hardware-msg:hw_max_current-val is deprecated.  Use ethercat_hardware-msg:hw_max_current instead.")
  (hw_max_current m))

(cl:ensure-generic-function 'poor_measured_motor_voltage-val :lambda-list '(m))
(cl:defmethod poor_measured_motor_voltage-val ((m <BoardInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ethercat_hardware-msg:poor_measured_motor_voltage-val is deprecated.  Use ethercat_hardware-msg:poor_measured_motor_voltage instead.")
  (poor_measured_motor_voltage m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <BoardInfo>) ostream)
  "Serializes a message object of type '<BoardInfo>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'description))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'description))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'product_code)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'product_code)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'product_code)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'product_code)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'pcb)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'pcb)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'pcb)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'pcb)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'pca)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'pca)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'pca)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'pca)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'serial)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'serial)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'serial)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'serial)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'firmware_major)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'firmware_major)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'firmware_major)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'firmware_major)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'firmware_minor)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'firmware_minor)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'firmware_minor)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'firmware_minor)) ostream)
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'board_resistance))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'max_pwm_ratio))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'hw_max_current))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'poor_measured_motor_voltage) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <BoardInfo>) istream)
  "Deserializes a message object of type '<BoardInfo>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'description) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'description) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'product_code)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'product_code)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'product_code)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'product_code)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'pcb)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'pcb)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'pcb)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'pcb)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'pca)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'pca)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'pca)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'pca)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'serial)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'serial)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'serial)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'serial)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'firmware_major)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'firmware_major)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'firmware_major)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'firmware_major)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'firmware_minor)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'firmware_minor)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'firmware_minor)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'firmware_minor)) (cl:read-byte istream))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'board_resistance) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'max_pwm_ratio) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'hw_max_current) (roslisp-utils:decode-double-float-bits bits)))
    (cl:setf (cl:slot-value msg 'poor_measured_motor_voltage) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<BoardInfo>)))
  "Returns string type for a message object of type '<BoardInfo>"
  "ethercat_hardware/BoardInfo")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'BoardInfo)))
  "Returns string type for a message object of type 'BoardInfo"
  "ethercat_hardware/BoardInfo")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<BoardInfo>)))
  "Returns md5sum for a message object of type '<BoardInfo>"
  "ffcb87ef2725c5fab7d0d8fcd4c7e7bc")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'BoardInfo)))
  "Returns md5sum for a message object of type 'BoardInfo"
  "ffcb87ef2725c5fab7d0d8fcd4c7e7bc")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<BoardInfo>)))
  "Returns full string definition for message of type '<BoardInfo>"
  (cl:format cl:nil "string description~%uint32 product_code~%uint32 pcb~%uint32 pca~%uint32 serial~%uint32 firmware_major~%uint32 firmware_minor~%float64 board_resistance~%float64 max_pwm_ratio~%float64 hw_max_current~%bool poor_measured_motor_voltage~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'BoardInfo)))
  "Returns full string definition for message of type 'BoardInfo"
  (cl:format cl:nil "string description~%uint32 product_code~%uint32 pcb~%uint32 pca~%uint32 serial~%uint32 firmware_major~%uint32 firmware_minor~%float64 board_resistance~%float64 max_pwm_ratio~%float64 hw_max_current~%bool poor_measured_motor_voltage~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <BoardInfo>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'description))
     4
     4
     4
     4
     4
     4
     8
     8
     8
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <BoardInfo>))
  "Converts a ROS message object to a list"
  (cl:list 'BoardInfo
    (cl:cons ':description (description msg))
    (cl:cons ':product_code (product_code msg))
    (cl:cons ':pcb (pcb msg))
    (cl:cons ':pca (pca msg))
    (cl:cons ':serial (serial msg))
    (cl:cons ':firmware_major (firmware_major msg))
    (cl:cons ':firmware_minor (firmware_minor msg))
    (cl:cons ':board_resistance (board_resistance msg))
    (cl:cons ':max_pwm_ratio (max_pwm_ratio msg))
    (cl:cons ':hw_max_current (hw_max_current msg))
    (cl:cons ':poor_measured_motor_voltage (poor_measured_motor_voltage msg))
))
