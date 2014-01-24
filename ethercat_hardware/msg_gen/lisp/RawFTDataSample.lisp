; Auto-generated. Do not edit!


(cl:in-package ethercat_hardware-msg)


;//! \htmlinclude RawFTDataSample.msg.html

(cl:defclass <RawFTDataSample> (roslisp-msg-protocol:ros-message)
  ((sample_count
    :reader sample_count
    :initarg :sample_count
    :type cl:integer
    :initform 0)
   (data
    :reader data
    :initarg :data
    :type (cl:vector cl:fixnum)
   :initform (cl:make-array 0 :element-type 'cl:fixnum :initial-element 0))
   (vhalf
    :reader vhalf
    :initarg :vhalf
    :type cl:fixnum
    :initform 0))
)

(cl:defclass RawFTDataSample (<RawFTDataSample>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <RawFTDataSample>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'RawFTDataSample)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name ethercat_hardware-msg:<RawFTDataSample> is deprecated: use ethercat_hardware-msg:RawFTDataSample instead.")))

(cl:ensure-generic-function 'sample_count-val :lambda-list '(m))
(cl:defmethod sample_count-val ((m <RawFTDataSample>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ethercat_hardware-msg:sample_count-val is deprecated.  Use ethercat_hardware-msg:sample_count instead.")
  (sample_count m))

(cl:ensure-generic-function 'data-val :lambda-list '(m))
(cl:defmethod data-val ((m <RawFTDataSample>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ethercat_hardware-msg:data-val is deprecated.  Use ethercat_hardware-msg:data instead.")
  (data m))

(cl:ensure-generic-function 'vhalf-val :lambda-list '(m))
(cl:defmethod vhalf-val ((m <RawFTDataSample>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ethercat_hardware-msg:vhalf-val is deprecated.  Use ethercat_hardware-msg:vhalf instead.")
  (vhalf m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <RawFTDataSample>) ostream)
  "Serializes a message object of type '<RawFTDataSample>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'sample_count)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'sample_count)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'sample_count)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'sample_count)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 32) (cl:slot-value msg 'sample_count)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 40) (cl:slot-value msg 'sample_count)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 48) (cl:slot-value msg 'sample_count)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 56) (cl:slot-value msg 'sample_count)) ostream)
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'data))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let* ((signed ele) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    ))
   (cl:slot-value msg 'data))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'vhalf)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'vhalf)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <RawFTDataSample>) istream)
  "Deserializes a message object of type '<RawFTDataSample>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'sample_count)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'sample_count)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'sample_count)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'sample_count)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 32) (cl:slot-value msg 'sample_count)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 40) (cl:slot-value msg 'sample_count)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 48) (cl:slot-value msg 'sample_count)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 56) (cl:slot-value msg 'sample_count)) (cl:read-byte istream))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'data) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'data)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:aref vals i) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536)))))))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'vhalf)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'vhalf)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<RawFTDataSample>)))
  "Returns string type for a message object of type '<RawFTDataSample>"
  "ethercat_hardware/RawFTDataSample")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'RawFTDataSample)))
  "Returns string type for a message object of type 'RawFTDataSample"
  "ethercat_hardware/RawFTDataSample")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<RawFTDataSample>)))
  "Returns md5sum for a message object of type '<RawFTDataSample>"
  "6c3b6e352fd24802b2d95b606df80de6")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'RawFTDataSample)))
  "Returns md5sum for a message object of type 'RawFTDataSample"
  "6c3b6e352fd24802b2d95b606df80de6")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<RawFTDataSample>)))
  "Returns full string definition for message of type '<RawFTDataSample>"
  (cl:format cl:nil "# One raw Data sample from WG035 F/T input via WG006 (gripper MCB).~%uint64  sample_count~%int16[] data~%uint16  vhalf~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'RawFTDataSample)))
  "Returns full string definition for message of type 'RawFTDataSample"
  (cl:format cl:nil "# One raw Data sample from WG035 F/T input via WG006 (gripper MCB).~%uint64  sample_count~%int16[] data~%uint16  vhalf~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <RawFTDataSample>))
  (cl:+ 0
     8
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'data) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 2)))
     2
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <RawFTDataSample>))
  "Converts a ROS message object to a list"
  (cl:list 'RawFTDataSample
    (cl:cons ':sample_count (sample_count msg))
    (cl:cons ':data (data msg))
    (cl:cons ':vhalf (vhalf msg))
))
