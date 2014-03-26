/** Duet FL motor controller
 *
 */

#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Bool.h>
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>

#include "etherlab.h"

int main(int argc, char**argv)
{
    ROS_INFO("Hello there?!");
    ros::init(argc, argv, "Duet_FL_motor_controller");
    ros::NodeHandle n;
//    ros::Rate loop_rate(10);
    fm_auto::DuetflEthercatController duetController;
    ROS_INFO("2222222");
    if(!duetController.init())
    {
        ROS_ERROR("init failed");
        return 0;
    }
//    duetController.testGetHomingMethodSDO_SlaveZero();   // <----- tested ok
//    duetController.test_getMotorOperatingModeSDO_SlaveZero();//  <------ tested ok
//    duetController.testOperateHomingMethod_SlaveZero();//  <----- tested ok
//    duetController.test_goToPositionNewSetPoint_SDO_SlaveZero();//  <----- tested ok
//    duetController.test_goToPositionChangeSetImt_SDO_SlaveZero();//  <----- how test?

    if(!duetController.setSlaveZeroMotorOperatingMode2Homing())
    {
        ROS_ERROR("setSlaveZeroMotorOperatingMode2Homing failed");
        return 0;
    }
    else
    {
        ROS_INFO_ONCE("setSlaveZeroMotorOperatingMode2Homing ok\n");
    }
//    duetController.testEnableControllerSDO();
    if(!duetController.enableControlSDO_SlaveZero())
    {
        ROS_ERROR("enableControlSDO_SlaveZero failed");
        return 0;
    }
    else
    {
        ROS_INFO_ONCE("enableControlSDO_SlaveZero ok\n");
    }
    if(!duetController.operateSteeringMotorHomingMethod())
    {
        ROS_ERROR("operateSteeringMotorHomingMethod failed");
        return 0;
    }
    else
    {
        ROS_INFO_ONCE("operateSteeringMotorHomingMethod ok\n");
    }
    if(!duetController.disableControlSDO_SlaveZero())
    {
        ROS_ERROR("disableControlSDO_SlaveZero failed");
        return 0;
    }
    else
    {
        ROS_INFO_ONCE("disableControlSDO_SlaveZero ok\n");
    }
    //
    if(!duetController.setSlaveZeroMotorOperatingMode2ProfileVelocity())
    {
        ROS_ERROR("setSlaveZeroMotorOperatingMode2ProfileVelocity failed");
        return 0;
    }
    else
    {
        ROS_INFO_ONCE("setSlaveZeroMotorOperatingMode2ProfileVelocity ok\n");
    }
    if(!duetController.enableControlSDO_SlaveZero())
    {
        ROS_ERROR("enableControlSDO_SlaveZero failed");
        return 0;
    }
    else
    {
        ROS_INFO_ONCE("enableControlSDO_SlaveZero ok\n");
    }
    duetController.run();
    return 0;
}
