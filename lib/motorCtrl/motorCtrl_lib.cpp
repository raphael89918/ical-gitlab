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
    float vel_x = msg.linear.x;
    float vel_y = msg.linear.y;
    float vel_th = msg.angular.z;
    transform(vel_x, vel_y, vel_th);
    pub_to_pwm();
}

void motorCtrl::transform(float vel_x, float vel_y, float vel_th)
{
    float WHEEL_K = 0.21; //輪子相對於中心點的xy位置相加
    float WHEEL_R = 0.035; //輪子的半徑
    float WHEEL_PI = 3.14;
    float WHEEL_RATIO = 1; //減速度比

    //轉換成四個輪子
    wheel_vel[FL] = vel_x - vel_y - WHEEL_K * vel_th;
    wheel_vel[BL] = vel_x + vel_y - WHEEL_K * vel_th;
    wheel_vel[BR] = vel_x - vel_y + WHEEL_K * vel_th;
    wheel_vel[FR] = vel_x + vel_y + WHEEL_K * vel_th;

    //轉換成輪子的速度RPS（弧度/S）
    wheel_vel[FL] = wheel_vel[FL]/(2.0 * WHEEL_R * WHEEL_PI);
    wheel_vel[BL] = wheel_vel[BL]/(2.0 * WHEEL_R * WHEEL_PI);
    wheel_vel[FR] = wheel_vel[FR]/(2.0 * WHEEL_R * WHEEL_PI);
    wheel_vel[BR] = wheel_vel[BR]/(2.0 * WHEEL_R * WHEEL_PI);

    //轉換為RPM
    wheel_vel[FL] = wheel_vel[FL] * WHEEL_RATIO * 60;
    wheel_vel[BL] = wheel_vel[BL] * WHEEL_RATIO * 60;
    wheel_vel[FR] = wheel_vel[FR] * WHEEL_RATIO * 60;
    wheel_vel[BR] = wheel_vel[BR] * WHEEL_RATIO * 60;


}

void motorCtrl::pub_to_pwm()
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
    ros::Rate loop_rate(10);
    ros::spinOnce();
    m_pub.publish(m_msg);
    loop_rate.sleep();
}

