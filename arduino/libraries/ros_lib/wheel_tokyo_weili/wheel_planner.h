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
      typedef float _distance_x_type;
      _distance_x_type distance_x;
      typedef float _distance_y_type;
      _distance_y_type distance_y;
      typedef float _distance_z_type;
      _distance_z_type distance_z;
      typedef float _velocity_x_type;
      _velocity_x_type velocity_x;
      typedef float _velocity_y_type;
      _velocity_y_type velocity_y;
      typedef float _velocity_z_type;
      _velocity_z_type velocity_z;
      typedef bool _far_left_type;
      _far_left_type far_left;
      typedef bool _far_right_type;
      _far_right_type far_right;
      typedef bool _far_front_type;
      _far_front_type far_front;

    wheel_planner():
      encoder_reset(0),
      distance_x(0),
      distance_y(0),
      distance_z(0),
      velocity_x(0),
      velocity_y(0),
      velocity_z(0),
      far_left(0),
      far_right(0),
      far_front(0)
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
        float real;
        uint32_t base;
      } u_distance_x;
      u_distance_x.real = this->distance_x;
      *(outbuffer + offset + 0) = (u_distance_x.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_distance_x.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_distance_x.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_distance_x.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->distance_x);
      union {
        float real;
        uint32_t base;
      } u_distance_y;
      u_distance_y.real = this->distance_y;
      *(outbuffer + offset + 0) = (u_distance_y.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_distance_y.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_distance_y.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_distance_y.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->distance_y);
      union {
        float real;
        uint32_t base;
      } u_distance_z;
      u_distance_z.real = this->distance_z;
      *(outbuffer + offset + 0) = (u_distance_z.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_distance_z.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_distance_z.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_distance_z.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->distance_z);
      union {
        float real;
        uint32_t base;
      } u_velocity_x;
      u_velocity_x.real = this->velocity_x;
      *(outbuffer + offset + 0) = (u_velocity_x.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_velocity_x.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_velocity_x.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_velocity_x.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->velocity_x);
      union {
        float real;
        uint32_t base;
      } u_velocity_y;
      u_velocity_y.real = this->velocity_y;
      *(outbuffer + offset + 0) = (u_velocity_y.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_velocity_y.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_velocity_y.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_velocity_y.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->velocity_y);
      union {
        float real;
        uint32_t base;
      } u_velocity_z;
      u_velocity_z.real = this->velocity_z;
      *(outbuffer + offset + 0) = (u_velocity_z.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_velocity_z.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_velocity_z.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_velocity_z.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->velocity_z);
      union {
        bool real;
        uint8_t base;
      } u_far_left;
      u_far_left.real = this->far_left;
      *(outbuffer + offset + 0) = (u_far_left.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->far_left);
      union {
        bool real;
        uint8_t base;
      } u_far_right;
      u_far_right.real = this->far_right;
      *(outbuffer + offset + 0) = (u_far_right.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->far_right);
      union {
        bool real;
        uint8_t base;
      } u_far_front;
      u_far_front.real = this->far_front;
      *(outbuffer + offset + 0) = (u_far_front.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->far_front);
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
        float real;
        uint32_t base;
      } u_distance_x;
      u_distance_x.base = 0;
      u_distance_x.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_distance_x.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_distance_x.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_distance_x.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->distance_x = u_distance_x.real;
      offset += sizeof(this->distance_x);
      union {
        float real;
        uint32_t base;
      } u_distance_y;
      u_distance_y.base = 0;
      u_distance_y.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_distance_y.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_distance_y.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_distance_y.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->distance_y = u_distance_y.real;
      offset += sizeof(this->distance_y);
      union {
        float real;
        uint32_t base;
      } u_distance_z;
      u_distance_z.base = 0;
      u_distance_z.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_distance_z.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_distance_z.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_distance_z.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->distance_z = u_distance_z.real;
      offset += sizeof(this->distance_z);
      union {
        float real;
        uint32_t base;
      } u_velocity_x;
      u_velocity_x.base = 0;
      u_velocity_x.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_velocity_x.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_velocity_x.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_velocity_x.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->velocity_x = u_velocity_x.real;
      offset += sizeof(this->velocity_x);
      union {
        float real;
        uint32_t base;
      } u_velocity_y;
      u_velocity_y.base = 0;
      u_velocity_y.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_velocity_y.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_velocity_y.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_velocity_y.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->velocity_y = u_velocity_y.real;
      offset += sizeof(this->velocity_y);
      union {
        float real;
        uint32_t base;
      } u_velocity_z;
      u_velocity_z.base = 0;
      u_velocity_z.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_velocity_z.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_velocity_z.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_velocity_z.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->velocity_z = u_velocity_z.real;
      offset += sizeof(this->velocity_z);
      union {
        bool real;
        uint8_t base;
      } u_far_left;
      u_far_left.base = 0;
      u_far_left.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->far_left = u_far_left.real;
      offset += sizeof(this->far_left);
      union {
        bool real;
        uint8_t base;
      } u_far_right;
      u_far_right.base = 0;
      u_far_right.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->far_right = u_far_right.real;
      offset += sizeof(this->far_right);
      union {
        bool real;
        uint8_t base;
      } u_far_front;
      u_far_front.base = 0;
      u_far_front.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->far_front = u_far_front.real;
      offset += sizeof(this->far_front);
     return offset;
    }

    const char * getType(){ return "wheel_tokyo_weili/wheel_planner"; };
    const char * getMD5(){ return "77923c5df40e0774e0d9d555faca733d"; };

  };

}
#endif
