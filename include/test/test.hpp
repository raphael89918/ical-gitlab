#include "ros/ros.h"
#include "std_msgs/Bool.h"
#include <cstdlib>
#include "wheel_planner/wheel_planner.hpp"

class Test
{
public:
    Test();
    ~Test();
    void print(std::string str);

private:
    int a;
    int b;
    int c;
};

