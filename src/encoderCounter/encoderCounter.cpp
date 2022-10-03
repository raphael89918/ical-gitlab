#include "encoderCounter/encoderCounter.hpp"
#include "mecanum_wheel/mecanum_wheel.hpp"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "encoderCounter_node");
    ros::NodeHandle nh;
    ros::Rate loop_rate(30);

    Encoder Encoder(nh);
    mecanum_wheel mecanum_wheel(0.21, 0.035, 1);

    Encoder.init();
    while(ros::ok())
    {
        ros::Rate loop_rate(10);
        ros::spinOnce();
        Encoder.transform_to_msg(mecanum_wheel.wheel_to_robot(Encoder.fl,Encoder.fr,Encoder.bl,Encoder.br));
        Encoder.encoder_publish();

        loop_rate.sleep();
    }
}
