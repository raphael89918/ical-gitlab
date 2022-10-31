#include <ros/ros.h>
#include "wheel_tokyo_weili/wheel_planner.h"
#include "wheel_tokyo_weili/waitforidle.h"
enum DIRECTION
{
    left = 0,
    right = 1,
    front = 2
};

class third_level
{
private:
    ros::NodeHandle nh;
    ros::Publisher wheel_pub;
    ros::Subscriber wait_sub;
    wheel_tokyo_weili::wheel_planner wheel_msg;

    void wait_callback(const wheel_tokyo_weili::waitforidle &msg);
    void msg_init();
    bool waitforidle;
    uint8_t direction;

public:
    third_level(const ros::NodeHandle &nh);
    void init_pubsub();
    void robot_move(uint8_t direction, int distance);
    void robot_wait();
    void robot_far(uint8_t dir);
};