#include <iostream.hpp>
#include <ros/ros.h>
#include "wheel_tokyo_weili/encoder.h"

class Encoder
{
private:
    ros::NodeHandle nh;
    ros::Publisher pub;
    ros::Subscriber sub;
    wheel_tokyo_weili::encoder msg;

    int wheel_distance[4];
public:
    Encoder(const ros::NodeHandle &nh)
    void callback(const wheel_tokyo_weili::encoder &msg);
    void start();
    void encoder_to_distance();
};

Encoder::Encoder(const ros::NodeHandle &nh):nh(nh)
{
    ROS_INFO("Encoder constructed");    
}

void Encoder::start()
{
    pub = nh.advertise<wheel_tokyo_weili::encoder>("/wheel_distance",1);
    sub = nh.subscribe("/encoder", 1, &wheel_tokyo_weili::callback, this);
}

void Encoder::callback(const wheel_tokyo_weili::encoder &msg)
{
    for(int i=0;i<4;i++)
    {
        wheel_distance[i] = msg.value[i];
    }
}

void Encoder::encoder_to_distance()
{
    
}