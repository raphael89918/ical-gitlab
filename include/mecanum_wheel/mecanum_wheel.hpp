#include <iostream>

enum WHEEL_MOVEMENT : uint8_t
{
    fl = 0,
    fr = 1,
    bl = 2,
    br = 3
};

enum ROBOT_MOVEMENT : uint8_t
{
    linear_x = 0,
    linear_y = 1,
    angular_z = 2
};

class mecanum_wheel
{
public:
    mecanum_wheel(float wheel_K, float wheel_R, float wheel_RATIO);
    float* wheel_to_robot(float wheel_fl, float wheel_fr, float wheel_bl, float wheel_br);//透過編碼器的值來推算出距離
    float* robot_to_wheel(float linear_x, float linear_y, float angular_z);//轉換成四個輪子

private:
    float wheel_k;//輪子相對於中心點的xy距離相加
    float wheel_r;//輪子的半徑
    const float wheel_pi = 3.14;
    float wheel_ratio;//減速度比
    float wheel_movement_vector[4];
    float robot_movement_vector[3];
};