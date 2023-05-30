// Generated by gencpp from file jhr_type_2023/Jhr_pose.msg
// DO NOT EDIT!


#ifndef JHR_TYPE_2023_MESSAGE_JHR_POSE_H
#define JHR_TYPE_2023_MESSAGE_JHR_POSE_H


#include <string>
#include <vector>
#include <memory>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>

namespace jhr_type_2023
{
template <class ContainerAllocator>
struct Jhr_pose_
{
  typedef Jhr_pose_<ContainerAllocator> Type;

  Jhr_pose_()
    : header()
    , X(0.0)
    , Y(0.0)
    , A(0.0)
    , map()  {
    }
  Jhr_pose_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , X(0.0)
    , Y(0.0)
    , A(0.0)
    , map(_alloc)  {
  (void)_alloc;
    }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef float _X_type;
  _X_type X;

   typedef float _Y_type;
  _Y_type Y;

   typedef float _A_type;
  _A_type A;

   typedef std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> _map_type;
  _map_type map;





  typedef boost::shared_ptr< ::jhr_type_2023::Jhr_pose_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::jhr_type_2023::Jhr_pose_<ContainerAllocator> const> ConstPtr;

}; // struct Jhr_pose_

typedef ::jhr_type_2023::Jhr_pose_<std::allocator<void> > Jhr_pose;

typedef boost::shared_ptr< ::jhr_type_2023::Jhr_pose > Jhr_posePtr;
typedef boost::shared_ptr< ::jhr_type_2023::Jhr_pose const> Jhr_poseConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::jhr_type_2023::Jhr_pose_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::jhr_type_2023::Jhr_pose_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::jhr_type_2023::Jhr_pose_<ContainerAllocator1> & lhs, const ::jhr_type_2023::Jhr_pose_<ContainerAllocator2> & rhs)
{
  return lhs.header == rhs.header &&
    lhs.X == rhs.X &&
    lhs.Y == rhs.Y &&
    lhs.A == rhs.A &&
    lhs.map == rhs.map;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::jhr_type_2023::Jhr_pose_<ContainerAllocator1> & lhs, const ::jhr_type_2023::Jhr_pose_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace jhr_type_2023

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::jhr_type_2023::Jhr_pose_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::jhr_type_2023::Jhr_pose_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::jhr_type_2023::Jhr_pose_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::jhr_type_2023::Jhr_pose_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::jhr_type_2023::Jhr_pose_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::jhr_type_2023::Jhr_pose_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::jhr_type_2023::Jhr_pose_<ContainerAllocator> >
{
  static const char* value()
  {
    return "8f8c2ab4000c121b27dee893afca3646";
  }

  static const char* value(const ::jhr_type_2023::Jhr_pose_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x8f8c2ab4000c121bULL;
  static const uint64_t static_value2 = 0x27dee893afca3646ULL;
};

template<class ContainerAllocator>
struct DataType< ::jhr_type_2023::Jhr_pose_<ContainerAllocator> >
{
  static const char* value()
  {
    return "jhr_type_2023/Jhr_pose";
  }

  static const char* value(const ::jhr_type_2023::Jhr_pose_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::jhr_type_2023::Jhr_pose_<ContainerAllocator> >
{
  static const char* value()
  {
    return "Header header\n"
"float32 X\n"
"float32 Y\n"
"float32 A\n"
"string map\n"
"================================================================================\n"
"MSG: std_msgs/Header\n"
"# Standard metadata for higher-level stamped data types.\n"
"# This is generally used to communicate timestamped data \n"
"# in a particular coordinate frame.\n"
"# \n"
"# sequence ID: consecutively increasing ID \n"
"uint32 seq\n"
"#Two-integer timestamp that is expressed as:\n"
"# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')\n"
"# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')\n"
"# time-handling sugar is provided by the client library\n"
"time stamp\n"
"#Frame this data is associated with\n"
"string frame_id\n"
;
  }

  static const char* value(const ::jhr_type_2023::Jhr_pose_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::jhr_type_2023::Jhr_pose_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.X);
      stream.next(m.Y);
      stream.next(m.A);
      stream.next(m.map);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct Jhr_pose_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::jhr_type_2023::Jhr_pose_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::jhr_type_2023::Jhr_pose_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "X: ";
    Printer<float>::stream(s, indent + "  ", v.X);
    s << indent << "Y: ";
    Printer<float>::stream(s, indent + "  ", v.Y);
    s << indent << "A: ";
    Printer<float>::stream(s, indent + "  ", v.A);
    s << indent << "map: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>::stream(s, indent + "  ", v.map);
  }
};

} // namespace message_operations
} // namespace ros

#endif // JHR_TYPE_2023_MESSAGE_JHR_POSE_H
