FILE(REMOVE_RECURSE
  "../msg_gen"
  "../srv_gen"
  "../msg_gen"
  "../srv_gen"
  "../src/ethercat_hardware/msg"
  "../src/ethercat_hardware/srv"
  "CMakeFiles/ROSBUILD_genmsg_py"
  "../src/ethercat_hardware/msg/__init__.py"
  "../src/ethercat_hardware/msg/_MotorTrace.py"
  "../src/ethercat_hardware/msg/_ActuatorInfo.py"
  "../src/ethercat_hardware/msg/_MotorTemperature.py"
  "../src/ethercat_hardware/msg/_BoardInfo.py"
  "../src/ethercat_hardware/msg/_RawFTData.py"
  "../src/ethercat_hardware/msg/_RawFTDataSample.py"
  "../src/ethercat_hardware/msg/_MotorTraceSample.py"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_genmsg_py.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
