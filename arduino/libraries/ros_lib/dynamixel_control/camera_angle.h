#ifndef _ROS_dynamixel_control_camera_angle_h
#define _ROS_dynamixel_control_camera_angle_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace dynamixel_control
{

  class camera_angle : public ros::Msg
  {
    public:
      typedef int8_t _angle_type;
      _angle_type angle;

    camera_angle():
      angle(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int8_t real;
        uint8_t base;
      } u_angle;
      u_angle.real = this->angle;
      *(outbuffer + offset + 0) = (u_angle.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->angle);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int8_t real;
        uint8_t base;
      } u_angle;
      u_angle.base = 0;
      u_angle.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->angle = u_angle.real;
      offset += sizeof(this->angle);
     return offset;
    }

    const char * getType(){ return "dynamixel_control/camera_angle"; };
    const char * getMD5(){ return "fbb56a2fe56ac238b720fd3b47d0f11c"; };

  };

}
#endif
