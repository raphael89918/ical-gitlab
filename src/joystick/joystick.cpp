#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Joy.h>
#include <iostream>
using namespace std;

class Teleop
{
public:
    Teleop();

private:
    /* data */
    void callback(const sensor_msgs::Joy::ConstPtr& Joy);
    ros::NodeHandle n;
    ros::Subscriber sub ;
    ros::Publisher pub ;
    double vlinear,vangular;
    int axis_ang,axis_lin_x,axis_lin_y,ton;
};

Teleop::Teleop()
{
    n.param<int>("axis_linear_x",axis_lin_x,1);
    n.param<int>("axis_linear_y",axis_lin_y,0);//test
    n.param<int>("axis_angular",axis_ang,3);
    //n.param<int>("axis_angular",axis_ang,2);
    n.param<double>("vel_linear",vlinear,0.5);
    n.param<double>("vel_angular",vangular,1);
    n.param<int>("button",ton,5);
    pub = n.advertise<geometry_msgs::Twist>("/cmd_vel",1);
    sub = n.subscribe<sensor_msgs::Joy>("/joy",1,&Teleop::callback,this);
}

void Teleop::callback(const sensor_msgs::Joy::ConstPtr& Joy)
{
    geometry_msgs::Twist v;
    ros::Rate loop_rate(100);
   if(Joy->buttons[ton])
     {
     v.linear.x =(Joy->axes[axis_lin_x])*vlinear;
     v.linear.y =(Joy->axes[axis_lin_y])*vlinear;//test
     v.angular.z = (Joy->axes[axis_ang])*vangular;
     ROS_INFO("linear_x:%.3lf  linear_y:%.3lf  angular:%.3lf",v.linear.x,v.linear.y,v.angular.z);//test
     pub.publish(v);
     loop_rate.sleep();
     }
}

int main(int argc,char** argv)
{
    ros::init(argc, argv, "joy");
    Teleop telelog;
    ros::spin();
    return 0;
}
