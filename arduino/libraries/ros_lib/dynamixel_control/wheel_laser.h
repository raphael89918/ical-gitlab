#ifndef _ROS_dynamixel_control_wheel_laser_h
#define _ROS_dynamixel_control_wheel_laser_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace dynamixel_control
{

  class wheel_laser : public ros::Msg
  {
    public:
      typedef bool _ctrl_type;
      _ctrl_type ctrl;

    wheel_laser():
      ctrl(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_ctrl;
      u_ctrl.real = this->ctrl;
      *(outbuffer + offset + 0) = (u_ctrl.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->ctrl);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_ctrl;
      u_ctrl.base = 0;
      u_ctrl.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->ctrl = u_ctrl.real;
      offset += sizeof(this->ctrl);
     return offset;
    }

    const char * getType(){ return "dynamixel_control/wheel_laser"; };
    const char * getMD5(){ return "dcfc4e2783aec8736924bd6a69268950"; };

  };

}
#endif
