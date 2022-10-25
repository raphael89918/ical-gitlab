#ifndef _ROS_gpio_Laser_h
#define _ROS_gpio_Laser_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace gpio
{

  class Laser : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef int16_t _distance_UL_type;
      _distance_UL_type distance_UL;
      typedef int16_t _distance_UR_type;
      _distance_UR_type distance_UR;
      typedef int16_t _distance_LL_type;
      _distance_LL_type distance_LL;
      typedef int16_t _distance_LR_type;
      _distance_LR_type distance_LR;

    Laser():
      header(),
      distance_UL(0),
      distance_UR(0),
      distance_LL(0),
      distance_LR(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      union {
        int16_t real;
        uint16_t base;
      } u_distance_UL;
      u_distance_UL.real = this->distance_UL;
      *(outbuffer + offset + 0) = (u_distance_UL.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_distance_UL.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->distance_UL);
      union {
        int16_t real;
        uint16_t base;
      } u_distance_UR;
      u_distance_UR.real = this->distance_UR;
      *(outbuffer + offset + 0) = (u_distance_UR.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_distance_UR.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->distance_UR);
      union {
        int16_t real;
        uint16_t base;
      } u_distance_LL;
      u_distance_LL.real = this->distance_LL;
      *(outbuffer + offset + 0) = (u_distance_LL.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_distance_LL.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->distance_LL);
      union {
        int16_t real;
        uint16_t base;
      } u_distance_LR;
      u_distance_LR.real = this->distance_LR;
      *(outbuffer + offset + 0) = (u_distance_LR.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_distance_LR.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->distance_LR);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      union {
        int16_t real;
        uint16_t base;
      } u_distance_UL;
      u_distance_UL.base = 0;
      u_distance_UL.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_distance_UL.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->distance_UL = u_distance_UL.real;
      offset += sizeof(this->distance_UL);
      union {
        int16_t real;
        uint16_t base;
      } u_distance_UR;
      u_distance_UR.base = 0;
      u_distance_UR.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_distance_UR.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->distance_UR = u_distance_UR.real;
      offset += sizeof(this->distance_UR);
      union {
        int16_t real;
        uint16_t base;
      } u_distance_LL;
      u_distance_LL.base = 0;
      u_distance_LL.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_distance_LL.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->distance_LL = u_distance_LL.real;
      offset += sizeof(this->distance_LL);
      union {
        int16_t real;
        uint16_t base;
      } u_distance_LR;
      u_distance_LR.base = 0;
      u_distance_LR.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_distance_LR.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->distance_LR = u_distance_LR.real;
      offset += sizeof(this->distance_LR);
     return offset;
    }

    const char * getType(){ return "gpio/Laser"; };
    const char * getMD5(){ return "23a11ab6c6d35da887fd8a210b80e1a3"; };

  };

}
#endif
