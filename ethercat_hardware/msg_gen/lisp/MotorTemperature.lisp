; Auto-generated. Do not edit!


(cl:in-package ethercat_hardware-msg)


;//! \htmlinclude MotorTemperature.msg.html

(cl:defclass <MotorTemperature> (roslisp-msg-protocol:ros-message)
  ((stamp
    :reader stamp
    :initarg :stamp
    :type cl:real
    :initform 0)
   (winding_temperature
    :reader winding_temperature
    :initarg :winding_temperature
    :type cl:float
    :initform 0.0)
   (housing_temperature
    :reader housing_temperature
    :initarg :housing_temperature
    :type cl:float
    :initform 0.0)
   (ambient_temperature
    :reader ambient_temperature
    :initarg :ambient_temperature
    :type cl:float
    :initform 0.0)
   (heating_power
    :reader heating_power
    :initarg :heating_power
    :type cl:float
    :initform 0.0))
)

(cl:defclass MotorTemperature (<MotorTemperature>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <MotorTemperature>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'MotorTemperature)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name ethercat_hardware-msg:<MotorTemperature> is deprecated: use ethercat_hardware-msg:MotorTemperature instead.")))

(cl:ensure-generic-function 'stamp-val :lambda-list '(m))
(cl:defmethod stamp-val ((m <MotorTemperature>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ethercat_hardware-msg:stamp-val is deprecated.  Use ethercat_hardware-msg:stamp instead.")
  (stamp m))

(cl:ensure-generic-function 'winding_temperature-val :lambda-list '(m))
(cl:defmethod winding_temperature-val ((m <MotorTemperature>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ethercat_hardware-msg:winding_temperature-val is deprecated.  Use ethercat_hardware-msg:winding_temperature instead.")
  (winding_temperature m))

(cl:ensure-generic-function 'housing_temperature-val :lambda-list '(m))
(cl:defmethod housing_temperature-val ((m <MotorTemperature>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ethercat_hardware-msg:housing_temperature-val is deprecated.  Use ethercat_hardware-msg:housing_temperature instead.")
  (housing_temperature m))

(cl:ensure-generic-function 'ambient_temperature-val :lambda-list '(m))
(cl:defmethod ambient_temperature-val ((m <MotorTemperature>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ethercat_hardware-msg:ambient_temperature-val is deprecated.  Use ethercat_hardware-msg:ambient_temperature instead.")
  (ambient_temperature m))

(cl:ensure-generic-function 'heating_power-val :lambda-list '(m))
(cl:defmethod heating_power-val ((m <MotorTemperature>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ethercat_hardware-msg:heating_power-val is deprecated.  Use ethercat_hardware-msg:heating_power instead.")
  (heating_power m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <MotorTemperature>) ostream)
  "Serializes a message object of type '<MotorTemperature>"
  (cl:let ((__sec (cl:floor (cl:slot-value msg 'stamp)))
        (__nsec (cl:round (cl:* 1e9 (cl:- (cl:slot-value msg 'stamp) (cl:floor (cl:slot-value msg 'stamp)))))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 0) __nsec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __nsec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __nsec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __nsec) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'winding_temperature))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'housing_temperature))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'ambient_temperature))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'heating_power))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <MotorTemperature>) istream)
  "Deserializes a message object of type '<MotorTemperature>"
    (cl:let ((__sec 0) (__nsec 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 0) __nsec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __nsec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __nsec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __nsec) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'stamp) (cl:+ (cl:coerce __sec 'cl:double-float) (cl:/ __nsec 1e9))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'winding_temperature) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'housing_temperature) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'ambient_temperature) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'heating_power) (roslisp-utils:decode-double-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<MotorTemperature>)))
  "Returns string type for a message object of type '<MotorTemperature>"
  "ethercat_hardware/MotorTemperature")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'MotorTemperature)))
  "Returns string type for a message object of type 'MotorTemperature"
  "ethercat_hardware/MotorTemperature")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<MotorTemperature>)))
  "Returns md5sum for a message object of type '<MotorTemperature>"
  "d8c7239cd096d6f25b75bff6b63f2162")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'MotorTemperature)))
  "Returns md5sum for a message object of type 'MotorTemperature"
  "d8c7239cd096d6f25b75bff6b63f2162")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<MotorTemperature>)))
  "Returns full string definition for message of type '<MotorTemperature>"
  (cl:format cl:nil "# Sample of motor heating information~%time    stamp~%float64 winding_temperature~%float64 housing_temperature~%float64 ambient_temperature~%float64 heating_power~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'MotorTemperature)))
  "Returns full string definition for message of type 'MotorTemperature"
  (cl:format cl:nil "# Sample of motor heating information~%time    stamp~%float64 winding_temperature~%float64 housing_temperature~%float64 ambient_temperature~%float64 heating_power~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <MotorTemperature>))
  (cl:+ 0
     8
     8
     8
     8
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <MotorTemperature>))
  "Converts a ROS message object to a list"
  (cl:list 'MotorTemperature
    (cl:cons ':stamp (stamp msg))
    (cl:cons ':winding_temperature (winding_temperature msg))
    (cl:cons ':housing_temperature (housing_temperature msg))
    (cl:cons ':ambient_temperature (ambient_temperature msg))
    (cl:cons ':heating_power (heating_power msg))
))
