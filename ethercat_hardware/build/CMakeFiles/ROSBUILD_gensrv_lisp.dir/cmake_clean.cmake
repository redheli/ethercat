FILE(REMOVE_RECURSE
  "../msg_gen"
  "../srv_gen"
  "../msg_gen"
  "../srv_gen"
  "../src/ethercat_hardware/msg"
  "../src/ethercat_hardware/srv"
  "CMakeFiles/ROSBUILD_gensrv_lisp"
  "../srv_gen/lisp/SoftProcessorReset.lisp"
  "../srv_gen/lisp/_package.lisp"
  "../srv_gen/lisp/_package_SoftProcessorReset.lisp"
  "../srv_gen/lisp/SoftProcessorFirmwareWrite.lisp"
  "../srv_gen/lisp/_package.lisp"
  "../srv_gen/lisp/_package_SoftProcessorFirmwareWrite.lisp"
  "../srv_gen/lisp/SoftProcessorFirmwareRead.lisp"
  "../srv_gen/lisp/_package.lisp"
  "../srv_gen/lisp/_package_SoftProcessorFirmwareRead.lisp"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_gensrv_lisp.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
