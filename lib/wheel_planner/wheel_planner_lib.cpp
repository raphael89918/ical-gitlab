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
    enc_pub = wheelCtrl_nh.advertise<wheel_tokyo_weili::wheel_planner>("/planner/encoder", 1);
    dyna_pub = wheelCtrl_nh.advertise<dynamixel_control::wheel_laser>("/dynamixel/wheel_laser", 1);
    arduino_motor_pub = wheelCtrl_nh.advertise<wheel_tokyo_weili::motor>("/wheel/motor", 1);

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
    far_front = false;
    laser_ul = 0;
    laser_ur = 0;
    laser_dl = 0;
    laser_dr = 0;
    wait_msg.wait = false;
}

void wheel_planner::encoder_callback(const wheel_tokyo_weili::encoder &msg)
{
    double encoder_ratio_x = 17.25;
    double encoder_ratio_y = 17.5;
    double encoder_ratio_z = 7.2;
    planner_nh.getParamCached("/wheel/encoder_ratio_x", encoder_ratio_x);
    planner_nh.getParamCached("/wheel/encoder_ratio_y", encoder_ratio_y);
    planner_nh.getParamCached("/wheel/encoder_ratio_z", encoder_ratio_z);
    this->encRobot_x = msg.robot_distance[0] / encoder_ratio_x;
    this->encRobot_y = msg.robot_distance[1] / encoder_ratio_y;
    this->encRobot_z = msg.robot_distance[2] / encoder_ratio_z;
    this->wheel_fl = msg.wheel_value[0];
    this->wheel_fr = msg.wheel_value[1];
    this->wheel_bl = msg.wheel_value[2];
    this->wheel_br = msg.wheel_value[3];
    if (this->encRobot_x || this->encRobot_y || this->encRobot_z)
    {
        ROS_INFO("msg_dist: %lf, %lf, %lf", msg.robot_distance[0], msg.robot_distance[1], msg.robot_distance[2]);
        ROS_INFO("encoder_ratio_x: %lf, %lf, %lf", encoder_ratio_x, encoder_ratio_y, encoder_ratio_z);
        ROS_INFO("encoder_robot: %lf, %lf, %lf", encRobot_x, encRobot_y, encRobot_z);
        ROS_INFO("wheel: %d, %d, %d, %d", wheel_fl, wheel_fr, wheel_bl, wheel_br);
    }
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
    this->far_front = msg.far_front;
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
    // std::cout << "ctrl_method" << std::endl;
    init_encoder();
    state.callOne();
    plan.callOne();
    temp_x = dis_x;
    temp_y = dis_y;
    temp_z = dis_z;

    if (temp_x != 0)
    {
        continue_robot();
        distance_processed_x();
        std::cout << "fl" << wheel_fl << " fr" << wheel_fr << " bl" << wheel_bl << " br" << wheel_br << std::endl;
        wait_robot();
    }
    if (temp_y != 0)
    {
        continue_robot();
        distance_processed_y();
        std::cout << "fl" << wheel_fl << " fr" << wheel_fr << " bl" << wheel_bl << " br" << wheel_br << std::endl;
        wait_robot();
    }
    if (temp_z != 0)
    {
        continue_robot();
        distance_processed_z();
        std::cout << "fl" << wheel_fl << " fr" << wheel_fr << " bl" << wheel_bl << " br" << wheel_br << std::endl;
        wait_robot();
    }

    if (far_left == true || far_right == true || far_front == true)
    {
        continue_robot();
        dyna_msg.ctrl = true;
        dyna_pub.publish(dyna_msg);
        ros::Duration(2).sleep();
        go_to_far(far_left, far_right, far_front);
        far_left = false;
        far_right = false;
        far_front = false;
        dyna_msg.ctrl = false;
        dyna_pub.publish(dyna_msg);
        ros::Duration(2).sleep();
        wait_robot();
    }

    if (vel_x != 0 || vel_y != 0 || vel_z != 0)
    {
        continue_robot();
        velocity_processed();
        wait_robot();
    }
    wait_msg.wait = true;
    wait_pub.publish(wait_msg);
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
        pub.publish(msg);
        state.callOne();
        loop_rate.sleep();
    }
    dis_x = 0;
    stop_robot();
}

void wheel_planner::distance_processed_y()
{
    // std::cout << "distance_processed_y" << std::endl;
    ros::Rate loop_rate(100);
    state.callOne();
    while (fabs(encRobot_y) < fabs(temp_y))
    {
        if (temp_y > 0)
        {
            msg.linear.x = 0;
            msg.linear.y = 0.4;
            msg.angular.z = 0;
        }
        if (temp_y < 0)
        {
            msg.linear.x = 0;
            msg.linear.y = -0.4;
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
    // std::cout << "distance_processed_z" << std::endl;
    ros::Rate loop_rate(100);
    state.callOne();
    while (fabs(encRobot_z) < fabs(temp_z))
    {
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
    // std::cout << "velocity_processed" << std::endl;
    ros::Rate loop_rate(100);
    while (vel_x != 0 || vel_y != 0 || vel_z != 0)
    {
        msg.linear.x = vel_x;
        msg.linear.y = vel_y;
        msg.angular.z = vel_z;
        pub.publish(msg);
        plan.callOne();
        loop_rate.sleep();
    }

    stop_robot();
}

void wheel_planner::init_encoder()
{
    enc_msg.encoder_reset = true;
    state.callOne();
    enc_pub.publish(enc_msg);
}

void wheel_planner::stop_robot()
{
    msg.linear.x = 0;
    msg.linear.y = 0;
    msg.angular.z = 0;
    ROS_INFO("stop");
    pub.publish(msg);
}

void wheel_planner::go_to_far(bool left, bool right, bool front)
{
    if (left == true)
    {
        msg.linear.x = 0;
        msg.linear.y = -0.3;
        msg.angular.z = 0;
        ros::Rate loop_rate(100);
        state.callOne();
        ros::Duration(0.5).sleep();
        while (laser_dl <= 130)
        {
            state.callOne();
            pub.publish(msg);
            loop_rate.sleep();
        }
        stop_robot();
    }
    if (right == true)
    {
        msg.linear.x = 0;
        msg.linear.y = 0.3;
        msg.angular.z = 0;
        ros::Rate loop_rate(100);
        state.callOne();
        ros::Duration(0.5).sleep();
        while (laser_dr <= 130)
        {
            state.callOne();
            pub.publish(msg);
            loop_rate.sleep();
        }
        stop_robot();
    }
    if (front == true)
    {
        msg.linear.x = 0.3;
        msg.linear.y = 0;
        msg.angular.z = 0;
        ros::Rate loop_rate(100);
        state.callOne();
        ros::Duration(0.5).sleep();
        while (laser_ul >= 100 || laser_ur >= 100)
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
    wait_msg.wait = true;
    wait_pub.publish(wait_msg);
}

void wheel_planner::continue_robot()
{
    wait_msg.wait = false;
    wait_pub.publish(wait_msg);
}
