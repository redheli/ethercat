cmake_minimum_required(VERSION 2.4.6)
include($ENV{ROS_ROOT}/core/rosbuild/rosbuild.cmake)

# Set the build type.  Options are:
#  Coverage       : w/ debug symbols, w/o optimization, w/ code-coverage
#  Debug          : w/ debug symbols, w/o optimization
#  Release        : w/o debug symbols, w/ optimization
#  RelWithDebInfo : w/ debug symbols, w/ optimization
#  MinSizeRel     : w/o debug symbols, w/ optimization, stripped binaries
#set(ROS_BUILD_TYPE RelWithDebInfo)

rosbuild_init()

#set the default path for built executables to the "bin" directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#set the default path for built libraries to the "lib" directory
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

#uncomment if you have defined messages
rosbuild_genmsg()
#uncomment if you have defined services
#rosbuild_gensrv()

set(ETHERLAB /opt/etherlab/)
link_directories(${ETHERLAB}/lib/)
include_directories(${ETHERLAB}/include)
# /usr/src/linux-headers-3.2.0-53-generic/include
#    /usr/src/linux-headers-3.2.0-53-generic/arch/x86/include)
#include_directories(/usr/src/linux-headers-3.2.0-53-generic/include/linux)
rosbuild_add_executable(etherlab_master src/etherlab_master.cpp)
rosbuild_add_executable(etherlab_master_sdo src/etherlab_master_sdo.cpp)
target_link_libraries(etherlab_master ethercat)
target_link_libraries(etherlab_master_sdo ethercat)

rosbuild_add_executable(etherlab_master2 src/etherlab_master2.cpp)
target_link_libraries(etherlab_master2 ethercat)

rosbuild_add_executable(coe_example src/coe_example.c)
target_link_libraries(coe_example ethercat)

rosbuild_add_executable(DuetflController src/main.cpp
                                            src/ObjectDictionay.h
                                         src/etherlab.cpp src/etherlab.h)

target_link_libraries(DuetflController ethercat)

#rosbuild_add_executable(etherlab_example_main src/etherlab_example_main.c)
#target_link_libraries(etherlab_example_main ethercat)

#common commands for building c++ executables and libraries
#rosbuild_add_library(${PROJECT_NAME} src/example.cpp)
#target_link_libraries(${PROJECT_NAME} another_library)
#rosbuild_add_boost_directories()
#rosbuild_link_boost(${PROJECT_NAME} thread)

#target_link_libraries(example ${PROJECT_NAME})
