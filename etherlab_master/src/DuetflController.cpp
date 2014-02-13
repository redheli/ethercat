/** Duet FL motor controller
 *
 */

#include <ros/ros.h>

#include <std_msgs/Float64.h>
#include <std_msgs/Bool.h>
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>


int main(int argc, char**argv)
{
    ROS_INFO("Hello there?!");
    ros::init(argc, argv, "Duet FL motor controller");
//    ros::spin();
//    ros::spinOnce();
    return 0;
}
