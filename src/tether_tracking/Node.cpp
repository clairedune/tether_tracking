#include "Node.h"

#include "std_msgs/Int8.h"
#include "std_msgs/String.h"

#include <cv_bridge/cv_bridge.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

namespace tether_tracking{
        Node::Node() : n_("~"),
                       got_image_(false),
                       got_camInfo_(false),
                       cam_(),
                       imageTopic_("/turtle2/camera/rgb/image_raw"),
		       camInfoTopic_("/turtle2/camera/rgb/camera_info")
		       {
			 
		      }

        
        
        void Node::imageCallback(const sensor_msgs::ImageConstPtr& image){
	  
		cv_bridge::CvImagePtr cv_ptr;
		try{
			cv_ptr = cv_bridge::toCvCopy(image, "bgr8");
		}
		catch(cv_bridge::Exception& e)
		{
		    ROS_ERROR("Could not convert from '%s' to 'bgr8'.", image->encoding.c_str());
		}
		
		//drawDesiredCurve(cv_ptr->image, s_d, iVizD);
		cv::imshow("Image Turtlebot", cv_ptr->image);
		//cv::imshow("Image BW", imgMap);
		cv::waitKey(1);
		
                got_image_ = true;
        }
        
        void Node::waitForCamInfo(){
	  
		// initial camera parameter guess
		int px(554), py(554), u0(320), v0 (240);
	        ros::Duration timeout(2,0); // Timeout of 2 seconds
		sensor_msgs::CameraInfoConstPtr msg = ros::topic::waitForMessage<sensor_msgs::CameraInfo>(this->camInfoTopic_, this->n_, timeout);
                if(msg!=NULL){
		  got_camInfo_ = true;
		  /* Get camera info and store it in cam_params global variable */
		  px = (int)(msg->K[0]);
		  u0 = (int)(msg->K[2]);
		  py = (int)(msg->K[4]);
		  v0 = (int)(msg->K[5]);	
		}
		else{
		  ROS_WARN("Camera Info not available yet. Using default values");
		}
		// Camera initialization with a perspective projection without distortion model
		(this->cam_).initPersProjWithoutDistortion(px,py,u0,v0);
        }

        void Node::spin(){
	   
	  this->waitForCamInfo();
	  
	  image_transport::ImageTransport it(this->n_);
	  image_transport::Subscriber sub_img = it.subscribe(this->imageTopic_, 1, &Node::imageCallback, this);
	  /* Create opencv windows */
	  cv::namedWindow("Image Turtlebot", CV_WINDOW_NORMAL);
	  cv::namedWindow("Image BW", CV_WINDOW_NORMAL);
	  ros::spin();
	  cv::startWindowThread();
	  cv::destroyWindow("Image Turtlebot");
	  cv::destroyWindow("Image BW");
	  
	  
	}

}