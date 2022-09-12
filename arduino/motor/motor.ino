#include <Arduino.h>
#include "motor_controller.hpp"

ros::NodeHandle nh;
MotorController motor_controller(nh);


void setup()
{
    nh.initNode();
    nh.subscribe(motor_controller.m_sub);

    motor_controller.set_motor_driver(MD01, 4);

    motor_controller.set_pin(FL, 2,3,4);
    motor_controller.set_pin(FR, 5,6,7);
    motor_controller.set_pin(BL, 8,9,10);
    motor_controller.set_pin(BR, 11,12,13);

    motor_controller.subscribe();

    motor_controller.stop();
}

int interval = 100;
int previousMillis = 0;

void loop()
{
    int currentMillis = millis();
    if(currentMillis - previousMillis > interval)
    {
        previousMillis = currentMillis;

        if(!motor_controller.rosConnected())
        {
            motor_controller.stop();
        }
        nh.spinOnce();
    }
}
