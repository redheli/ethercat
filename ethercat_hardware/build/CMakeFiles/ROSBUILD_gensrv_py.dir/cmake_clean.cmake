FILE(REMOVE_RECURSE
  "../msg_gen"
  "../srv_gen"
  "../msg_gen"
  "../srv_gen"
  "../src/ethercat_hardware/msg"
  "../src/ethercat_hardware/srv"
  "CMakeFiles/ROSBUILD_gensrv_py"
  "../src/ethercat_hardware/srv/__init__.py"
  "../src/ethercat_hardware/srv/_SoftProcessorReset.py"
  "../src/ethercat_hardware/srv/_SoftProcessorFirmwareWrite.py"
  "../src/ethercat_hardware/srv/_SoftProcessorFirmwareRead.py"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_gensrv_py.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
