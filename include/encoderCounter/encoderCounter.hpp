#include <ros/ros.h>
#include <iostream>
#include "wheel_tokyo_weili/encoder.h"
#include <bits/stdc++.h>

class Encoder
{
public:
    Encoder();
    Encoder(ros::NodeHandle &nh);
    ~Encoder();
    void init();
    void encoder_to_distance();
    void transform_to_msg(std::array<float, 3> dis);
    void encoder_publish();
    float get_fl();
    float get_fr();
    float get_bl();
    float get_br();

private:
    ros::NodeHandle m_nh;
    ros::Subscriber m_sub;
    ros::Publisher m_pub;
    float m_fl;
    float m_fr;
    float m_bl;
    float m_br;
    // std::vector<float> Encoder_robot;

    wheel_tokyo_weili::encoder m_distance_msg;
    void callback(const wheel_tokyo_weili::encoder &wheel_msg);
};
