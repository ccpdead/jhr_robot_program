// Generated by gencpp from file jhr_type_2023/Jhr_points.msg
// DO NOT EDIT!


#ifndef JHR_TYPE_2023_MESSAGE_JHR_POINTS_H
#define JHR_TYPE_2023_MESSAGE_JHR_POINTS_H


#include <string>
#include <vector>
#include <memory>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>
#include <jhr_type_2023/Jhr_point.h>

namespace jhr_type_2023
{
template <class ContainerAllocator>
struct Jhr_points_
{
  typedef Jhr_points_<ContainerAllocator> Type;

  Jhr_points_()
    : header()
    , points()  {
    }
  Jhr_points_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , points(_alloc)  {
  (void)_alloc;
    }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef std::vector< ::jhr_type_2023::Jhr_point_<ContainerAllocator> , typename std::allocator_traits<ContainerAllocator>::template rebind_alloc< ::jhr_type_2023::Jhr_point_<ContainerAllocator> >> _points_type;
  _points_type points;





  typedef boost::shared_ptr< ::jhr_type_2023::Jhr_points_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::jhr_type_2023::Jhr_points_<ContainerAllocator> const> ConstPtr;

}; // struct Jhr_points_

typedef ::jhr_type_2023::Jhr_points_<std::allocator<void> > Jhr_points;

typedef boost::shared_ptr< ::jhr_type_2023::Jhr_points > Jhr_pointsPtr;
typedef boost::shared_ptr< ::jhr_type_2023::Jhr_points const> Jhr_pointsConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::jhr_type_2023::Jhr_points_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::jhr_type_2023::Jhr_points_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::jhr_type_2023::Jhr_points_<ContainerAllocator1> & lhs, const ::jhr_type_2023::Jhr_points_<ContainerAllocator2> & rhs)
{
  return lhs.header == rhs.header &&
    lhs.points == rhs.points;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::jhr_type_2023::Jhr_points_<ContainerAllocator1> & lhs, const ::jhr_type_2023::Jhr_points_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace jhr_type_2023

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::jhr_type_2023::Jhr_points_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::jhr_type_2023::Jhr_points_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::jhr_type_2023::Jhr_points_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::jhr_type_2023::Jhr_points_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::jhr_type_2023::Jhr_points_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::jhr_type_2023::Jhr_points_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::jhr_type_2023::Jhr_points_<ContainerAllocator> >
{
  static const char* value()
  {
    return "b5a347b507bfdfb23842aa0f4df79f03";
  }

  static const char* value(const ::jhr_type_2023::Jhr_points_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xb5a347b507bfdfb2ULL;
  static const uint64_t static_value2 = 0x3842aa0f4df79f03ULL;
};

template<class ContainerAllocator>
struct DataType< ::jhr_type_2023::Jhr_points_<ContainerAllocator> >
{
  static const char* value()
  {
    return "jhr_type_2023/Jhr_points";
  }

  static const char* value(const ::jhr_type_2023::Jhr_points_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::jhr_type_2023::Jhr_points_<ContainerAllocator> >
{
  static const char* value()
  {
    return "Header header\n"
"jhr_type_2023/Jhr_point[] points\n"
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
"\n"
"================================================================================\n"
"MSG: jhr_type_2023/Jhr_point\n"
"float32 X\n"
"float32 Y\n"
"float32 A\n"
;
  }

  static const char* value(const ::jhr_type_2023::Jhr_points_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::jhr_type_2023::Jhr_points_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.points);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct Jhr_points_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::jhr_type_2023::Jhr_points_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::jhr_type_2023::Jhr_points_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "points[]" << std::endl;
    for (size_t i = 0; i < v.points.size(); ++i)
    {
      s << indent << "  points[" << i << "]: ";
      s << std::endl;
      s << indent;
      Printer< ::jhr_type_2023::Jhr_point_<ContainerAllocator> >::stream(s, indent + "    ", v.points[i]);
    }
  }
};

} // namespace message_operations
} // namespace ros

#endif // JHR_TYPE_2023_MESSAGE_JHR_POINTS_H
