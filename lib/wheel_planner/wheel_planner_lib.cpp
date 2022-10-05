#include "wheel_planner/wheel_planner.hpp"

wheel_planner::wheel_planner(const ros::NodeHandle &encoder_nh, const ros::NodeHandle &planner_nh, const ros::NodeHandle &wheelCtrl_nh)
    :   planner_nh(planner_nh), encoder_nh(encoder_nh), wheelCtrl_nh(wheelCtrl_nh)
{
    
    ROS_INFO("wheel_planner constructed");
}

void wheel_planner::init_pubsub()
{
    pub = wheelCtrl_nh.advertise<geometry_msgs::Twist>("/cmd_vel", 1);
    encoder_sub = encoder_nh.subscribe("/wheel/distance", 1, &wheel_planner::encoder_callback, this);
    planner_sub = planner_nh.subscribe("/wheel/planner", 1 ,&wheel_planner::planner_callback, this);
    
}

void wheel_planner::encoder_callback(const wheel_tokyo_weili::encoder &msg)
{
    this->encRobot_x = msg.robot_distance[0];
    this->encRobot_y = msg.robot_distance[1];
    this->encRobot_z = msg.robot_distance[2];
}

void wheel_planner::planner_callback(const wheel_tokyo_weili::wheel_planner &msg)
{
    this->dis_x = msg.distance_x;
    this->dis_y = msg.distance_y;
    this->dis_z = msg.distance_z;

    this->vel_x = msg.velocity_x;
    this->vel_y = msg.velockty_y;
    this->vel_z = msg.velockty_z;
}

void wheel_planner::ctrl_method()
{
    if(dis_x=!0||dis_y!=0||dis_z!=0)
    {
        distance_processed();
    }
    if(vel_x=!0||vel_y!=0||vel_z!=0)
    {
        velocity_processed();
    }
}

void wheel_planner::distance_processed()
{
    ros::Rate loop_rate(10);
    ros::spinOnce();
    if(dis_x>0)
    {
        msg.linear.x = 0.4;
        msg.linear.y = 0;
        msg.angular.z = 0;
    }
    else if(dis_x<0)
    {
        msg.linear.x = -0.4;
        msg.linear.y = 0;
        msg.angular.z = 0;
    }
    while(fabs(encRobot_x) > fabs(dis_x))
    {
        pub.publish(msg);
        ros::spinOnce();
        loop_rate.sleep();
    }
    
    if(dis_y>0)
    {
        msg.linear.x = 0;
        msg.linear.y = 0.4;
        msg.angular.z = 0;
    }
    else if(dis_y<0)
    {
        msg.linear.x = 0;
        msg.linear.y = -0.4;
        msg.angular.z = 0;
    }
    while(fabs(encRobot_y) > fabs(dis_y))
    {
        pub.publish(msg);
        ros::spinOnce();
        loop_rate.sleep();
    }

    if(dis_z>0)
    {
        msg.linear.x = 0;
        msg.linear.y = 0;
        msg.angular.z = 1;
    }
    else if(dis_z<0)
    {
        msg.linear.x = 0;
        msg.linear.y = 0;
        msg.angular.z = 1;
    }
    while(fabs(encRobot_z) > fabs(dis_z))
    {
        pub.publish(msg);
        ros::spinOnce();
        loop_rate.sleep();
    }
}

void wheel_planner::velocity_processed()
{
    ros::Rate loop_rate(10);
    while(vel_x!=0||vel_y!=0||vel_z!=0)
    {
        msg.linear.x = vel_x;
        msg.linear.y = vel_y;
        msg.angular.z = vel_z;
        pub.publish(msg);
        ros::spinOnce();
        loop_rate.sleep();
    }
}