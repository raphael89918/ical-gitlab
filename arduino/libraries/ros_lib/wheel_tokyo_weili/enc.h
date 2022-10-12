#ifndef _ROS_wheel_tokyo_weili_enc_h
#define _ROS_wheel_tokyo_weili_enc_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace wheel_tokyo_weili
{

  class enc : public ros::Msg
  {
    public:
      int32_t wheel_value[4];

    enc():
      wheel_value()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      for( uint32_t i = 0; i < 4; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_wheel_valuei;
      u_wheel_valuei.real = this->wheel_value[i];
      *(outbuffer + offset + 0) = (u_wheel_valuei.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_wheel_valuei.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_wheel_valuei.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_wheel_valuei.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->wheel_value[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      for( uint32_t i = 0; i < 4; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_wheel_valuei;
      u_wheel_valuei.base = 0;
      u_wheel_valuei.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_wheel_valuei.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_wheel_valuei.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_wheel_valuei.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->wheel_value[i] = u_wheel_valuei.real;
      offset += sizeof(this->wheel_value[i]);
      }
     return offset;
    }

    const char * getType(){ return "wheel_tokyo_weili/enc"; };
    const char * getMD5(){ return "c25e9ee1eae9e01bd9b448271d066e2a"; };

  };

}
#endif
