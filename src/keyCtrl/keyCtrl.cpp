#include <conio.h>
#include "ros/ros.h"
#include "geometry_msgs/Twist.h"

int main(int argc, char* argv[])
{
    int f_leftSpeed, f_rightSpeed, b_leftSpeed, b_rightSpeed;
    char kbin;

    geometry_msgs::Twist msg;
    ros::init(argc, argv, "key_Ctrl_node");
    ros::NodeHandle n;
    ros::Rate loop_rate(30);
    ros::Publisher wheel_twist_pub = n.advertise<geometry_msgs::Twist>("/cmd_vel", 1);
    while (kbin != 27) {
        // Get keyboard input
        if (kbhit()) {
            kbin = getch();

        // Find speeds
            switch (toupper(kbin)) {
            case 'W':
                msg.linear.x = 0.2;
                msg.linear.y = 0;
                msg.angular.z = 0;
                break;

            case 'D':
                msg.linear.x = 0;
                msg.linear.y = -0.2;
                msg.angular.z = 0;
                break;

            case 'S':
                msg.linear.x = -0.2;
                msg.linear.y = 0;
                msg.angular.z = 0;
                break;

            case 'A':
                msg.linear.x = 0;
                msg.linear.y = 0.2;
                msg.angular.z = 0;
                break;

            case 'Q':
                msg.linear.x = 0;
                msg.linear.y = 0;
                msg.angular.z = 0.2;
                break;


            case 'E':
                msg.linear.x = 0;
                msg.linear.y = 0;
                msg.angular.z = -0.2;
                break;

            default:
                msg.linear.x = 0;
                msg.linear.y = 0;
                msg.angular.z = 0;
            }
        }
        else
        {
            msg.linear.x = 0;
            msg.linear.y = 0;
            msg.angular.z = 0;
        }


        wheel_twist_pub.publish(msg);
        loop_rate.sleep();
    }

    return 0;
}


