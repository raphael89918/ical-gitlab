#ifndef _ROS_wheel_tokyo_weili_encoder_h
#define _ROS_wheel_tokyo_weili_encoder_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace wheel_tokyo_weili
{

  class encoder : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      int8_t value[4];

    encoder():
      header(),
      value()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      for( uint32_t i = 0; i < 4; i++){
      union {
        int8_t real;
        uint8_t base;
      } u_valuei;
      u_valuei.real = this->value[i];
      *(outbuffer + offset + 0) = (u_valuei.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->value[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      for( uint32_t i = 0; i < 4; i++){
      union {
        int8_t real;
        uint8_t base;
      } u_valuei;
      u_valuei.base = 0;
      u_valuei.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->value[i] = u_valuei.real;
      offset += sizeof(this->value[i]);
      }
     return offset;
    }

    virtual const char * getType() override { return "wheel_tokyo_weili/encoder"; };
    virtual const char * getMD5() override { return "a45c6596bc958aaf9bcea86d06c447fd"; };

  };

}
#endif
