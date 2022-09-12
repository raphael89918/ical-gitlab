#include "motorCtrl/motorCtrl.hpp"

int main (int argc, char **argv)
{
    ros::init(argc, argv, "motorCtrl_node");
    ros::NodeHandle nh;
    ros::Rate loop_rate(30);


    motorCtrl motorCtrl(nh);
    motorCtrl.start();
    while(ros::ok())
    {
        motorCtrl.execute();
    }
}

