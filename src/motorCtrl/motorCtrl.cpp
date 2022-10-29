#include "motorCtrl/motorCtrl.hpp"
#include "mecanum_wheel/mecanum_wheel.hpp"

int main (int argc, char **argv)
{
    ros::init(argc, argv, "motorCtrl_node");
    ros::NodeHandle nh;

    mecanum_wheel mecanum_wheel(0.21, 0.035, 1);
    motorCtrl motorCtrl(nh);

    motorCtrl.start();
    while(ros::ok())
    {
        ros::Rate loop_rate(100);
        ros::spinOnce();
        motorCtrl.transform_to_pwm(mecanum_wheel.robot_to_wheel(motorCtrl.vel_x, motorCtrl.vel_y, motorCtrl.vel_th));
        motorCtrl.m_pub.publish(motorCtrl.m_msg);
        loop_rate.sleep();
    }
}