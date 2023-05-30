// Generated by gencpp from file jhr_type_2023/SetRobot.msg
// DO NOT EDIT!


#ifndef JHR_TYPE_2023_MESSAGE_SETROBOT_H
#define JHR_TYPE_2023_MESSAGE_SETROBOT_H

#include <ros/service_traits.h>


#include <jhr_type_2023/SetRobotRequest.h>
#include <jhr_type_2023/SetRobotResponse.h>


namespace jhr_type_2023
{

struct SetRobot
{

typedef SetRobotRequest Request;
typedef SetRobotResponse Response;
Request request;
Response response;

typedef Request RequestType;
typedef Response ResponseType;

}; // struct SetRobot
} // namespace jhr_type_2023


namespace ros
{
namespace service_traits
{


template<>
struct MD5Sum< ::jhr_type_2023::SetRobot > {
  static const char* value()
  {
    return "7cbfb8a0467c30430a839a7c40eb6982";
  }

  static const char* value(const ::jhr_type_2023::SetRobot&) { return value(); }
};

template<>
struct DataType< ::jhr_type_2023::SetRobot > {
  static const char* value()
  {
    return "jhr_type_2023/SetRobot";
  }

  static const char* value(const ::jhr_type_2023::SetRobot&) { return value(); }
};


// service_traits::MD5Sum< ::jhr_type_2023::SetRobotRequest> should match
// service_traits::MD5Sum< ::jhr_type_2023::SetRobot >
template<>
struct MD5Sum< ::jhr_type_2023::SetRobotRequest>
{
  static const char* value()
  {
    return MD5Sum< ::jhr_type_2023::SetRobot >::value();
  }
  static const char* value(const ::jhr_type_2023::SetRobotRequest&)
  {
    return value();
  }
};

// service_traits::DataType< ::jhr_type_2023::SetRobotRequest> should match
// service_traits::DataType< ::jhr_type_2023::SetRobot >
template<>
struct DataType< ::jhr_type_2023::SetRobotRequest>
{
  static const char* value()
  {
    return DataType< ::jhr_type_2023::SetRobot >::value();
  }
  static const char* value(const ::jhr_type_2023::SetRobotRequest&)
  {
    return value();
  }
};

// service_traits::MD5Sum< ::jhr_type_2023::SetRobotResponse> should match
// service_traits::MD5Sum< ::jhr_type_2023::SetRobot >
template<>
struct MD5Sum< ::jhr_type_2023::SetRobotResponse>
{
  static const char* value()
  {
    return MD5Sum< ::jhr_type_2023::SetRobot >::value();
  }
  static const char* value(const ::jhr_type_2023::SetRobotResponse&)
  {
    return value();
  }
};

// service_traits::DataType< ::jhr_type_2023::SetRobotResponse> should match
// service_traits::DataType< ::jhr_type_2023::SetRobot >
template<>
struct DataType< ::jhr_type_2023::SetRobotResponse>
{
  static const char* value()
  {
    return DataType< ::jhr_type_2023::SetRobot >::value();
  }
  static const char* value(const ::jhr_type_2023::SetRobotResponse&)
  {
    return value();
  }
};

} // namespace service_traits
} // namespace ros

#endif // JHR_TYPE_2023_MESSAGE_SETROBOT_H