#include "first_level/first_level.hpp"

third_level::third_level(const ros::NodeHandle &nh) : nh(nh), direction(0), pid_x(0.02, 0.01, 0, 0), pid_z(0.1, 0.05, 0, 0)
{
    ROS_INFO("third_level constructed");
}

void third_level::init_pubsub()
{
    wheel_pub = nh.advertise<wheel_tokyo_weili::wheel_planner>("/wheel/planner", 1);
    wait_sub = nh.subscribe("/wheel/waitforidle", 1, &third_level::wait_callback, this);
    visual_sub = nh.subscribe("/alphabet", 1, &third_level::visual_callback, this);
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
    switch (direction)
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
    while (this->waitforidle == false)
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

void third_level::visual_callback(const ros_deep_learning::alphabet &msg)
{
    T_x = msg.T.x;
    E_x = msg.E.x;
    L_x = msg.L.x;
    C_x = msg.C.x;
    F_x = msg.F.x;

    T_z = msg.T.z;
    E_z = msg.E.z;
    L_z = msg.L.z;
    C_z = msg.C.z;
    F_z = msg.F.z;
}

void third_level::choose_target()
{
    ros::spinOnce();
    if (T_x == 0 && E_x == 0 && L_x == 0)
    {
        ROS_INFO("no TEL target");
        return;
    }
    if (T_z >= E_z && T_z >= L_z)
    {
        if (E_z == std::min(E_z, L_z))
        {
            trace_target(T, E, L);
        }
        if (L_z == std::min(E_z, L_z))
        {
            trace_target(T, L, E);
        }
    }
    if (E_z >= T_z && E_z >= L_z)
    {
        if (T_z == std::min(T_z, L_z))
        {
            trace_target(E, T, L);
        }
        if (L_z == std::min(T_z, L_z))
        {
            trace_target(E, L, T);
        }
    }
    if (L_z >= E_z && L_z >= T_z)
    {
        if (T_z == std::min(E_z, T_z))
        {
            trace_target(L, T, E);
        }
        if (E_z == std::min(E_z, T_z))
        {
            trace_target(L, E, T);
        }
    }
    robot_wait();
    msg_init();
}

void third_level::trace_target(uint8_t first, uint8_t second, uint8_t third)
{
    int temp[3] = {first, second, third};
    float center_z = 25;
    int center_x = 640;
    for (int i = 0; i < 3; i++)
    {
        switch (temp[i])
        {
        case T:
            ROS_INFO("trace T");
            ros::spinOnce();
            while(T_z>=27 || T_z <=23)
            {
                int target = T_z - center_z;
                wheel_msg.velocity_x = pid_z.pidCtrl(target,0);
                if(wheel_msg.velocity_x >= 0.4)
                {
                    wheel_msg.velocity_x = 0.4;
                }
                ros::Duration(0.01).sleep();
                ros::spinOnce();
            }
            while(T_x >= 655 || T_x <=645)
            {
                int target = center_x - T_x;
                wheel_msg.velocity_y = pid_x.pidCtrl(target,0);
                if(wheel_msg.velocity_y >= 0.4)
                {
                    wheel_msg.velocity_y = 0.4;
                }
                ros::spinOnce();
                ros::Duration(0.01).sleep();
            }
            break;
        case E:
            ROS_INFO("trace E");
            ros::spinOnce();
            while(E_z>=27 || E_z <=23)
            {
                int target = E_z - center_z;
                wheel_msg.velocity_x = pid_z.pidCtrl(target,0);
                if(wheel_msg.velocity_x >= 0.4)
                {
                    wheel_msg.velocity_x = 0.4;
                }
                ros::Duration(0.01).sleep();
                ros::spinOnce();
            }
            while(E_x >= 655 || E_x <=645)
            {
                int target = center_x - E_x;
                wheel_msg.velocity_y = pid_x.pidCtrl(target,0);
                if(wheel_msg.velocity_y >= 0.4)
                {
                    wheel_msg.velocity_y = 0.4;
                }
                ros::spinOnce();
                ros::Duration(0.01).sleep();
            }
            break;
        case L:
            ROS_INFO("trace L");
            ros::spinOnce();
            while(L_z>=27 || L_z <=23)
            {
                int target = L_z - center_z;
                wheel_msg.velocity_x = pid_z.pidCtrl(target,0);
                if(wheel_msg.velocity_x >= 0.4)
                {
                    wheel_msg.velocity_x = 0.4;
                }
                ros::Duration(0.01).sleep();
                ros::spinOnce();
            }
            while(T_x >= 655 || T_x <=645)
            {
                int target = center_x - T_x;
                wheel_msg.velocity_y = pid_x.pidCtrl(target,0);
                if(wheel_msg.velocity_y >= 0.4)
                {
                    wheel_msg.velocity_y = 0.4;
                }
                ros::spinOnce();
                ros::Duration(0.01).sleep();
            }
            break;
        }
    }
}

void third_level::robot_move(uint8_t direction, int distance)
{
    switch (direction)
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