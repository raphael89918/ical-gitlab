#include "first_level/first_level.hpp"


int main(int argc, char **argv)
{
    ros::init(argc, argv, "third_level_node");
    ros::NodeHandle nh;
    third_level third_level(nh);
    third_level.init_pubsub();
    ROS_INFO("waiting");
    ros::Duration(10).sleep();
    ROS_INFO("GO");
    
    ROS_INFO("go front 90");
    third_level.robot_move(front, 90);
    
    ROS_INFO("go to far left");
    third_level.robot_far(left);
    third_level.robot_move(right, 3);
    
    ROS_INFO("choose target");
    third_level.choose_target();
    
    return 0;
}
