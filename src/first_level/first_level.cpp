#include "first_level/first_level.hpp"


int main(int argc, char **argv)
{
    ros::init(argc, argv, "first_level");
    ros::NodeHandle nh;
    first_level first_level(nh);
    first_level.init_pubsub();
    ROS_INFO("waiting");
    ros::Duration(10).sleep();
    ROS_INFO("GO");
    
    // ROS_INFO("go front 90");
    // first_level.robot_move(front, 60);
    
    // ROS_INFO("go to far left");
    // first_level.robot_far(left);
    // first_level.robot_move(right, 3);
    
    ROS_INFO("choose target");
    first_level.choose_target();
    
    return 0;
}
