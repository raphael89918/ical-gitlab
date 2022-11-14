#include "motorCtrl/motorCtrl.hpp"

motorCtrl::motorCtrl(const ros::NodeHandle &nh)
    : m_nh(nh), t_nh(nh), pid_wheel(1, 0, 0, 0), yet_bl(0), yet_br(0), yet_fl(0), yet_fr(0)
    ,con_fl(0),con_fr(0),con_bl(0),con_br(0)
{
    ROS_INFO("class motorCtrl has been constructed");
}

motorCtrl::~motorCtrl()
{
    ROS_INFO("class motorCtrl has been destructed");
}

void motorCtrl::start()
{
    ROS_INFO("Starting to set up pub and sub");
    m_pub = m_nh.advertise<wheel_tokyo_weili::motor>("/wheel/motor", 1);
    m_sub = t_nh.subscribe("/cmd_vel", 1, &motorCtrl::callback, this);
    e_sub = t_nh.subscribe("/encoder", 1, &motorCtrl::encoder_callback, this);
    ROS_INFO("Initialzing motor parameter");
    enc_fl = 0;
    enc_fr = 0;
    enc_bl = 0;
    enc_br = 0;
    enc_sum = 0;
    vel_x = 0;
    vel_y = 0;
    vel_th = 0;
}
void motorCtrl::encoder_callback(const wheel_tokyo_weili::encoder &msg)
{
    enc_fl = msg.wheel_value[0];
    enc_fr = msg.wheel_value[1];
    enc_bl = msg.wheel_value[2];
    enc_br = msg.wheel_value[3];
    encoder_calculate();
}

void motorCtrl::encoder_calculate()
{
    enc_fl = enc_fl - yet_fl;
    enc_fr = enc_fr - yet_fr;
    enc_bl = enc_bl - yet_bl;
    enc_br = enc_br - yet_br;
    enc_sum = (abs(enc_fl) + abs(enc_fr) + abs(enc_bl) + abs(enc_br))/4;
    yet_fl = enc_fl;
    yet_fr = enc_fr;
    yet_bl = enc_bl;
    yet_br = enc_br;
    con_fl = enc_sum - abs(enc_fl);
    con_fr = enc_sum - abs(enc_fr);
    con_bl = enc_sum - abs(enc_bl);
    con_br = enc_sum - abs(enc_br);
}

void motorCtrl::callback(const geometry_msgs::Twist &msg)
{
    vel_x = msg.linear.x;
    vel_y = -msg.linear.y;
    vel_th = msg.angular.z;
}

void motorCtrl::transform_to_pwm(float *wheel_vel)
{
    for (int i = 0; i < 4; i++)
    {
        if (wheel_vel[i] > 0)
        {
            wheel_dir[i] = true;
        }
        if (wheel_vel[i] <= 0)
        {
            wheel_dir[i] = false;
            wheel_vel[i] = wheel_vel[i] * -1;
            if(wheel_vel[i]==0)
            {
                con_fl = 0;
                con_fr = 0;
                con_bl = 0;
                con_br = 0;
            }
        }
    }

    m_msg.FL = pid_wheel.pidCtrl(con_fl, wheel_vel[FL]);
    m_msg.BL = pid_wheel.pidCtrl(con_bl, wheel_vel[BL]);
    m_msg.FR = pid_wheel.pidCtrl(con_fr, wheel_vel[FR]);
    m_msg.BR = pid_wheel.pidCtrl(con_br, wheel_vel[BR]);

    m_msg.FL_DIR = wheel_dir[FL];
    m_msg.BL_DIR = wheel_dir[BL];
    m_msg.FR_DIR = wheel_dir[FR];
    m_msg.BR_DIR = wheel_dir[BR];
}

