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
    duetController.testGetStatusword();
//    ROS_INFO("2222222");
//    duetController.testGetStatusword();
//    ros::spin();
//    ros::spinOnce();
    return 0;
}
