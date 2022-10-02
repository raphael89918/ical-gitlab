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
      int8_t wheel_value[4];
      float robot_distance[3];

    encoder():
      header(),
      wheel_value(),
      robot_distance()
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
      } u_wheel_valuei;
      u_wheel_valuei.real = this->wheel_value[i];
      *(outbuffer + offset + 0) = (u_wheel_valuei.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->wheel_value[i]);
      }
      for( uint32_t i = 0; i < 3; i++){
      union {
        float real;
        uint32_t base;
      } u_robot_distancei;
      u_robot_distancei.real = this->robot_distance[i];
      *(outbuffer + offset + 0) = (u_robot_distancei.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_robot_distancei.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_robot_distancei.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_robot_distancei.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->robot_distance[i]);
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
      } u_wheel_valuei;
      u_wheel_valuei.base = 0;
      u_wheel_valuei.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->wheel_value[i] = u_wheel_valuei.real;
      offset += sizeof(this->wheel_value[i]);
      }
      for( uint32_t i = 0; i < 3; i++){
      union {
        float real;
        uint32_t base;
      } u_robot_distancei;
      u_robot_distancei.base = 0;
      u_robot_distancei.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_robot_distancei.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_robot_distancei.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_robot_distancei.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->robot_distance[i] = u_robot_distancei.real;
      offset += sizeof(this->robot_distance[i]);
      }
     return offset;
    }

    virtual const char * getType() override { return "wheel_tokyo_weili/encoder"; };
    virtual const char * getMD5() override { return "a45c6596bc958aaf9bcea86d06c447fd"; };

  };

}
#endif
