#include "encoderCounter/encoderCounter.hpp"

Encoder::Encoder(const ros::NodeHandle &nh):nh(nh)
{
    ROS_INFO("Encoder constructed");    
}

void Encoder::start()
{
    pub = nh.advertise<wheel_tokyo_weili::encoder>("/wheel_distance",1);
    sub = nh.subscribe("/encoder", 1, &Encoder::callback, this);
}

void Encoder::callback(const wheel_tokyo_weili::encoder &wheel_msg)
{
    fl = wheel_msg.wheel_value[0];
    fr = wheel_msg.wheel_value[1];
    bl = wheel_msg.wheel_value[2];
    br = wheel_msg.wheel_value[3];
}

void Encoder::transform_to_msg(float *dis)
{
    for(int i=0;i<3;i++)
    {
        distance_msg.robot_distance[i] = dis[i];
    }
}
