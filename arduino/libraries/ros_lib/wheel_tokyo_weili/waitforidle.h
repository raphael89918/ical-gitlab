#ifndef _ROS_wheel_tokyo_weili_waitforidle_h
#define _ROS_wheel_tokyo_weili_waitforidle_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace wheel_tokyo_weili
{

  class waitforidle : public ros::Msg
  {
    public:
      typedef bool _wait_type;
      _wait_type wait;

    waitforidle():
      wait(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_wait;
      u_wait.real = this->wait;
      *(outbuffer + offset + 0) = (u_wait.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->wait);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_wait;
      u_wait.base = 0;
      u_wait.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->wait = u_wait.real;
      offset += sizeof(this->wait);
     return offset;
    }

    const char * getType(){ return "wheel_tokyo_weili/waitforidle"; };
    const char * getMD5(){ return "6dc166bbd80d5d4bf7925bea15c27be3"; };

  };

}
#endif
