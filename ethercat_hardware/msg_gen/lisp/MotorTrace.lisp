; Auto-generated. Do not edit!


(cl:in-package ethercat_hardware-msg)


;//! \htmlinclude MotorTrace.msg.html

(cl:defclass <MotorTrace> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (reason
    :reader reason
    :initarg :reason
    :type cl:string
    :initform "")
   (board_info
    :reader board_info
    :initarg :board_info
    :type ethercat_hardware-msg:BoardInfo
    :initform (cl:make-instance 'ethercat_hardware-msg:BoardInfo))
   (actuator_info
    :reader actuator_info
    :initarg :actuator_info
    :type ethercat_hardware-msg:ActuatorInfo
    :initform (cl:make-instance 'ethercat_hardware-msg:ActuatorInfo))
   (samples
    :reader samples
    :initarg :samples
    :type (cl:vector ethercat_hardware-msg:MotorTraceSample)
   :initform (cl:make-array 0 :element-type 'ethercat_hardware-msg:MotorTraceSample :initial-element (cl:make-instance 'ethercat_hardware-msg:MotorTraceSample))))
)

(cl:defclass MotorTrace (<MotorTrace>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <MotorTrace>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'MotorTrace)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name ethercat_hardware-msg:<MotorTrace> is deprecated: use ethercat_hardware-msg:MotorTrace instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <MotorTrace>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ethercat_hardware-msg:header-val is deprecated.  Use ethercat_hardware-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'reason-val :lambda-list '(m))
(cl:defmethod reason-val ((m <MotorTrace>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ethercat_hardware-msg:reason-val is deprecated.  Use ethercat_hardware-msg:reason instead.")
  (reason m))

(cl:ensure-generic-function 'board_info-val :lambda-list '(m))
(cl:defmethod board_info-val ((m <MotorTrace>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ethercat_hardware-msg:board_info-val is deprecated.  Use ethercat_hardware-msg:board_info instead.")
  (board_info m))

(cl:ensure-generic-function 'actuator_info-val :lambda-list '(m))
(cl:defmethod actuator_info-val ((m <MotorTrace>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ethercat_hardware-msg:actuator_info-val is deprecated.  Use ethercat_hardware-msg:actuator_info instead.")
  (actuator_info m))

(cl:ensure-generic-function 'samples-val :lambda-list '(m))
(cl:defmethod samples-val ((m <MotorTrace>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ethercat_hardware-msg:samples-val is deprecated.  Use ethercat_hardware-msg:samples instead.")
  (samples m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <MotorTrace>) ostream)
  "Serializes a message object of type '<MotorTrace>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'reason))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'reason))
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'board_info) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'actuator_info) ostream)
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'samples))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'samples))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <MotorTrace>) istream)
  "Deserializes a message object of type '<MotorTrace>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'reason) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'reason) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'board_info) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'actuator_info) istream)
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'samples) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'samples)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'ethercat_hardware-msg:MotorTraceSample))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<MotorTrace>)))
  "Returns string type for a message object of type '<MotorTrace>"
  "ethercat_hardware/MotorTrace")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'MotorTrace)))
  "Returns string type for a message object of type 'MotorTrace"
  "ethercat_hardware/MotorTrace")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<MotorTrace>)))
  "Returns md5sum for a message object of type '<MotorTrace>"
  "ada0b8b7f00967d292bd5bb4f59d4bd8")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'MotorTrace)))
  "Returns md5sum for a message object of type 'MotorTrace"
  "ada0b8b7f00967d292bd5bb4f59d4bd8")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<MotorTrace>)))
  "Returns full string definition for message of type '<MotorTrace>"
  (cl:format cl:nil "Header header~%string reason~%ethercat_hardware/BoardInfo board_info~%ethercat_hardware/ActuatorInfo actuator_info~%ethercat_hardware/MotorTraceSample[] samples~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.secs: seconds (stamp_secs) since epoch~%# * stamp.nsecs: nanoseconds since stamp_secs~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: ethercat_hardware/BoardInfo~%string description~%uint32 product_code~%uint32 pcb~%uint32 pca~%uint32 serial~%uint32 firmware_major~%uint32 firmware_minor~%float64 board_resistance~%float64 max_pwm_ratio~%float64 hw_max_current~%bool poor_measured_motor_voltage~%================================================================================~%MSG: ethercat_hardware/ActuatorInfo~%uint32 id~%string name~%string robot_name~%string motor_make~%string motor_model~%float64 max_current~%float64 speed_constant~%float64 motor_resistance~%float64 motor_torque_constant~%float64 encoder_reduction~%float64 pulses_per_revolution~%================================================================================~%MSG: ethercat_hardware/MotorTraceSample~%float64 timestamp~%bool    enabled~%float64 supply_voltage~%float64 measured_motor_voltage~%float64 programmed_pwm~%float64 executed_current~%float64 measured_current~%float64 velocity~%float64 encoder_position~%uint32  encoder_error_count~%float64 motor_voltage_error_limit~%float64 filtered_motor_voltage_error~%float64 filtered_abs_motor_voltage_error~%float64 filtered_measured_voltage_error~%float64 filtered_abs_measured_voltage_error~%float64 filtered_current_error~%float64 filtered_abs_current_error~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'MotorTrace)))
  "Returns full string definition for message of type 'MotorTrace"
  (cl:format cl:nil "Header header~%string reason~%ethercat_hardware/BoardInfo board_info~%ethercat_hardware/ActuatorInfo actuator_info~%ethercat_hardware/MotorTraceSample[] samples~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.secs: seconds (stamp_secs) since epoch~%# * stamp.nsecs: nanoseconds since stamp_secs~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: ethercat_hardware/BoardInfo~%string description~%uint32 product_code~%uint32 pcb~%uint32 pca~%uint32 serial~%uint32 firmware_major~%uint32 firmware_minor~%float64 board_resistance~%float64 max_pwm_ratio~%float64 hw_max_current~%bool poor_measured_motor_voltage~%================================================================================~%MSG: ethercat_hardware/ActuatorInfo~%uint32 id~%string name~%string robot_name~%string motor_make~%string motor_model~%float64 max_current~%float64 speed_constant~%float64 motor_resistance~%float64 motor_torque_constant~%float64 encoder_reduction~%float64 pulses_per_revolution~%================================================================================~%MSG: ethercat_hardware/MotorTraceSample~%float64 timestamp~%bool    enabled~%float64 supply_voltage~%float64 measured_motor_voltage~%float64 programmed_pwm~%float64 executed_current~%float64 measured_current~%float64 velocity~%float64 encoder_position~%uint32  encoder_error_count~%float64 motor_voltage_error_limit~%float64 filtered_motor_voltage_error~%float64 filtered_abs_motor_voltage_error~%float64 filtered_measured_voltage_error~%float64 filtered_abs_measured_voltage_error~%float64 filtered_current_error~%float64 filtered_abs_current_error~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <MotorTrace>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     4 (cl:length (cl:slot-value msg 'reason))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'board_info))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'actuator_info))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'samples) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <MotorTrace>))
  "Converts a ROS message object to a list"
  (cl:list 'MotorTrace
    (cl:cons ':header (header msg))
    (cl:cons ':reason (reason msg))
    (cl:cons ':board_info (board_info msg))
    (cl:cons ':actuator_info (actuator_info msg))
    (cl:cons ':samples (samples msg))
))
