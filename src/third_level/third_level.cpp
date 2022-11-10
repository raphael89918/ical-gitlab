#include "third_level/third_level.hpp"


int main(int argc, char **argv)
{
    ros::init(argc, argv, "third_level_node");
    ros::NodeHandle nh;
    third_level third_level(nh);
    third_level.init_pubsub();
    ROS_INFO("waiting");
    ros::Duration(10).sleep();
    ROS_INFO("GO");
    // ROS_INFO("far_left");
    // third_level.robot_far(left);
    ROS_INFO("far_front");
    third_level.robot_far(front);
    ROS_INFO("far_right");
    third_level.robot_far(right);
    ROS_INFO("far_front");
    third_level.robot_far(front);
    ROS_INFO("far_left");
    third_level.robot_far(left);
    ROS_INFO("robot_move");
    third_level.robot_move(front, 40);
    // ROS_INFO("trace_traget");
    // third_level.trace_target();
    ROS_INFO("far_right");
    third_level.robot_far(right);
    ROS_INFO("robot_move");
    third_level.robot_move(front, 50);
}
