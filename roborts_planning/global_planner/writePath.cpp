#include "ros/ros.h"
#include <nav_msgs/Path.h>
#include <geometry_msgs/PointStamped.h>
#include <geometry_msgs/Pose.h>
#include <tf/transform_broadcaster.h>
#include <tf/tf.h>
#include <unordered_map>

#include  <iostream>
#include <fstream>    // 读写文件的头文件
#include <string>
using namespace std;

void pathCallBack(nav_msgs::Path &path){
	float x;
	float y;
	
	ofstream ofs;
    ofs.open("text.txt", ios::out);
	
	geometry_msgs::PoseStamped this_pose_stamped;
	for(int i=0;i<1000;i++){
		if(path.pose.push_back(i)){
		this_pose_stamped=path.poses.push_back(i);
		x=this_pose_stamped.pose.position.x;
		y=this_pose_stamped.pose.position.y;
		ofs << x ;
		ofs <<" ";
		ofs << y<< endl;}
		else continue;
	}
    ofs.close();
/*         geometry_msgs::Quaternion goal_quat = tf::createQuaternionMsgFromYaw(th);
        this_pose_stamped.pose.orientation.x = goal_quat.x;
        this_pose_stamped.pose.orientation.y = goal_quat.y;
        this_pose_stamped.pose.orientation.z = goal_quat.z;
        this_pose_stamped.pose.orientation.w = goal_quat.w; */

/*         this_pose_stamped.header.stamp = current_time;
        this_pose_stamped.header.frame_id = "odom";
        path.poses.push_back(this_pose_stamped); */

        //path_pub.publish(path);
    	
}

int main (int argc ,char **argv)
{

    ros::init(argc,argv,"writePath");
	ros::NodeHandle viz_nh("~");
     nav_msgs::Path path;
    ros::Subscriber sub = viz_nh.subscribe<nav_msgs::Path>("SubscribePath",100,pathcallback);
	ros::spin();
	return 0;
}
