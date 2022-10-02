ARDUINO_DIR = $(HOME)/api/arduino-1.8.19
ARDMK_DIR = $(realpath ../Arduino-Makefile)

USER_LIB_PATH := $(realpath ../libraries)
ARDUINO_LIB_PATH := $(realpath ../libraries)
BOARD_TAG   = nano_33_iot

#ARDUINO_PACKAGE_DIR = $(realpath ../Arduino-Makefile)
ARDUINO_PACKAGE_DIR = $(HOME)/.arduino15/packages

MONITOR_PORT = /dev/ttyACM1
MNITOR_BAUDRATE = 57600
ARDUINO_SKETCHBOOK := $(realpath ../libraries)
CXXFLAGS_STD = -std=gnu++14

ARDUINO_LIBS += ros_lib

include $(ARDMK_DIR)/Sam.mk
