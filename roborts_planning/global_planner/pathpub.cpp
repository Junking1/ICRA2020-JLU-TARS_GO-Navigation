#include "ros/ros.h"
#include <nav_msgs/Path.h>
#include <geometry_msgs/PointStamped.h>
#include <geometry_msgs/Pose.h>
#include <tf/transform_broadcaster.h>
#include <tf/tf.h>
int main (int argc ,char **argv)
{
    ros::init(argc,argv,"pathpub");
    ros::NodeHandle n("~");
    ros::Publisher pub = n.advertise<nav_msgs::Path>("pubpath",1,true);
    ros::Rate loop_rate(10);
    nav_msgs::Path path;
    int count =50;
    ros::Time current_time,last_time;
    current_time = ros::Time::now();
    last_time = ros::Time::now();
    path.header.stamp = current_time;
    path.header.frame_id = "odom";
    while (ros::ok())
    {   
        geometry_msgs::PoseStamped start;
        current_time = ros::Time::now();
        if(count<=70)
        {
            start.pose.position.x = 50;
            start.pose.position.y = count++;
        }
        else
        {
            count = 50;
            continue;
        }
        start.header.stamp = current_time;
        start.header.frame_id = "odom";
        start.pose.orientation.w = 1;
        path.poses.push_back(start);
        pub.publish(path);
        ros::spinOnce;
        last_time = current_time;
        loop_rate.sleep();
        
    }
    return 0;
}
