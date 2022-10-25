ARDUINO_DIR = $(HOME)/api/arduino-1.8.19/
ARDMK_DIR = $(realpath ../Arduino-Makefile)

USER_LIB_PATH := $(realpath ../libraries)
ARDUINO_LIB_PATH := $(realpath ../libraries)

BOARD_TAG    = mega
BOARD_SUB	 = atmega2560

MONITOR_PORT = /dev/ttyACM0
MNITOR_BAUDRATE = 57600
ARDUINO_SKETCHBOOK := $(realpath ../libraries)
CXXFLAGS_STD = -std=gnu++14

#ARDUINO_LIBS += avr-libc
ARDUINO_LIBS += ros_lib
ARDUINO_LIBS += motor_controller

include $(ARDMK_DIR)/Arduino.mk
