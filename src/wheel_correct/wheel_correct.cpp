#include <ros/ros.h>
#include "wheel_planner/wheel_planner.hpp"
#include "conio.h"
#include "wheel_tokyo_weili/encoder.h"
#include "wheel_tokyo_weili/waitforidle.h"

float encRobot_x, encRobot_y, encRobot_z;
float tx, ty, tz;
void encoder_callback(const wheel_tokyo_weili::encoder &msg)
{
    encRobot_x = msg.robot_distance[0] / 21.2;
    encRobot_y = msg.robot_distance[1] / 20.03;
    encRobot_z = msg.robot_distance[2] / 7;
    // std::cout << "encoder_callback" << std::endl;
}

bool wait;
void wait_callback(const wheel_tokyo_weili::waitforidle &msg)
{
    wait = msg.wait;
    if(msg.wait==false)
    {
        tx = encRobot_x;
        ty = encRobot_y;
        tz = encRobot_z;
    }
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "test");
    ros::NodeHandle nh;
    ros::Subscriber wait_sub = nh.subscribe("/wheel/waitforidle", 1, &wait_callback);
    ros::Subscriber sub = nh.subscribe("/wheel/distance", 1, &encoder_callback);
    ros::Publisher pub = nh.advertise<wheel_tokyo_weili::wheel_planner>("/wheel/planner", 1);
    ros::Rate loop_rate(10);
    wheel_tokyo_weili::wheel_planner msg;

    char kbin;
    while (kbin != 27)
    {
        // Get keyboard input
        if (kbhit())
        {
            kbin = getch();
            // Find speeds
            switch (toupper(kbin))
            {
            case 'W':
                msg.distance_x = 30;
                msg.distance_y = 0;
                msg.distance_z = 0;
                break;
            }
            pub.publish(msg);
            while(wait==false)
            {
                ros::spin();
            }
            std::cout << tx << " " << ty << " " << tz << std::endl;
        }
        ros::Duration(0.01).sleep();
    }
    return 0;
}
