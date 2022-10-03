#ifndef _ROS_wheel_tokyo_weili_test_h
#define _ROS_wheel_tokyo_weili_test_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace wheel_tokyo_weili
{

  class test : public ros::Msg
  {
    public:
      typedef bool _test_type;
      _test_type test;

    test():
      test(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_test;
      u_test.real = this->test;
      *(outbuffer + offset + 0) = (u_test.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->test);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_test;
      u_test.base = 0;
      u_test.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->test = u_test.real;
      offset += sizeof(this->test);
     return offset;
    }

    const char * getType(){ return "wheel_tokyo_weili/test"; };
    const char * getMD5(){ return "53f660718d381cdd11604ea1445a3cc7"; };

  };

}
#endif
