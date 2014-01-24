FILE(REMOVE_RECURSE
  "../msg_gen"
  "../srv_gen"
  "../msg_gen"
  "../srv_gen"
  "../src/ethercat_hardware/msg"
  "../src/ethercat_hardware/srv"
  "CMakeFiles/ROSBUILD_genmsg_cpp"
  "../msg_gen/cpp/include/ethercat_hardware/MotorTrace.h"
  "../msg_gen/cpp/include/ethercat_hardware/ActuatorInfo.h"
  "../msg_gen/cpp/include/ethercat_hardware/MotorTemperature.h"
  "../msg_gen/cpp/include/ethercat_hardware/BoardInfo.h"
  "../msg_gen/cpp/include/ethercat_hardware/RawFTData.h"
  "../msg_gen/cpp/include/ethercat_hardware/RawFTDataSample.h"
  "../msg_gen/cpp/include/ethercat_hardware/MotorTraceSample.h"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_genmsg_cpp.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
