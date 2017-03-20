#ifndef __TETHER_TRACKING_NODE_H__
#define __TETHER_TRACKING_NODE_H__
#include "ros/ros.h"

#include <string>
#include <sstream>





//ros
#include <ros/ros.h>
#include "message_filters/subscriber.h"
#include "message_filters/time_synchronizer.h"
#include "sensor_msgs/CameraInfo.h"
#include "sensor_msgs/Image.h"
#include "geometry_msgs/PoseStamped.h"
#include "geometry_msgs/PoseWithCovarianceStamped.h"
#include <geometry_msgs/Twist.h>
#include <image_transport/image_transport.h>
#include <sensor_msgs/CameraInfo.h>
#include <rosgraph_msgs/Clock.h>
#include "std_msgs/Header.h"

#include "nav_msgs/Odometry.h"
#include "tf/transform_datatypes.h"

// Visp
#include <visp/vpPixelMeterConversion.h>
#include <visp/vpCameraParameters.h>

//C++
#include <iostream>
#include <fstream>
#include <math.h>
#include <ctime>



namespace tether_tracking{
  class Node{
    private:
      ros::NodeHandle n_;
      bool got_image_;
      bool got_camInfo_;
      vpCameraParameters cam_;
      std::string imageTopic_;
      std::string camInfoTopic_;

      void imageCallback(const sensor_msgs::ImageConstPtr& image);
      void waitForCamInfo();
  
    public:
      Node();
      void spin();
  };
};
#endif