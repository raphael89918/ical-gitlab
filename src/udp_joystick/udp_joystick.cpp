#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Joy.h>
#include <iostream>
#include "dynamixel_control/arm_trunk.h"

using namespace std;

class Teleop
{
public:
    Teleop();

private:
    /* data */
    void callback(const sensor_msgs::Joy::ConstPtr &Joy);
    ros::NodeHandle n;
    ros::Subscriber sub;
    ros::Publisher pub;
    ros::Publisher dyna_pub;
    double vlinear, vangular;
    int axis_ang, axis_lin_x, axis_lin_y, ton;
    int ready_trunk, crab, ready_crab, stack, dyna_init, putin;
};

Teleop::Teleop()
{
    n.param<int>("axis_linear_x", axis_lin_x, 1);
    n.param<int>("axis_linear_y", axis_lin_y, 0);
    n.param<int>("axis_angular", axis_ang, 2);

    n.param<double>("vel_linear", vlinear, 0.5);
    n.param<double>("vel_angular", vangular, 1);

    n.param<int>("button", ton, 5);

    n.param<int>("ready_trunk", ready_trunk, 0);
    n.param<int>("crab", crab, 4);
    n.param<int>("putin", putin, 1);
    n.param<int>("ready_crab", ready_crab, 6);
    n.param<int>("stack", stack, 2);
    n.param<int>("dyna_init", dyna_init, 7);

    pub = n.advertise<geometry_msgs::Twist>("/cmd_vel", 1);
    sub = n.subscribe<sensor_msgs::Joy>("/joy", 1, &Teleop::callback, this);
    dyna_pub = n.advertise<dynamixel_control::arm_trunk>("/dynamixel/arm_storage", 1);
}

void Teleop::callback(const sensor_msgs::Joy::ConstPtr &Joy)
{
    geometry_msgs::Twist v;
    dynamixel_control::arm_trunk msg;
    ros::Rate loop_rate(100);
    if (Joy->buttons[ton])
    {
        v.linear.x = (Joy->axes[axis_lin_x]) * vlinear;
        v.linear.y = -(Joy->axes[axis_lin_y]) * vlinear;
        v.angular.z = -(Joy->axes[axis_ang]) * vangular;
        if(Joy->buttons[dyna_init] == 1)
        {
            msg.control = 6;
        }
        if(Joy->buttons[ready_trunk] == 1)
        {
            msg.control = 1;
        }
        if(Joy->buttons[ready_crab] == 1)
        {
            msg.control = 4;
        }
        if(Joy->buttons[crab] == 1)
        {
            msg.control = 2;
        }
        if(Joy->buttons[putin] == 1)
        {
            msg.control = 3;
        }
        if(Joy->buttons[stack] == 1)
        {
            msg.control = 5;
        }
        dyna_pub.publish(msg);
        pub.publish(v);
        loop_rate.sleep();
    }
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "joy");
    Teleop telelog;
    ros::spin();
    return 0;
}
