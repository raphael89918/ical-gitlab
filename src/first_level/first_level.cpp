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
    
    ROS_INFO("go front 30");
    first_level.robot_move(front, 20);
    
    ROS_INFO("go to far right");
    first_level.robot_far(right);
    first_level.robot_move(left, 5);
    
    ROS_INFO("go front 100");
    first_level.robot_move(front, 110);

    ROS_INFO("turn -90 angle");
    first_level.robot_move(rotate, -90);

    ROS_INFO("choose target");
    first_level.choose_target();
    
    ROS_INFO("go back 10");
    first_level.robot_move(back, 3);

    ROS_INFO("turn -90 angle");
    first_level.robot_move(rotate, -90);

    ROS_INFO("go back 120");
    first_level.robot_move(back, 120);

    ROS_INFO("Heap target");
    first_level.heap_target();

    ROS_INFO("go front 10");
    first_level.robot_move(front, 10);

    ROS_INFO("turn 180 angle");
    first_level.robot_move(rotate, 180);

    ROS_INFO("go to far left");
    first_level.robot_far(left);

    return 0;
}
