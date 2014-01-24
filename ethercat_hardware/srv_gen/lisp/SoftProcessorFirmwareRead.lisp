; Auto-generated. Do not edit!


(cl:in-package ethercat_hardware-srv)


;//! \htmlinclude SoftProcessorFirmwareRead-request.msg.html

(cl:defclass <SoftProcessorFirmwareRead-request> (roslisp-msg-protocol:ros-message)
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

(cl:defclass SoftProcessorFirmwareRead-request (<SoftProcessorFirmwareRead-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SoftProcessorFirmwareRead-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SoftProcessorFirmwareRead-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name ethercat_hardware-srv:<SoftProcessorFirmwareRead-request> is deprecated: use ethercat_hardware-srv:SoftProcessorFirmwareRead-request instead.")))

(cl:ensure-generic-function 'actuator_name-val :lambda-list '(m))
(cl:defmethod actuator_name-val ((m <SoftProcessorFirmwareRead-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ethercat_hardware-srv:actuator_name-val is deprecated.  Use ethercat_hardware-srv:actuator_name instead.")
  (actuator_name m))

(cl:ensure-generic-function 'processor_name-val :lambda-list '(m))
(cl:defmethod processor_name-val ((m <SoftProcessorFirmwareRead-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ethercat_hardware-srv:processor_name-val is deprecated.  Use ethercat_hardware-srv:processor_name instead.")
  (processor_name m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SoftProcessorFirmwareRead-request>) ostream)
  "Serializes a message object of type '<SoftProcessorFirmwareRead-request>"
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
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SoftProcessorFirmwareRead-request>) istream)
  "Deserializes a message object of type '<SoftProcessorFirmwareRead-request>"
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
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SoftProcessorFirmwareRead-request>)))
  "Returns string type for a service object of type '<SoftProcessorFirmwareRead-request>"
  "ethercat_hardware/SoftProcessorFirmwareReadRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SoftProcessorFirmwareRead-request)))
  "Returns string type for a service object of type 'SoftProcessorFirmwareRead-request"
  "ethercat_hardware/SoftProcessorFirmwareReadRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SoftProcessorFirmwareRead-request>)))
  "Returns md5sum for a message object of type '<SoftProcessorFirmwareRead-request>"
  "52ad83cdf3a5cf0a74166c7d411fc0aa")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SoftProcessorFirmwareRead-request)))
  "Returns md5sum for a message object of type 'SoftProcessorFirmwareRead-request"
  "52ad83cdf3a5cf0a74166c7d411fc0aa")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SoftProcessorFirmwareRead-request>)))
  "Returns full string definition for message of type '<SoftProcessorFirmwareRead-request>"
  (cl:format cl:nil "string actuator_name~%string processor_name~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SoftProcessorFirmwareRead-request)))
  "Returns full string definition for message of type 'SoftProcessorFirmwareRead-request"
  (cl:format cl:nil "string actuator_name~%string processor_name~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SoftProcessorFirmwareRead-request>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'actuator_name))
     4 (cl:length (cl:slot-value msg 'processor_name))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SoftProcessorFirmwareRead-request>))
  "Converts a ROS message object to a list"
  (cl:list 'SoftProcessorFirmwareRead-request
    (cl:cons ':actuator_name (actuator_name msg))
    (cl:cons ':processor_name (processor_name msg))
))
;//! \htmlinclude SoftProcessorFirmwareRead-response.msg.html

(cl:defclass <SoftProcessorFirmwareRead-response> (roslisp-msg-protocol:ros-message)
  ((success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil)
   (error_msg
    :reader error_msg
    :initarg :error_msg
    :type cl:string
    :initform "")
   (instructions
    :reader instructions
    :initarg :instructions
    :type (cl:vector cl:integer)
   :initform (cl:make-array 0 :element-type 'cl:integer :initial-element 0)))
)

(cl:defclass SoftProcessorFirmwareRead-response (<SoftProcessorFirmwareRead-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SoftProcessorFirmwareRead-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SoftProcessorFirmwareRead-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name ethercat_hardware-srv:<SoftProcessorFirmwareRead-response> is deprecated: use ethercat_hardware-srv:SoftProcessorFirmwareRead-response instead.")))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <SoftProcessorFirmwareRead-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ethercat_hardware-srv:success-val is deprecated.  Use ethercat_hardware-srv:success instead.")
  (success m))

(cl:ensure-generic-function 'error_msg-val :lambda-list '(m))
(cl:defmethod error_msg-val ((m <SoftProcessorFirmwareRead-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ethercat_hardware-srv:error_msg-val is deprecated.  Use ethercat_hardware-srv:error_msg instead.")
  (error_msg m))

(cl:ensure-generic-function 'instructions-val :lambda-list '(m))
(cl:defmethod instructions-val ((m <SoftProcessorFirmwareRead-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ethercat_hardware-srv:instructions-val is deprecated.  Use ethercat_hardware-srv:instructions instead.")
  (instructions m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SoftProcessorFirmwareRead-response>) ostream)
  "Serializes a message object of type '<SoftProcessorFirmwareRead-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'error_msg))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'error_msg))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'instructions))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:write-byte (cl:ldb (cl:byte 8 0) ele) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) ele) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) ele) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) ele) ostream))
   (cl:slot-value msg 'instructions))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SoftProcessorFirmwareRead-response>) istream)
  "Deserializes a message object of type '<SoftProcessorFirmwareRead-response>"
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'error_msg) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'error_msg) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'instructions) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'instructions)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:aref vals i)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:aref vals i)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:aref vals i)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:aref vals i)) (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SoftProcessorFirmwareRead-response>)))
  "Returns string type for a service object of type '<SoftProcessorFirmwareRead-response>"
  "ethercat_hardware/SoftProcessorFirmwareReadResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SoftProcessorFirmwareRead-response)))
  "Returns string type for a service object of type 'SoftProcessorFirmwareRead-response"
  "ethercat_hardware/SoftProcessorFirmwareReadResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SoftProcessorFirmwareRead-response>)))
  "Returns md5sum for a message object of type '<SoftProcessorFirmwareRead-response>"
  "52ad83cdf3a5cf0a74166c7d411fc0aa")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SoftProcessorFirmwareRead-response)))
  "Returns md5sum for a message object of type 'SoftProcessorFirmwareRead-response"
  "52ad83cdf3a5cf0a74166c7d411fc0aa")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SoftProcessorFirmwareRead-response>)))
  "Returns full string definition for message of type '<SoftProcessorFirmwareRead-response>"
  (cl:format cl:nil "bool success~%string error_msg~%uint32[] instructions~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SoftProcessorFirmwareRead-response)))
  "Returns full string definition for message of type 'SoftProcessorFirmwareRead-response"
  (cl:format cl:nil "bool success~%string error_msg~%uint32[] instructions~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SoftProcessorFirmwareRead-response>))
  (cl:+ 0
     1
     4 (cl:length (cl:slot-value msg 'error_msg))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'instructions) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SoftProcessorFirmwareRead-response>))
  "Converts a ROS message object to a list"
  (cl:list 'SoftProcessorFirmwareRead-response
    (cl:cons ':success (success msg))
    (cl:cons ':error_msg (error_msg msg))
    (cl:cons ':instructions (instructions msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'SoftProcessorFirmwareRead)))
  'SoftProcessorFirmwareRead-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'SoftProcessorFirmwareRead)))
  'SoftProcessorFirmwareRead-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SoftProcessorFirmwareRead)))
  "Returns string type for a service object of type '<SoftProcessorFirmwareRead>"
  "ethercat_hardware/SoftProcessorFirmwareRead")