#include "third_level/third_level.hpp"

#define xcenter 640

third_level::third_level(const ros::NodeHandle &nh) : nh(nh), direction(0)
{
    ROS_INFO("third_level constructed");
}

void third_level::init_pubsub()
{
    wheel_pub = nh.advertise<wheel_tokyo_weili::wheel_planner>("/wheel/planner", 1);
    wait_sub = nh.subscribe("/wheel/waitforidle", 1, &third_level::wait_callback, this);
    color_sub = nh.subscribe("/ground_color", 1, &third_level::ground_color_callback, this);
    msg_init();
    waitforidle = false;
}

void third_level::wait_callback(const wheel_tokyo_weili::waitforidle &msg)
{
    this->waitforidle = msg.wait;
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
    ros::Duration(0.1).sleep();
    robot_wait();
    msg_init();
}

void third_level::robot_wait()
{
    this->waitforidle = false;
    while(this->waitforidle == false)
    {
        ros::spinOnce();
        ros::Duration(0.05).sleep();
    }
    ros::Duration(1).sleep();
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
void third_level::ground_color_callback(const ground_color::GroundColor &color_msg)
{
    ROS_INFO("===================");
    ROS_INFO("I heard Red x: %d, y:%d", color_msg.rect[GROUND_RED].x_center, color_msg.rect[GROUND_RED].y_center);
    ROS_INFO("I heard Green x: %d, y:%d", color_msg.rect[GROUND_GREEN].x_center, color_msg.rect[GROUND_GREEN].y_center);
    ROS_INFO("I heard Blue x: %d, y:%d", color_msg.rect[GROUND_BLUE].x_center, color_msg.rect[GROUND_BLUE].y_center);
    ROS_INFO("I heard Combined Black x: %d, y:%d", color_msg.rect[COMBINED_BLACK].x_center, color_msg.rect[COMBINED_BLACK].y_center);
    ROS_INFO("I heard Combined Blue x: %d, y:%d", color_msg.rect[CONBINED_BLUE].x_center, color_msg.rect[CONBINED_BLUE].y_center);
    target = color_msg.rect[CONBINED_BLUE].x_center;
}


void third_level::trace_target()
{
    ros::spinOnce();
    while(abs(xcenter-target)>100)
    {
        if(target>xcenter)
        {
            wheel_msg.velocity_y = -0.4;
            ros::spinOnce();
            wheel_pub.publish(wheel_msg);
            ros::Duration(0.01).sleep();
        }
        if(target<xcenter)
        {
            wheel_msg.velocity_y = 0.4;
            ros::spinOnce();
            wheel_pub.publish(wheel_msg);
            ros::Duration(0.01).sleep();
        }
    }
    ros::Duration(0.05).sleep();
    robot_wait();
    msg_init();
}

void third_level::robot_move(uint8_t direction, int distance)
{
    switch(direction)
    {
        case left:
            wheel_msg.distance_y = -distance;
            break;

        case right:
            wheel_msg.distance_y = distance;
            break;
        
        case front:
            wheel_msg.distance_x = distance;
            break;
    }

    wheel_pub.publish(wheel_msg);
    ros::Duration(0.05).sleep();
    robot_wait();
    msg_init();
}