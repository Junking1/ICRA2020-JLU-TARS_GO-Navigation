#include "ros/ros.h"
#include <iostream>
#include "std_msgs/Int8.h"
  
int main(int argc, char **argv)
{
	ros::init(argc,argv,"set_obstacle_region");
	ros::NodeHandle ob;
	ros::Publisher object_number=ob.advertise<std_msgs::Int8>("object_number",10);

	ros::Rate loop_rate(10);

	while(ros::ok){
		std_msgs::Int8 msg;
		std::cin>>msg.data;
		object_number.publish(msg);
		ros::spinOnce();
		loop_rate.sleep();
	}
	return 0;
}
 
