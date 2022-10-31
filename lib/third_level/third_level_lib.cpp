#include "third_level/third_level.hpp"

third_level::third_level(const ros::NodeHandle &nh) : nh(nh), direction(0)
{
    ROS_INFO("third_level constructed");
}

void third_level::init_pubsub()
{
    wheel_pub = nh.advertise<wheel_tokyo_weili::wheel_planner>("/wheel/planner", 1);
    wait_sub = nh.subscribe("/wheel/waitforidle", 1, &third_level::wait_callback, this);
    msg_init();
}

void third_level::wait_callback(const wheel_tokyo_weili::waitforidle &msg)
{
    this->waitforidle = msg.wait;
}

void third_level::robot_move(uint8_t direction, int distance)
{
    
}

void third_level::robot_far(uint8_t dir)
{
    direction = dir;
    switch(direction)
    {
        case left:
            this->wheel_msg.far_left = true;
            break;

        case right:
            this->wheel_msg.far_right = true;
            break;
        
        case front:
            this->wheel_msg.far_front = true;
            break;
    }

    wheel_pub.publish(wheel_msg);
    robot_wait();
    msg_init();
}

void third_level::robot_wait()
{
    this->waitforidle = false;
    while(this->waitforidle == false)
    {
        ros::spinOnce();
        ros::Duration(0.001).sleep();
    }
}
void third_level::msg_init()
{
    wheel_msg.distance_x = 0;
    wheel_msg.distance_y = 0;
    wheel_msg.distance_z = 0;
    wheel_msg.far_front = false;
    wheel_msg.far_left = false;
    wheel_msg.far_right = false;
    wheel_msg.velocity_x = 0;
    wheel_msg.velocity_y = 0;
    wheel_msg.velocity_z = 0;
    wheel_pub.publish(wheel_msg);
}