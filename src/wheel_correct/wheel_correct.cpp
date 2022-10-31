#include <ros/ros.h>
#include "wheel_planner/wheel_planner.hpp"
#include "conio.h"
#include "wheel_tokyo_weili/encoder.h"
#include "wheel_tokyo_weili/waitforidle.h"

float fl, fr, bl, br;
float tfl, tfr, tbl, tbr;
void encoder_callback(const wheel_tokyo_weili::encoder &msg)
{
    fl = msg.wheel_value[0];
    fr = msg.wheel_value[1];
    bl = msg.wheel_value[2];
    br = msg.wheel_value[3];
}

bool wait;
void wait_callback(const wheel_tokyo_weili::waitforidle &msg)
{
    wait = msg.wait;
    if(msg.wait==false)
    {
        tfl = fl;
        tfr = fr;
        tbl = bl;
        tbr = br;
    }
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "test");
    ros::NodeHandle nh;
    ros::Subscriber wait_sub = nh.subscribe("/wheel/waitforidle", 1, &wait_callback);
    ros::Subscriber sub = nh.subscribe("/encoder", 1, &encoder_callback);
    ros::Publisher pub = nh.advertise<wheel_tokyo_weili::wheel_planner>("/wheel/planner", 1);
    ros::Rate loop_rate(10);
    wheel_tokyo_weili::wheel_planner msg;
    msg.distance_x = 30;
    msg.distance_y = 0;
    msg.distance_z = 0;
    ros::spinOnce();
    ros::Duration(0.5).sleep();
    pub.publish(msg);
    while(wait==false)
    {
        ros::spin();
        ros::Duration(0.01).sleep();
    }
    std::cout << tfl << " " << tfr << " " << tbl << " " << tbr << "end" << std::endl;
    return 0;
}
