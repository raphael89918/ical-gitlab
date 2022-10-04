#ifndef _ROS_wheel_tokyo_weili_wheel_planner_h
#define _ROS_wheel_tokyo_weili_wheel_planner_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace wheel_tokyo_weili
{

  class wheel_planner : public ros::Msg
  {
    public:
      typedef bool _encoder_reset_type;
      _encoder_reset_type encoder_reset;
      typedef int32_t _dis_wheel_type;
      _dis_wheel_type dis_wheel;
      typedef float _vel_wheel_type;
      _vel_wheel_type vel_wheel;

    wheel_planner():
      encoder_reset(0),
      dis_wheel(0),
      vel_wheel(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_encoder_reset;
      u_encoder_reset.real = this->encoder_reset;
      *(outbuffer + offset + 0) = (u_encoder_reset.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->encoder_reset);
      union {
        int32_t real;
        uint32_t base;
      } u_dis_wheel;
      u_dis_wheel.real = this->dis_wheel;
      *(outbuffer + offset + 0) = (u_dis_wheel.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_dis_wheel.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_dis_wheel.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_dis_wheel.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->dis_wheel);
      union {
        float real;
        uint32_t base;
      } u_vel_wheel;
      u_vel_wheel.real = this->vel_wheel;
      *(outbuffer + offset + 0) = (u_vel_wheel.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_vel_wheel.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_vel_wheel.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_vel_wheel.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->vel_wheel);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_encoder_reset;
      u_encoder_reset.base = 0;
      u_encoder_reset.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->encoder_reset = u_encoder_reset.real;
      offset += sizeof(this->encoder_reset);
      union {
        int32_t real;
        uint32_t base;
      } u_dis_wheel;
      u_dis_wheel.base = 0;
      u_dis_wheel.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_dis_wheel.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_dis_wheel.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_dis_wheel.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->dis_wheel = u_dis_wheel.real;
      offset += sizeof(this->dis_wheel);
      union {
        float real;
        uint32_t base;
      } u_vel_wheel;
      u_vel_wheel.base = 0;
      u_vel_wheel.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_vel_wheel.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_vel_wheel.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_vel_wheel.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->vel_wheel = u_vel_wheel.real;
      offset += sizeof(this->vel_wheel);
     return offset;
    }

    const char * getType(){ return "wheel_tokyo_weili/wheel_planner"; };
    const char * getMD5(){ return "80944dc86c334d7f4e9973e5d98c5bca"; };

  };

}
#endif
