#include <ros/ros.h>
#include <ros/console.h>
#include <nav_msgs/Path.h>
#include <std_msgs/String.h>
#include <geometry_msgs/Quaternion.h>
#include <geometry_msgs/PoseStamped.h>
#include <tf/transform_broadcaster.h>
#include <tf/tf.h>
/**不用坐标转换，但不知为何
bool World2Map(double wx, double wy, unsigned int &mx, unsigned int &my){
	double origin_x_=0.0;
	double origin_y_=0.0;
	double resolution_=0.05;
	int size_x_=163;
	int size_y_=104;
  if (wx < origin_x_ || wy < origin_y_) {
    return false;
  }
  mx = (int) ((wx - origin_x_) / resolution_);
  my = (int) ((wy - origin_y_) / resolution_);
  if (mx < size_x_ && my < size_y_) {
    return true;
  }
  return false;
}
*/
main(int argc, char** argv)
{
    ros::init(argc, argv, "showpath");

    ros::NodeHandle ph;
    ros::Publisher path_pub = ph.advertise<nav_msgs::Path>("trajectory", 10, true);

    ros::Time current_time, last_time;
    current_time = ros::Time::now();
    last_time = ros::Time::now();

    nav_msgs::Path path;
    //nav_msgs::Path path;
    path.header.stamp = current_time;
    path.header.frame_id = "map";


    double x = 3.0;
    double y = 0.4;
    double th = 0.0;
    double vx = 0.1;
    double vy = 0.1;
	//unsigned int ax=0;
        //unsigned int ay=0;
    //double vth = 1;

    ros::Rate loop_rate(10);
    while (ros::ok())
    {

        current_time = ros::Time::now();
        //compute odometry in a typical way given the velocities of the robot

	/**
        double dt = 10;
        double delta_x = (vx * cos(th) - vy * sin(th)) * dt;
        double delta_y = (vx * sin(th) + vy * cos(th)) * dt;
        double delta_th = vth * dt;

        x += delta_x;
        y += delta_y;
        th += delta_th;
	*/
	if(y<4.3)	y+=vy;

	//World2Map(x,y,ax,ay);

        geometry_msgs::PoseStamped this_pose_stamped;
        this_pose_stamped.pose.position.x = x;
        this_pose_stamped.pose.position.y = y;

        geometry_msgs::Quaternion goal_quat = tf::createQuaternionMsgFromYaw(th);
        this_pose_stamped.pose.orientation.x = goal_quat.x;
        this_pose_stamped.pose.orientation.y = goal_quat.y;
        this_pose_stamped.pose.orientation.z = goal_quat.z;
        this_pose_stamped.pose.orientation.w = goal_quat.w;

        this_pose_stamped.header.stamp = current_time;
        this_pose_stamped.header.frame_id = "odom";
        path.poses.push_back(this_pose_stamped);

        path_pub.publish(path);
        ros::spinOnce();               // check for incoming messages

        last_time = current_time;
        loop_rate.sleep();
    }

    return 0;
}

