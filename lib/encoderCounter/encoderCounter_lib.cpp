#include "encoderCounter/encoderCounter.hpp"

Encoder::Encoder()
{
    ROS_INFO("Default Encoder constructed");
    m_fl = 1;
    m_fr = 1;
    m_bl = 1;
    m_br = 1;
}

Encoder::Encoder(ros::NodeHandle &nh) : m_nh(nh), m_fl(1), m_fr(1), m_bl(1), m_br(1)
{
    ROS_INFO("Encoder constructed");
    m_sub = m_nh.subscribe("/encoder", 1, &Encoder::callback, this);
    m_pub = m_nh.advertise<wheel_tokyo_weili::encoder>("/wheel/distance", 1);
}

Encoder::~Encoder()
{
    ROS_INFO("Encoder destructed");
}

void Encoder::init()
{
    m_distance_msg.robot_distance[0] = 0;
    m_distance_msg.robot_distance[1] = 0;
    m_distance_msg.robot_distance[2] = 0;
}

void Encoder::callback(const wheel_tokyo_weili::encoder &wheel_msg)
{
    m_fl = wheel_msg.wheel_value[0];
    m_fr = wheel_msg.wheel_value[1];
    m_bl = wheel_msg.wheel_value[2];
    m_br = wheel_msg.wheel_value[3];
    for (int i = 0; i < 4; i++)
    {
        m_distance_msg.wheel_value[i] = wheel_msg.wheel_value[i];
    }
}

void Encoder::transform_to_msg(std::array<float, 3> dis)
{
    for (int i = 0; i < 3; i++)
    {
        m_distance_msg.robot_distance[i] = dis[i];
    }
}

void Encoder::encoder_publish()
{
    m_pub.publish(m_distance_msg);
}

float Encoder::get_fl() { return m_fl; }

float Encoder::get_fr() { return m_fr; }

float Encoder::get_bl() { return m_bl; }

float Encoder::get_br() { return m_br; }
