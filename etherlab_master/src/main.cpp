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
    duetController.test_getMotorOperatingModeSDO_SlaveZero();//  <------ tested ok
//    duetController.testOperateHomingMethod_SlaveZero();
    return 0;
}
