#pragma once
//#include <Arduino.h>
#include <ros.h>
#include <wheel_tokyo_weili/motor.h>

enum MOTOR_DRIVER
{
    TB6612_FNG = 0,
    MD01 = 1,
    CUSTOM = 2
};

enum TB66FNG_INPUT_PIN_TYPE
{
    AIN1 = 0,
    AIN2 = 1,
    PWMA = 2,
    BIN1 = 3,
    BIN2 = 4,
    PWMB = 5,
    STBY = 6
};

enum MD01_INPUT_PIN_TYPE
{
    DIR = 0,
    PWM = 1,
    SLP = 2
};

enum MOTOR_POSITION
{
    FL = 0,
    FR = 1,
    BL = 2,
    BR = 3
};

enum MOTOR_POSITION_PAIR
{
    FRONT_PAIR = 0,
    BACK_PAIR = 1
};

enum ROTATION
{
    FRONT = 0,
    BACK = 1
};

typedef struct motor_dirver_data
{
    uint8_t pin[8];
    uint8_t value[8];
} MotorDriver;

class MotorController
{
public:
    MotorController(ros::NodeHandle &nh);

    ~MotorController();

    void set_motor_driver(uint8_t MOTOR_DRIVER_type, uint8_t MOTOR_DRIVER_num);

    void set_pin(uint8_t motor_pair,
                 uint8_t ain1, uint8_t ain2, uint8_t pwma,
                 uint8_t bin1, uint8_t bin2, uint8_t pwmb,
                 uint8_t stby);

    void set_pin(uint8_t motor_position,
                 uint8_t dir, uint8_t pwm, uint8_t slp);

    void flip_rotation(uint8_t MOTOR_POSITION);

    void pwm_log(const wheel_tokyo_weili::motor &msg);

    void subscribe();

    void spin_once();

    ros::Subscriber<wheel_tokyo_weili::motor, MotorController> m_sub;

    void stop();
    bool rosConnected();
private:
    MotorDriver m_motor_driver[4];
    bool m_motor_flip_rotation[4];

    uint8_t m_driver_id;
    uint8_t m_driver_num;

    ros::NodeHandle m_nh;

    void motor_callback(const wheel_tokyo_weili::motor &msg);
    void update_wheel(const wheel_tokyo_weili::motor &msg);
    void control_wheel(const wheel_tokyo_weili::motor &msg);
};
