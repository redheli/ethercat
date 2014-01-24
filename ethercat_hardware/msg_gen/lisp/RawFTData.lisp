; Auto-generated. Do not edit!


(cl:in-package ethercat_hardware-msg)


;//! \htmlinclude RawFTData.msg.html

(cl:defclass <RawFTData> (roslisp-msg-protocol:ros-message)
  ((samples
    :reader samples
    :initarg :samples
    :type (cl:vector ethercat_hardware-msg:RawFTDataSample)
   :initform (cl:make-array 0 :element-type 'ethercat_hardware-msg:RawFTDataSample :initial-element (cl:make-instance 'ethercat_hardware-msg:RawFTDataSample)))
   (sample_count
    :reader sample_count
    :initarg :sample_count
    :type cl:integer
    :initform 0)
   (missed_samples
    :reader missed_samples
    :initarg :missed_samples
    :type cl:integer
    :initform 0))
)

(cl:defclass RawFTData (<RawFTData>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <RawFTData>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'RawFTData)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name ethercat_hardware-msg:<RawFTData> is deprecated: use ethercat_hardware-msg:RawFTData instead.")))

(cl:ensure-generic-function 'samples-val :lambda-list '(m))
(cl:defmethod samples-val ((m <RawFTData>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ethercat_hardware-msg:samples-val is deprecated.  Use ethercat_hardware-msg:samples instead.")
  (samples m))

(cl:ensure-generic-function 'sample_count-val :lambda-list '(m))
(cl:defmethod sample_count-val ((m <RawFTData>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ethercat_hardware-msg:sample_count-val is deprecated.  Use ethercat_hardware-msg:sample_count instead.")
  (sample_count m))

(cl:ensure-generic-function 'missed_samples-val :lambda-list '(m))
(cl:defmethod missed_samples-val ((m <RawFTData>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ethercat_hardware-msg:missed_samples-val is deprecated.  Use ethercat_hardware-msg:missed_samples instead.")
  (missed_samples m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <RawFTData>) ostream)
  "Serializes a message object of type '<RawFTData>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'samples))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'samples))
  (cl:let* ((signed (cl:slot-value msg 'sample_count)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 18446744073709551616) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'missed_samples)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 18446744073709551616) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <RawFTData>) istream)
  "Deserializes a message object of type '<RawFTData>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'samples) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'samples)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'ethercat_hardware-msg:RawFTDataSample))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'sample_count) (cl:if (cl:< unsigned 9223372036854775808) unsigned (cl:- unsigned 18446744073709551616))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'missed_samples) (cl:if (cl:< unsigned 9223372036854775808) unsigned (cl:- unsigned 18446744073709551616))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<RawFTData>)))
  "Returns string type for a message object of type '<RawFTData>"
  "ethercat_hardware/RawFTData")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'RawFTData)))
  "Returns string type for a message object of type 'RawFTData"
  "ethercat_hardware/RawFTData")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<RawFTData>)))
  "Returns md5sum for a message object of type '<RawFTData>"
  "85f5ed45095367bfb8fb2e57954c0b89")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'RawFTData)))
  "Returns md5sum for a message object of type 'RawFTData"
  "85f5ed45095367bfb8fb2e57954c0b89")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<RawFTData>)))
  "Returns full string definition for message of type '<RawFTData>"
  (cl:format cl:nil "# Raw Data from WG035 F/T input via WG006 (gripper MCB).~%RawFTDataSample[] samples  # The realtime loop receives upto 4 new samples each 1hKhz cycle ~%int64 sample_count         # Counts number of samples~%int64 missed_samples       # Counts number of samples that were missed~%================================================================================~%MSG: ethercat_hardware/RawFTDataSample~%# One raw Data sample from WG035 F/T input via WG006 (gripper MCB).~%uint64  sample_count~%int16[] data~%uint16  vhalf~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'RawFTData)))
  "Returns full string definition for message of type 'RawFTData"
  (cl:format cl:nil "# Raw Data from WG035 F/T input via WG006 (gripper MCB).~%RawFTDataSample[] samples  # The realtime loop receives upto 4 new samples each 1hKhz cycle ~%int64 sample_count         # Counts number of samples~%int64 missed_samples       # Counts number of samples that were missed~%================================================================================~%MSG: ethercat_hardware/RawFTDataSample~%# One raw Data sample from WG035 F/T input via WG006 (gripper MCB).~%uint64  sample_count~%int16[] data~%uint16  vhalf~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <RawFTData>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'samples) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
     8
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <RawFTData>))
  "Converts a ROS message object to a list"
  (cl:list 'RawFTData
    (cl:cons ':samples (samples msg))
    (cl:cons ':sample_count (sample_count msg))
    (cl:cons ':missed_samples (missed_samples msg))
))
