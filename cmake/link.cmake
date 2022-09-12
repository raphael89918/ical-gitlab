target_link_libraries(test_node
test_lib
${OpenCV_LIBS}
${catkin_LIBRARIES}
)

target_link_libraries(keyCtrl_node
conio
${catkin_LIBRARIES}
)

target_link_libraries(motorCtrl_node
motorCtrl_lib
${catkin_LIBRARIES}
)



target_link_libraries(joystick_node
${catkin_LIBRARIES}
)
