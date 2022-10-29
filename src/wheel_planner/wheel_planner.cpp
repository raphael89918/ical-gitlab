#include "wheel_planner/wheel_planner.hpp"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "wheel_planner_node");

    ros::NodeHandle encoder_nh;
    ros::NodeHandle planner_nh;
    ros::NodeHandle wheelCtrl_nh;
    ros::NodeHandle laser_nh;
    ros::NodeHandle wait_nh;
    wheel_planner wheel_planner(encoder_nh, planner_nh, wheelCtrl_nh, laser_nh);

    wheel_planner.init_pubsub();
    
    while(ros::ok())
    {
        ros::Rate loop_rate(100);
        wheel_planner.ctrl_method();
        loop_rate.sleep();
    }
}