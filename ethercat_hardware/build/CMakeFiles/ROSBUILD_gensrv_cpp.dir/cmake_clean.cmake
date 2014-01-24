FILE(REMOVE_RECURSE
  "../msg_gen"
  "../srv_gen"
  "../msg_gen"
  "../srv_gen"
  "../src/ethercat_hardware/msg"
  "../src/ethercat_hardware/srv"
  "CMakeFiles/ROSBUILD_gensrv_cpp"
  "../srv_gen/cpp/include/ethercat_hardware/SoftProcessorReset.h"
  "../srv_gen/cpp/include/ethercat_hardware/SoftProcessorFirmwareWrite.h"
  "../srv_gen/cpp/include/ethercat_hardware/SoftProcessorFirmwareRead.h"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_gensrv_cpp.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
