ARDUINO_DIR = $(HOME)/api/arduino-1.8.19/
ARDMK_DIR = $(realpath ../Arduino-Makefile)

USER_LIB_PATH := $(realpath ../libraries)
ARDUINO_LIB_PATH := $(realpath ../libraries)
BOARD_TAG    = nano_33_iot

ALTERNTE_CORE_PATH = $(realpath ../libraries/ArduinoCore-samd)

#ALTERNTE_CORE_PATH = $(HOME)/.arduino15/packages/arduino/hardware/samd/1.8.13

MONITOR_PORT = /dev/ttyACM1
MNITOR_BAUDRATE = 57600
ARDUINO_SKETCHBOOK := $(realpath ../libraries)
CXXFLAGS_STD = -std=gnu++14

ARDUINO_LIBS += ros_lib

include $(ARDMK_DIR)/Sam.mk
