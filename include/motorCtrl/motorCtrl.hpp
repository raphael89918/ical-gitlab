#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "wheel_tokyo_weili/motor.h"
#include "wheel_tokyo_weili/encoder.h"
#include "pid.hpp"
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

    float vel_x;
    float vel_y;
    float vel_th;
    void transform_to_pwm(float *wheel_vel);
    void encoder_calculate();
    
private:
    ros::NodeHandle m_nh;
    ros::NodeHandle t_nh;

    ros::Subscriber m_sub;
    ros::Subscriber e_sub;
    void encoder_callback(const wheel_tokyo_weili::encoder &msg);
    double right_vel, left_vel;
    int enc_fl, enc_fr, enc_bl, enc_br, enc_sum;
    int yet_fl, yet_fr, yet_bl, yet_br;
    int con_fl, con_fr, con_bl, con_br;
    float wheel_vel[4];
    bool wheel_dir[4];
    PID pid_wheel;
};
