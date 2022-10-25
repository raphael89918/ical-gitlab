#include "wheel_planner/wheel_planner.hpp"
#include <iostream>

wheel_planner::wheel_planner(const ros::NodeHandle &encoder_nh, const ros::NodeHandle &planner_nh, const ros::NodeHandle &wheelCtrl_nh, const ros::NodeHandle &laser_nh)
    : planner_nh(planner_nh), encoder_nh(encoder_nh), wheelCtrl_nh(wheelCtrl_nh), laser_nh(laser_nh)
{

    ROS_INFO("wheel_planner constructed");
}

void wheel_planner::init_pubsub()
{
    encoder_nh.setCallbackQueue(&state);
    laser_nh.setCallbackQueue(&state);
    planner_nh.setCallbackQueue(&plan);

    wait_pub = wheelCtrl_nh.advertise<wheel_tokyo_weili::waitforidle>("/wheel/waitforidle", 1);
    pub = wheelCtrl_nh.advertise<geometry_msgs::Twist>("/cmd_vel", 1);
    enc_pub = wheelCtrl_nh.advertise<wheel_tokyo_weili::wheel_planner>("/planner/encoder",1);
    encoder_sub = encoder_nh.subscribe("/wheel/distance", 1, &wheel_planner::encoder_callback, this);
    planner_sub = planner_nh.subscribe("/wheel/planner", 1, &wheel_planner::planner_callback, this);
    laser_sub = laser_nh.subscribe("/laser", 1, &wheel_planner::laser_callback, this);

    dis_x = 0;
    dis_y = 0;
    dis_z = 0;
    encRobot_x = 0;
    encRobot_y = 0;
    encRobot_z = 0;
    vel_x = 0;
    vel_y = 0;
    vel_z = 0;
    far_left = false;
    far_right = false;
    laser_ul = 0;
    laser_ur = 0;
    laser_dl = 0;
    laser_dr = 0;
    wait_msg.waitforidle = 0;
}

void wheel_planner::encoder_callback(const wheel_tokyo_weili::encoder &msg)
{
    this->encRobot_x = msg.robot_distance[0] / 21.2;
    this->encRobot_y = msg.robot_distance[1] / 20.03;
    this->encRobot_z = msg.robot_distance[2] / 7;
    std::cout << "encoder_callback" << std::endl;
}

void wheel_planner::planner_callback(const wheel_tokyo_weili::wheel_planner &msg)
{
    this->dis_x = msg.distance_x;
    this->dis_y = msg.distance_y;
    this->dis_z = msg.distance_z;

    this->vel_x = msg.velocity_x;
    this->vel_y = msg.velocity_y;
    this->vel_z = msg.velocity_z;

    this->far_left = msg.far_left;
    this->far_right = msg.far_right;

    std::cout << "planner_callback" << std::endl;
}

void wheel_planner::laser_callback(const gpio::Laser &msg)
{
    this->laser_ul = msg.distance_UL;
    this->laser_dl = msg.distance_LL;
    this->laser_ur = msg.distance_UR;
    this->laser_dr = msg.distance_LR;
}

void wheel_planner::ctrl_method()
{
    std::cout << "ctrl_method" << std::endl;
    init_encoder();
    state.callOne();
    plan.callOne();
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

    if(far_left == true || far_right == true)
    {
        go_to_far(far_left, far_right);
    }
    wait_msg.waitforidle = false;
    pub.publish(wait_msg);
}

void wheel_planner::distance_processed_x()
{
    // std::cout << "distance_processed_x" << std::endl;
    ros::Rate loop_rate(100);
    state.callOne();
    while (fabs(encRobot_x) < fabs(temp_x))
    {
        if (temp_x > 0)
        {
            msg.linear.x = 0.4;
            msg.linear.y = 0;
            msg.angular.z = 0;
        }
        if (temp_x < 0)
        {
            msg.linear.x = -0.4;
            msg.linear.y = 0;
            msg.angular.z = 0;
        }

        // std::cout << "temp_x" << temp_x << std::endl;
        // std::cout << "encRobt_x" << encRobot_x << std::endl;
        pub.publish(msg);
        state.callOne();
        loop_rate.sleep();
    }
    dis_x = 0;
    stop_robot();
}

void wheel_planner::distance_processed_y()
{
    std::cout << "distance_processed_y" << std::endl;
    ros::Rate loop_rate(100);
    state.callOne();
    while (fabs(encRobot_y) < fabs(temp_y))
    {
        // std::cout << "temp_y" << temp_y << std::endl;
        // std::cout << "encRobt_y" << encRobot_y << std::endl;
        if (temp_y > 0)
        {
            msg.linear.x = 0;
            msg.linear.y = -0.4;
            msg.angular.z = 0;

        }
        if (temp_y < 0)
        {
            msg.linear.x = 0;
            msg.linear.y = 0.4;
            msg.angular.z = 0;
        }
        pub.publish(msg);
        state.callOne();
        loop_rate.sleep();
    }
    dis_y = 0;
    stop_robot();
}

void wheel_planner::distance_processed_z()
{
    std::cout << "distance_processed_z" << std::endl;
    ros::Rate loop_rate(100);
    state.callOne();
    while (fabs(encRobot_z) < fabs(temp_z))
    {
        // std::cout << "temp_y" << temp_y << std::endl;
        // std::cout << "encRobt_y" << encRobot_y << std::endl;
        if (temp_z > 0)
        {
            msg.linear.x = 0;
            msg.linear.y = 0;
            msg.angular.z = -1;

        }
        if (temp_z < 0)
        {
            msg.linear.x = 0;
            msg.linear.y = 0;
            msg.angular.z = 1;
        }
        pub.publish(msg);
        state.callOne();
        loop_rate.sleep();
    }
    dis_z = 0;
    stop_robot();
}

void wheel_planner::velocity_processed()
{
    std::cout << "velocity_processed" << std::endl;
    ros::Rate loop_rate(100);
    while (vel_x != 0 || vel_y != 0 || vel_z != 0)
    {
        msg.linear.x = vel_x;
        msg.linear.y = vel_y;
        msg.angular.z = vel_z;
        pub.publish(msg);
        state.callOne();
        loop_rate.sleep();
    }

    stop_robot();
}

void wheel_planner::init_encoder()
{
    enc_msg.encoder_reset = true;
    enc_pub.publish(enc_msg);
}

void wheel_planner::stop_robot()
{
    msg.linear.x = 0;
    msg.linear.y = 0;
    msg.angular.z = 0;
    pub.publish(msg);
    wait_robot();
}

void wheel_planner::go_to_far(bool left, bool right)
{
    if(left == true && right != true)
    {
        msg.linear.x = 0;
        msg.linear.y = -0.5;
        msg.angular.z = 0;
        ros::Rate loop_rate(100);
        while(laser_dl <= 50) // need to test
        {
            state.callOne();
            pub.publish(msg);
            loop_rate.sleep();
        }
        stop_robot();
    }
    if(left != true && right == true)
    {
        msg.linear.x = 0;
        msg.linear.y = 0.5;
        msg.angular.z = 0;
        ros::Rate loop_rate(100);
        while(laser_dr <= 50) // neet to test
        {
            state.callOne();
            pub.publish(msg);
            loop_rate.sleep();
        }
        stop_robot();
    }
}

void wheel_planner::wait_robot()
{
    ros::Duration(0.5).sleep();
    wait_msg.waitforidle = true;
    pub.publish(wait_msg);
}