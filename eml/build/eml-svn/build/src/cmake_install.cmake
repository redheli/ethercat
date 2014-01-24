# Install script for directory: /home/turtlebot/ros_workspace/ethercat/eml/build/eml-svn/src

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/home/turtlebot/ros_workspace/ethercat/eml/eml")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "1")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/ethercat" TYPE FILE FILES
    "/home/turtlebot/ros_workspace/ethercat/eml/build/eml-svn/include/ethercat/arch-RTnet/ethercat/ethercat_defs.h"
    "/home/turtlebot/ros_workspace/ethercat/eml/build/eml-svn/include/ethercat/arch-RTnet/ethercat/ethercat_log.h"
    "/home/turtlebot/ros_workspace/ethercat/eml/build/eml-svn/include/ethercat/arch-RTnet/ethercat/netif.h"
    "/home/turtlebot/ros_workspace/ethercat/eml/build/eml-svn/include/ethercat/arch-RTnet/ethercat/ethercat_xenomai_drv.h"
    "/home/turtlebot/ros_workspace/ethercat/eml/build/eml-svn/include/ethercat/arch-RTnet/ethercat/ethercat_datastruct.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/al" TYPE FILE FILES
    "/home/turtlebot/ros_workspace/ethercat/eml/build/eml-svn/include/al/ethercat_FSM.h"
    "/home/turtlebot/ros_workspace/ethercat/eml/build/eml-svn/include/al/ethercat_AL.h"
    "/home/turtlebot/ros_workspace/ethercat/eml/build/eml-svn/include/al/ethercat_master.h"
    "/home/turtlebot/ros_workspace/ethercat/eml/build/eml-svn/include/al/ethercat_router.h"
    "/home/turtlebot/ros_workspace/ethercat/eml/build/eml-svn/include/al/ethercat_mbx.h"
    "/home/turtlebot/ros_workspace/ethercat/eml/build/eml-svn/include/al/ethercat_slave_conf.h"
    "/home/turtlebot/ros_workspace/ethercat/eml/build/eml-svn/include/al/ethercat_process_data.h"
    "/home/turtlebot/ros_workspace/ethercat/eml/build/eml-svn/include/al/ethercat_slave_handler.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/dll" TYPE FILE FILES
    "/home/turtlebot/ros_workspace/ethercat/eml/build/eml-svn/include/dll/ethercat_device_addressed_telegram.h"
    "/home/turtlebot/ros_workspace/ethercat/eml/build/eml-svn/include/dll/ethercat_frame.h"
    "/home/turtlebot/ros_workspace/ethercat/eml/build/eml-svn/include/dll/ethercat_telegram.h"
    "/home/turtlebot/ros_workspace/ethercat/eml/build/eml-svn/include/dll/ethercat_dll.h"
    "/home/turtlebot/ros_workspace/ethercat/eml/build/eml-svn/include/dll/ethercat_logical_addressed_telegram.h"
    "/home/turtlebot/ros_workspace/ethercat/eml/build/eml-svn/include/dll/ethercat_slave_memory.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libeml.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libeml.so")
    FILE(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libeml.so"
         RPATH "")
  ENDIF()
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/turtlebot/ros_workspace/ethercat/eml/build/eml-svn/build/src/libeml.so")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libeml.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libeml.so")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libeml.so")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

