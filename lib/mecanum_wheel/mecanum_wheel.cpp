#include "mecanum_wheel/mecanum_wheel.hpp"

mecanum_wheel::mecanum_wheel(float wheel_K, float wheel_R, float ratio_fl, float ratio_fr, float ratio_bl, float ratio_br)
{
    this->wheel_k = wheel_K;
    this->wheel_r = wheel_R;
    this->ratio_fl_ = ratio_fl;
    this->ratio_fr_ = ratio_fr;
    this->ratio_bl_ = ratio_bl;
    this->ratio_br_ = ratio_br;
    wheel_movement_vector.fill(0);
    robot_movement_vector.fill(0);
}

std::array<float, 3> mecanum_wheel::wheel_to_robot(float wheel_fl, float wheel_fr, float wheel_bl, float wheel_br)
{
    robot_movement_vector[linear_x] = -(wheel_fl + wheel_br + wheel_fr + wheel_bl)/4;
    robot_movement_vector[linear_y] = -(-wheel_fr + wheel_fl + wheel_br - wheel_bl)/4;
    robot_movement_vector[angular_z] = -(wheel_bl + wheel_fl - wheel_br - wheel_fr)/4;

    return robot_movement_vector;
}

std::array<float, 4> mecanum_wheel::robot_to_wheel(float linear_x, float linear_y, float angular_z)
{
    //轉換成四個輪子的值
    wheel_movement_vector[fl] = (linear_x - linear_y - wheel_k * angular_z) * ratio_fl_;
    wheel_movement_vector[bl] = (linear_x + linear_y - wheel_k * angular_z) * ratio_fr_;
    wheel_movement_vector[br] = (linear_x - linear_y + wheel_k * angular_z) * ratio_bl_;
    wheel_movement_vector[fr] = (linear_x + linear_y + wheel_k * angular_z) * ratio_br_;

    //轉換成輪子的速度rps(弧度/s)
    wheel_movement_vector[fl] = wheel_movement_vector[fl]/(2.0 * wheel_r * wheel_pi);
    wheel_movement_vector[fr] = wheel_movement_vector[fr]/(2.0 * wheel_r * wheel_pi);
    wheel_movement_vector[bl] = wheel_movement_vector[bl]/(2.0 * wheel_r * wheel_pi);
    wheel_movement_vector[br] = wheel_movement_vector[br]/(2.0 * wheel_r * wheel_pi);

    //轉換成rpm
    wheel_movement_vector[fl] = wheel_movement_vector[fl] * 60;
    wheel_movement_vector[fr] = wheel_movement_vector[fr] * 60;
    wheel_movement_vector[bl] = wheel_movement_vector[bl] * 60;
    wheel_movement_vector[br] = wheel_movement_vector[br] * 60;

    return wheel_movement_vector;
}
