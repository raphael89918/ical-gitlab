#include <ros/ros.h>
#include "wheel_tokyo_weili/wheel_planner.h"
#include "wheel_tokyo_weili/encoder.h"
#include "geometry_msgs/Twist.h"

class wheel_planner
{
private:
    ros::NodeHandle encoder_nh;
    ros::NodeHandle planner_nh;
    ros::NodeHandle wheelCtrl_nh;
    ros::Subscriber encoder_sub;
    ros::Subscriber planner_sub;
    ros::Publisher pub;
    geometry_msgs::Twist msg;
    void encoder_callback(const wheel_tokyo_weili::encoder &msg);
    void planner_callback(const wheel_tokyo_weili::wheel_planner &msg);
    
    void distance_processed_x();
    void distance_processed_y();
    void distance_processed_z();

    void velocity_processed();

    float encRobot_x, encRobot_y, encRobot_z;
    float dis_x, dis_y, dis_z;
    float vel_x, vel_y, vel_z;

public:
    wheel_planner(const ros::NodeHandle &encoder_nh, const ros::NodeHandle &planner_nh, const ros::NodeHandle &wheelCtrl_nh);
    void init_pubsub();
    void ctrl_method();
};