#include <ros/ros.h>
#include "wheel_tokyo_weili/wheel_planner.h"
#include "wheel_tokyo_weili/waitforidle.h"
#include <ground_color/GroundColor.h>

enum DIRECTION
{
    left = 0,
    right = 1,
    front = 2
};

enum Color
{
    GROUND_RED = 0,
    GROUND_GREEN = 1,
    GROUND_BLUE = 2,
    COMBINED_BLACK = 3,
    CONBINED_BLUE = 4
};

class third_level
{
private:
    ros::NodeHandle nh;
    ros::Publisher wheel_pub;
    ros::Subscriber wait_sub;
    ros::Subscriber color_sub;
    wheel_tokyo_weili::wheel_planner wheel_msg;

    void wait_callback(const wheel_tokyo_weili::waitforidle &msg);
    void msg_init();
    bool waitforidle;
    uint8_t direction;
    void ground_color_callback(const ground_color::GroundColor &color_msg);
    int target;
public:
    third_level(const ros::NodeHandle &nh);
    void init_pubsub();
    void robot_move(uint8_t direction, int distance);
    void robot_wait();
    void robot_far(uint8_t dir);
    void trace_target();
};