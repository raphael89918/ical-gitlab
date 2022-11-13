#include "udp_motorCtrl/udp_motorCtrl.hpp"
#include "mecanum_wheel/mecanum_wheel.hpp"

int main (int argc, char **argv)
{
    ros::init(argc, argv, "motorCtrl_node");
    ros::NodeHandle nh;

    float r_fl(1), r_fr(1), r_bl(1), r_br(1);
    nh.getParam("/wheel_ratio_fl", r_fl);
    nh.getParam("/wheel_ratio_fr", r_fr);
    nh.getParam("/wheel_ratio_bl", r_bl);
    nh.getParam("/wheel_ratio_br", r_br);
    
    mecanum_wheel mecanum_wheel(0.21, 0.035, r_fl, r_fr, r_bl, r_br);
    motorCtrl motorCtrl(nh);

    motorCtrl.start();
    while(ros::ok())
    {
        ros::Rate loop_rate(100);
        ros::spinOnce();
        motorCtrl.transform_to_pwm(mecanum_wheel.robot_to_wheel(motorCtrl.vel_x, motorCtrl.vel_y, motorCtrl.vel_th));
        motorCtrl.encoder_calculate();
        motorCtrl.m_pub.publish(motorCtrl.m_msg);
        loop_rate.sleep();
    }
}
