#include <ros/ros.h>
#include "wheel_tokyo_weili/wheel_planner.h"
#include "wheel_tokyo_weili/waitforidle.h"
#include "ros_deep_learning/alphabet.h"
#include "ros_deep_learning/alphabet_info.h"
#include "pid.hpp"

enum DIRECTION : uint8_t
{
    left = 0,
    right = 1,
    front = 2
};

enum TARGET : uint8_t
{
    T = 0,
    E = 1,
    L = 2
};

class third_level
{
private:
    ros::NodeHandle nh;
    ros::Publisher wheel_pub;
    ros::Subscriber wait_sub;
    ros::Subscriber visual_sub;
    wheel_tokyo_weili::wheel_planner wheel_msg;

    void wait_callback(const wheel_tokyo_weili::waitforidle &msg);
    void msg_init();
    bool waitforidle;
    uint8_t direction;
    void visual_callback(const ros_deep_learning::alphabet &msg);
    int T_x, E_x, L_x, C_x, F_x;
    float T_z, E_z, L_z, C_z, F_z;
    void trace_target(uint8_t first, uint8_t second, uint8_t third);
    PID pid_x, pid_z;
public:
    third_level(const ros::NodeHandle &nh);
    void init_pubsub();
    void robot_move(uint8_t direction, int distance);
    void robot_wait();
    void robot_far(uint8_t dir);
    void choose_target();
};