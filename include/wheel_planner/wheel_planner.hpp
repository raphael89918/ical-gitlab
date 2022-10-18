#include <ros/ros.h>
#include "wheel_tokyo_weili/wheel_planner.h"
#include "wheel_tokyo_weili/encoder.h"
#include "geometry_msgs/Twist.h"
#include "gpio/Laser.h"
#include "ros/callback_queue.h"

class wheel_planner
{
private:
    ros::NodeHandle encoder_nh;
    ros::NodeHandle planner_nh;
    ros::NodeHandle wheelCtrl_nh;
    ros::NodeHandle laser_nh;
    ros::CallbackQueue state, plan;

    ros::Subscriber encoder_sub;
    ros::Subscriber planner_sub;
    ros::Subscriber laser_sub;

    ros::Publisher pub;
    ros::Publisher enc_pub;
    geometry_msgs::Twist msg;
    wheel_tokyo_weili::wheel_planner enc_msg;

    void encoder_callback(const wheel_tokyo_weili::encoder &msg);
    void planner_callback(const wheel_tokyo_weili::wheel_planner &msg);
    void laser_callback(const gpio::Laser &msg);

    void distance_processed_x();
    void distance_processed_y();
    void distance_processed_z();

    void velocity_processed();
    void go_to_far(bool left, bool right);

    void init_encoder();
    void stop_robot();

    float encRobot_x, encRobot_y, encRobot_z;
    float dis_x, dis_y, dis_z;
    float vel_x, vel_y, vel_z;
    float temp_x, temp_y, temp_z;
    int laser_ul, laser_ur, laser_dl, laser_dr;
    bool far_left, far_right;

public:
    wheel_planner(const ros::NodeHandle &encoder_nh, const ros::NodeHandle &planner_nh, const ros::NodeHandle &wheelCtrl_nh, const ros::NodeHandle &laser_nh);
    void init_pubsub();
    void ctrl_method();
};