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

    if(duetController.needDoHoming_SlaveZero)
    {
        if(!duetController.doHoming_SlaveZero())
        {
            ROS_ERROR("doHoming_SlaveZero failed");
            return 0;
        }
    }// if need homing slave zero
    if(duetController.hasSlaveOne && duetController.needDoHoming_SlaveOne)
    {
        if(!duetController.doHoming_SlaveOne())
        {
            ROS_ERROR("doHoming_SlaveOne failed");
            return 0;
        }
    }// if need homing slave zero

    // profile velocity mode is mandatory
    if(!duetController.setSlaveZeroMotorOperatingMode2ProfileVelocity())
    {
        ROS_ERROR("setSlaveZeroMotorOperatingMode2ProfileVelocity failed");
        return 0;
    }
    else
    {
        ROS_INFO_ONCE("setSlaveZeroMotorOperatingMode2ProfileVelocity ok\n");
    }
    if(duetController.hasSlaveOne)
    {
        if(!duetController.setSlaveOneMotorOperatingMode2ProfileVelocity())
        {
            ROS_ERROR("setSlaveOneMotorOperatingMode2ProfileVelocity failed");
            return 0;
        }
        else
        {
            ROS_INFO_ONCE("setSlaveOneMotorOperatingMode2ProfileVelocity ok\n");
        }
    }

    // enable the controller
    if(!duetController.enableControlSDO_SlaveZero())
    {
        ROS_ERROR("enableControlSDO_SlaveZero failed");
        return 0;
    }
    else
    {
        ROS_INFO_ONCE("enableControlSDO_SlaveZero ok\n");
    }
    if(duetController.hasSlaveOne)
    {
        if(!duetController.enableControlSDO_SlaveOne())
        {
            ROS_ERROR("enableControlSDO_SlaveOne failed");
            return 0;
        }
        else
        {
            ROS_INFO_ONCE("enableControlSDO_SlaveOne ok\n");
        }
    }

    duetController.run();
    return 0;
}
