#ifndef _ROS_dynamixel_control_arm_trunk_h
#define _ROS_dynamixel_control_arm_trunk_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace dynamixel_control
{

  class arm_trunk : public ros::Msg
  {
    public:
      typedef int8_t _control_type;
      _control_type control;

    arm_trunk():
      control(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int8_t real;
        uint8_t base;
      } u_control;
      u_control.real = this->control;
      *(outbuffer + offset + 0) = (u_control.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->control);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int8_t real;
        uint8_t base;
      } u_control;
      u_control.base = 0;
      u_control.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->control = u_control.real;
      offset += sizeof(this->control);
     return offset;
    }

    const char * getType(){ return "dynamixel_control/arm_trunk"; };
    const char * getMD5(){ return "a0786a4facddf607542c97ed187d5ea3"; };

  };

}
#endif
