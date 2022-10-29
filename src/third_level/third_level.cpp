#include "third_level/third_level.hpp"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "third_level_node");
    ros::NodeHandle nh;
    third_level third_level(nh);
    third_level.init_pubsub();

    uint8_t front, left, right;
    third_level.robot_far(left);
    third_level.robot_far(front);
    third_level.robot_far(right);
    third_level.robot_far(front);
    third_level.robot_far(left);
    third_level.robot_move(front, 40);
}