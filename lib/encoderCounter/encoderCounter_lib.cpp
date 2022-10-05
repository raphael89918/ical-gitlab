#include "encoderCounter/encoderCounter.hpp"

Encoder::Encoder(const ros::NodeHandle &nh):nh(nh)
{
    ROS_INFO("Encoder constructed");
}

void Encoder::init()
{
    pub = nh.advertise<wheel_tokyo_weili::encoder>("/wheel/distance",1);
    sub = nh.subscribe("/encoder", 1, &Encoder::callback, this);
}

void Encoder::callback(const wheel_tokyo_weili::encoder &wheel_msg)
{
    fl = wheel_msg.wheel_value[0];
    fr = wheel_msg.wheel_value[1];
    bl = wheel_msg.wheel_value[2];
    br = wheel_msg.wheel_value[3];
    for(int i =0;i<4;i++)
    {
        distance_msg.wheel_value[i] = wheel_msg.wheel_value[i];
    }
}

void Encoder::transform_to_msg(float *dis)
{
    for(int i=0;i<3;i++)
    {
        distance_msg.robot_distance[i] = dis[i];
    }
}

void Encoder::encoder_publish()
{
    pub.publish(distance_msg);
}
