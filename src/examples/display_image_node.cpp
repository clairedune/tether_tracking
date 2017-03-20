#include "Node.h"

#include "nav_msgs/Odometry.h"
#include <rosgraph_msgs/Clock.h>
#include "tf/transform_datatypes.h"
#include <iostream>
#include <fstream>


int main(int argc,char** argv){
  
	ROS_INFO("Display_image_node Launched");
	ros::init(argc, argv, "Display_image_node");
	tether_tracking::Node().spin();	
	return 0;
}