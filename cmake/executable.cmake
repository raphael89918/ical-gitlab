add_executable(test_control_node src/test/test.cpp)

add_executable(keyCtrl_node src/keyCtrl/keyCtrl.cpp)

add_executable(motorCtrl_node src/motorCtrl/motorCtrl.cpp)

add_executable(joystick_node src/joystick/joystick.cpp)

add_executable(encoderCounter_node src/encoderCounter/encoderCounter.cpp)

add_executable(wheel_planner_node src/wheel_planner/wheel_planner.cpp)

add_executable(third_level_node src/third_level/third_level.cpp)

add_executable(udp_joystick_node src/udp_joystick/udp_joystick.cpp)

add_executable(udp_motorCtrl_node src/udp_motorCtrl/udp_motorCtrl.cpp)