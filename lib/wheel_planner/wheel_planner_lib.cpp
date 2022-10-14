#include "wheel_planner/wheel_planner.hpp"
#include <iostream>
wheel_planner::wheel_planner(const ros::NodeHandle &encoder_nh, const ros::NodeHandle &planner_nh, const ros::NodeHandle &wheelCtrl_nh)
    : planner_nh(planner_nh), encoder_nh(encoder_nh), wheelCtrl_nh(wheelCtrl_nh)
{

    ROS_INFO("wheel_planner constructed");
}

void wheel_planner::init_pubsub()
{
    pub = wheelCtrl_nh.advertise<geometry_msgs::Twist>("/cmd_vel", 1);
    encoder_sub = encoder_nh.subscribe("/wheel/distance", 1, &wheel_planner::encoder_callback, this);
    planner_sub = planner_nh.subscribe("/wheel/planner", 1, &wheel_planner::planner_callback, this);
}

void wheel_planner::encoder_callback(const wheel_tokyo_weili::encoder &msg)
{
    this->encRobot_x = msg.robot_distance[0] / 21.2;
    this->encRobot_y = msg.robot_distance[1] / 20.03;
    this->encRobot_z = msg.robot_distance[2] / 7;
    //std::cout << "encRobot" << encRobot_x << std::endl;
}

void wheel_planner::planner_callback(const wheel_tokyo_weili::wheel_planner &msg)
{
    this->dis_x = msg.distance_x;
    this->dis_y = msg.distance_y;
    this->dis_z = msg.distance_z;

    this->vel_x = msg.velocity_x;
    this->vel_y = msg.velocity_y;
    this->vel_z = msg.velocity_z;

    //std::cout << dis_x << std::endl;
}

void wheel_planner::ctrl_method()
{
    temp_x = dis_x;
    temp_y = dis_y;
    temp_z = dis_z;
    
    if(temp_x != 0)
    {
        distance_processed_x();
    }
    if(temp_y != 0)
    {
        distance_processed_y();
    }
    if(temp_z != 0)
    {
        distance_processed_z();
    }
}

void wheel_planner::distance_processed_x()
{
    ros::Rate loop_rate(100);
    ros::spinOnce();
    while (fabs(encRobot_x) < fabs(temp_x))
    {
        // std::cout << "temp_x" << temp_x << std::endl;
        // std::cout << "encRobt_x" << encRobot_x << std::endl;
        if (temp_x > 0)
        {
            msg.linear.x = 0.5;
            msg.linear.y = 0;
            msg.angular.z = 0;
            
        }
        if (temp_x < 0)
        {
            msg.linear.x = -0.5;
            msg.linear.y = 0;
            msg.angular.z = 0;
        }
        pub.publish(msg);
        ros::spinOnce();
        loop_rate.sleep();
    }
    dis_x = 0;
    msg.linear.x = 0;
    msg.linear.y = 0;
    msg.angular.z = 0;
    pub.publish(msg);
    ros::spinOnce();
    temp_z = encRobot_z;
    distance_processed_z();
}

void wheel_planner::distance_processed_y()
{
    ros::Rate loop_rate(100);
    ros::spinOnce();
    while (fabs(encRobot_y) < fabs(temp_y))
    {
        // std::cout << "temp_y" << temp_y << std::endl;
        // std::cout << "encRobt_y" << encRobot_y << std::endl;
        if (temp_y > 0)
        {
            msg.linear.x = 0;
            msg.linear.y = 0.5;
            msg.angular.z = 0;
            
        }
        if (temp_y < 0)
        {
            msg.linear.x = 0;
            msg.linear.y = -0.5;
            msg.angular.z = 0;
        }
        pub.publish(msg);
        ros::spinOnce();
        loop_rate.sleep();
    }
    dis_y = 0;
    msg.linear.x = 0;
    msg.linear.y = 0;
    msg.angular.z = 0;
    pub.publish(msg);
    ros::spinOnce();
    temp_z = encRobot_z;
    distance_processed_z();
}

void wheel_planner::distance_processed_z()
{
    ros::Rate loop_rate(100);
    ros::spinOnce();
    while (fabs(encRobot_z) < fabs(temp_z))
    {
        // std::cout << "temp_y" << temp_y << std::endl;
        // std::cout << "encRobt_y" << encRobot_y << std::endl;
        if (temp_z > 0)
        {
            msg.linear.x = 0;
            msg.linear.y = 0;
            msg.angular.z = 1;
            
        }
        if (temp_z < 0)
        {
            msg.linear.x = 0;
            msg.linear.y = 0;
            msg.angular.z = -1;
        }
        pub.publish(msg);
        ros::spinOnce();
        loop_rate.sleep();
    }
    dis_z = 0;
    msg.linear.x = 0;
    msg.linear.y = 0;
    msg.angular.z = 0;
    pub.publish(msg);
}

void wheel_planner::velocity_processed()
{
    ros::Rate loop_rate(10);
    while (vel_x != 0 || vel_y != 0 || vel_z != 0)
    {
        msg.linear.x = vel_x;
        msg.linear.y = vel_y;
        msg.angular.z = vel_z;
        pub.publish(msg);
        ros::spinOnce();
        loop_rate.sleep();
    }
}
