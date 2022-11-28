#include "encoderCounter/encoderCounter.hpp"
#include "mecanum_wheel/mecanum_wheel.hpp"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "encoderCounter_node");
    ros::NodeHandle nh;

    Encoder Encoder(nh);
    float r_fl{1}, r_fr{1}, r_bl{1}, r_br{1};
    nh.getParam("/wheel_ratio_fl", r_fl);
    nh.getParam("/wheel_ratio_fr", r_fr);
    nh.getParam("/wheel_ratio_bl", r_bl);
    nh.getParam("/wheel_ratio_br", r_br);
    ROS_INFO("encoderCounter_node: r_fl = %f, r_fr = %f, r_bl = %f, r_br = %f", r_fl, r_fr, r_bl, r_br);
    mecanum_wheel mecanum_wheel(0.21, 0.035, r_fl, r_fr, r_bl, r_br);

    Encoder.init();
    while(ros::ok())
    {
        ros::Rate loop_rate(100);
        ros::spinOnce();
        Encoder.transform_to_msg(mecanum_wheel.wheel_to_robot(Encoder.fl,Encoder.fr,Encoder.bl,Encoder.br));

        Encoder.encoder_publish();
        loop_rate.sleep();
    }
}
