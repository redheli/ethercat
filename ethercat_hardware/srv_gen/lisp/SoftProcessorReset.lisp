; Auto-generated. Do not edit!


(cl:in-package ethercat_hardware-srv)


;//! \htmlinclude SoftProcessorReset-request.msg.html

(cl:defclass <SoftProcessorReset-request> (roslisp-msg-protocol:ros-message)
  ((actuator_name
    :reader actuator_name
    :initarg :actuator_name
    :type cl:string
    :initform "")
   (processor_name
    :reader processor_name
    :initarg :processor_name
    :type cl:string
    :initform ""))
)

(cl:defclass SoftProcessorReset-request (<SoftProcessorReset-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SoftProcessorReset-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SoftProcessorReset-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name ethercat_hardware-srv:<SoftProcessorReset-request> is deprecated: use ethercat_hardware-srv:SoftProcessorReset-request instead.")))

(cl:ensure-generic-function 'actuator_name-val :lambda-list '(m))
(cl:defmethod actuator_name-val ((m <SoftProcessorReset-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ethercat_hardware-srv:actuator_name-val is deprecated.  Use ethercat_hardware-srv:actuator_name instead.")
  (actuator_name m))

(cl:ensure-generic-function 'processor_name-val :lambda-list '(m))
(cl:defmethod processor_name-val ((m <SoftProcessorReset-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ethercat_hardware-srv:processor_name-val is deprecated.  Use ethercat_hardware-srv:processor_name instead.")
  (processor_name m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SoftProcessorReset-request>) ostream)
  "Serializes a message object of type '<SoftProcessorReset-request>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'actuator_name))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'actuator_name))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'processor_name))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'processor_name))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SoftProcessorReset-request>) istream)
  "Deserializes a message object of type '<SoftProcessorReset-request>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'actuator_name) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'actuator_name) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'processor_name) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'processor_name) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SoftProcessorReset-request>)))
  "Returns string type for a service object of type '<SoftProcessorReset-request>"
  "ethercat_hardware/SoftProcessorResetRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SoftProcessorReset-request)))
  "Returns string type for a service object of type 'SoftProcessorReset-request"
  "ethercat_hardware/SoftProcessorResetRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SoftProcessorReset-request>)))
  "Returns md5sum for a message object of type '<SoftProcessorReset-request>"
  "338c1a9d2fcf7479cddb1ea63dbc8af9")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SoftProcessorReset-request)))
  "Returns md5sum for a message object of type 'SoftProcessorReset-request"
  "338c1a9d2fcf7479cddb1ea63dbc8af9")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SoftProcessorReset-request>)))
  "Returns full string definition for message of type '<SoftProcessorReset-request>"
  (cl:format cl:nil "string actuator_name~%string processor_name~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SoftProcessorReset-request)))
  "Returns full string definition for message of type 'SoftProcessorReset-request"
  (cl:format cl:nil "string actuator_name~%string processor_name~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SoftProcessorReset-request>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'actuator_name))
     4 (cl:length (cl:slot-value msg 'processor_name))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SoftProcessorReset-request>))
  "Converts a ROS message object to a list"
  (cl:list 'SoftProcessorReset-request
    (cl:cons ':actuator_name (actuator_name msg))
    (cl:cons ':processor_name (processor_name msg))
))
;//! \htmlinclude SoftProcessorReset-response.msg.html

(cl:defclass <SoftProcessorReset-response> (roslisp-msg-protocol:ros-message)
  ((success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil)
   (error_msg
    :reader error_msg
    :initarg :error_msg
    :type cl:string
    :initform ""))
)

(cl:defclass SoftProcessorReset-response (<SoftProcessorReset-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SoftProcessorReset-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SoftProcessorReset-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name ethercat_hardware-srv:<SoftProcessorReset-response> is deprecated: use ethercat_hardware-srv:SoftProcessorReset-response instead.")))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <SoftProcessorReset-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ethercat_hardware-srv:success-val is deprecated.  Use ethercat_hardware-srv:success instead.")
  (success m))

(cl:ensure-generic-function 'error_msg-val :lambda-list '(m))
(cl:defmethod error_msg-val ((m <SoftProcessorReset-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ethercat_hardware-srv:error_msg-val is deprecated.  Use ethercat_hardware-srv:error_msg instead.")
  (error_msg m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SoftProcessorReset-response>) ostream)
  "Serializes a message object of type '<SoftProcessorReset-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'error_msg))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'error_msg))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SoftProcessorReset-response>) istream)
  "Deserializes a message object of type '<SoftProcessorReset-response>"
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'error_msg) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'error_msg) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SoftProcessorReset-response>)))
  "Returns string type for a service object of type '<SoftProcessorReset-response>"
  "ethercat_hardware/SoftProcessorResetResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SoftProcessorReset-response)))
  "Returns string type for a service object of type 'SoftProcessorReset-response"
  "ethercat_hardware/SoftProcessorResetResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SoftProcessorReset-response>)))
  "Returns md5sum for a message object of type '<SoftProcessorReset-response>"
  "338c1a9d2fcf7479cddb1ea63dbc8af9")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SoftProcessorReset-response)))
  "Returns md5sum for a message object of type 'SoftProcessorReset-response"
  "338c1a9d2fcf7479cddb1ea63dbc8af9")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SoftProcessorReset-response>)))
  "Returns full string definition for message of type '<SoftProcessorReset-response>"
  (cl:format cl:nil "bool success~%string error_msg~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SoftProcessorReset-response)))
  "Returns full string definition for message of type 'SoftProcessorReset-response"
  (cl:format cl:nil "bool success~%string error_msg~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SoftProcessorReset-response>))
  (cl:+ 0
     1
     4 (cl:length (cl:slot-value msg 'error_msg))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SoftProcessorReset-response>))
  "Converts a ROS message object to a list"
  (cl:list 'SoftProcessorReset-response
    (cl:cons ':success (success msg))
    (cl:cons ':error_msg (error_msg msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'SoftProcessorReset)))
  'SoftProcessorReset-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'SoftProcessorReset)))
  'SoftProcessorReset-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SoftProcessorReset)))
  "Returns string type for a service object of type '<SoftProcessorReset>"
  "ethercat_hardware/SoftProcessorReset")