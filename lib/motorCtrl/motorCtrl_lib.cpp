#include "motorCtrl/motorCtrl.hpp"

motorCtrl::motorCtrl(const ros::NodeHandle &nh)
    : m_nh(nh), t_nh(nh)
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
    ROS_INFO("Initialzing motor parameter");

}

void motorCtrl::callback(const geometry_msgs::Twist &msg)
{
    vel_x = msg.linear.x;
    vel_y = msg.linear.y;
    vel_th = msg.angular.z;
}

void motorCtrl::transform_to_pwm(float* wheel_vel)
{
    for(int i=0;i<4;i++)
    {
        if(wheel_vel[i] > 0)
        {
            wheel_dir[i] = true;
        }
        if(wheel_vel[i] <= 0)
        {
            wheel_dir[i] = false;
            wheel_vel[i] = wheel_vel[i] * -1;
        }
    }
    m_msg.FL = wheel_vel[FL];
    m_msg.BL = wheel_vel[BL];
    m_msg.FR = wheel_vel[FR];
    m_msg.BR = wheel_vel[BR];

    m_msg.FL_DIR = wheel_dir[FL];
    m_msg.BL_DIR = wheel_dir[BL];
    m_msg.FR_DIR = wheel_dir[FR];
    m_msg.BR_DIR = wheel_dir[BR];
}

void motorCtrl::execute()
{
    ros::spinOnce();
    m_pub.publish(m_msg);
}
