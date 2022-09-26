#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "wheel_tokyo_weili/motor.h"

#define LEFT 0
#define RIGHT 1

enum WHEEL_POSITION : uint8_t
{
    FL = 0,
    FR = 1,
    BL = 2,
    BR = 3
};

enum DIRECTION : bool
{
    FORWARD = true,
    BACKWARD = false,
};

struct wheel_data
{
    uint8_t pwm;
    DIRECTION direction;
};

class motorCtrl
{
public:
    motorCtrl(const ros::NodeHandle &nh);
    ~motorCtrl();

    wheel_tokyo_weili::motor m_msg;
    ros::Publisher m_pub;

    void start();

    void callback(const geometry_msgs::Twist &msg);
    void execute();

    float vel_x;
    float vel_y;
    float vel_th;
    void transform_to_pwm(float* wheel_vel);

private:
    ros::NodeHandle m_nh;
    ros::NodeHandle t_nh;

    ros::Subscriber m_sub;

    double right_vel, left_vel;

    float wheel_vel[4];
    bool wheel_dir[4];
};
