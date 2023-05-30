// Auto-generated. Do not edit!

// (in-package jhr_type_2023.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class Jhr_pose {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.X = null;
      this.Y = null;
      this.A = null;
      this.map = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('X')) {
        this.X = initObj.X
      }
      else {
        this.X = 0.0;
      }
      if (initObj.hasOwnProperty('Y')) {
        this.Y = initObj.Y
      }
      else {
        this.Y = 0.0;
      }
      if (initObj.hasOwnProperty('A')) {
        this.A = initObj.A
      }
      else {
        this.A = 0.0;
      }
      if (initObj.hasOwnProperty('map')) {
        this.map = initObj.map
      }
      else {
        this.map = '';
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type Jhr_pose
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [X]
    bufferOffset = _serializer.float32(obj.X, buffer, bufferOffset);
    // Serialize message field [Y]
    bufferOffset = _serializer.float32(obj.Y, buffer, bufferOffset);
    // Serialize message field [A]
    bufferOffset = _serializer.float32(obj.A, buffer, bufferOffset);
    // Serialize message field [map]
    bufferOffset = _serializer.string(obj.map, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Jhr_pose
    let len;
    let data = new Jhr_pose(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [X]
    data.X = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [Y]
    data.Y = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [A]
    data.A = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [map]
    data.map = _deserializer.string(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    length += _getByteLength(object.map);
    return length + 16;
  }

  static datatype() {
    // Returns string type for a message object
    return 'jhr_type_2023/Jhr_pose';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '8f8c2ab4000c121b27dee893afca3646';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    Header header
    float32 X
    float32 Y
    float32 A
    string map
    ================================================================================
    MSG: std_msgs/Header
    # Standard metadata for higher-level stamped data types.
    # This is generally used to communicate timestamped data 
    # in a particular coordinate frame.
    # 
    # sequence ID: consecutively increasing ID 
    uint32 seq
    #Two-integer timestamp that is expressed as:
    # * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
    # * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
    # time-handling sugar is provided by the client library
    time stamp
    #Frame this data is associated with
    string frame_id
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new Jhr_pose(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.X !== undefined) {
      resolved.X = msg.X;
    }
    else {
      resolved.X = 0.0
    }

    if (msg.Y !== undefined) {
      resolved.Y = msg.Y;
    }
    else {
      resolved.Y = 0.0
    }

    if (msg.A !== undefined) {
      resolved.A = msg.A;
    }
    else {
      resolved.A = 0.0
    }

    if (msg.map !== undefined) {
      resolved.map = msg.map;
    }
    else {
      resolved.map = ''
    }

    return resolved;
    }
};

module.exports = Jhr_pose;
