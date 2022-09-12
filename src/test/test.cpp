#include "test/test.hpp"

int main(int argc,char **argv)
{
    ros::init(argc,argv,"test");
    ros::NodeHandle nh;

    Test test;
    while(ros::ok())
    {
        test.print("holy shit if this worked");
    }
    return 0;
}
