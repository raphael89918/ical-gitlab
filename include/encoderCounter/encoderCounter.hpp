#include <iostream>
#include "wheel_tokyo_weili/encoder.h"
#include <ros/ros.h>

class Encoder
{
public:
    ros::NodeHandle nh;
    ros::Subscriber sub;
    wheel_tokyo_weili::encoder distance_msg;

    Encoder(const ros::NodeHandle &nh);
    void callback(const wheel_tokyo_weili::encoder &wheel_msg);
    void start();
    void encoder_to_distance();

    float fl, fr, bl, br;
    float Encoder_robot[3];
    void transform_to_msg(float *dis);
    ros::Publisher pub;
};