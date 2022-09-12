#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "wheel_tokyo_weili/motor.h"

#define ROBOT_WIDTH 250
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

    void start();

    void callback(const geometry_msgs::Twist &msg);
    void execute();
private:
    ros::NodeHandle m_nh;
    ros::NodeHandle t_nh;

    ros::Publisher m_pub;

    wheel_tokyo_weili::motor m_msg;

    ros::Subscriber m_sub;

    double right_vel, left_vel;

    float wheel_vel[4];
    bool wheel_dir[4];
    void transform(float vel_x, float vel_y, float vel_th);
    void pub_to_pwm();
};

