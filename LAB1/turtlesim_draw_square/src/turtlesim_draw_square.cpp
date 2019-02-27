#include "ros/ros.h"

#include "turtlesim/Pose.h"

#include "geometry_msgs/Twist.h"



#define PI 3.14159



ros::Publisher pub;

ros::Subscriber sub;





void moveStraight(double speed,double distance,bool isForward);
void rotate(double angular_speed,double angle,bool isClockwise);
double degree2radians(double angle_in_degree);




int main(int argc, char **argv)

{

    // Initialize the node here

	ros::init(argc, argv, "turtle");

    	ros::NodeHandle node;
	double	speed,angular_speed;
	double	distance,angle;
	bool	isForward,isClockwise;

	
	speed=1.0;
	angular_speed=30.0;
	distance=5.0;
	angle=90.0;
	isForward=true;
	isClockwise=true;


	pub = node.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel",10);


    /**** Write a subscriber for the turtle pose

	sub = ...



	****/





    // Set the publish rate here

	ros::Rate rate(10);

    

    while (ros::ok()) 

	{
	moveStraight(speed,distance,isForward);
	rotate(degree2radians(angular_speed),degree2radians(angle),isClockwise);
        ros::spinOnce();    // Allow processing of incoming messages
        rate.sleep();

    }

}

void moveStraight(double speed,double distance,bool isForward)
{
	geometry_msgs::Twist vel_msg;

	if (isForward==true) 
		vel_msg.linear.x=fabs(speed);
	else
		vel_msg.linear.x=-fabs(speed);
		
	vel_msg.linear.y=0.0;
	vel_msg.linear.z=0.0;
	vel_msg.angular.x=0.0;
	vel_msg.angular.y=0.0;
	vel_msg.angular.z=0.0;

	double t0=ros::Time::now().toSec();
	double Current_distance=0.0;
	ros::Rate loop_rate(100);
	do
	{
		pub.publish(vel_msg);
		double t1= ros::Time::now().toSec();
		Current_distance=speed*(t1-t0);
		ros::spinOnce();
		loop_rate.sleep();
	}while(Current_distance<distance);
	vel_msg.linear.x=0.0;
	pub.publish(vel_msg);

}
void rotate(double angular_speed,double angle,bool isClockwise)
{
	geometry_msgs::Twist vel_msg;

	if (isClockwise==true) 
		vel_msg.angular.z=-fabs(angular_speed);
	else
		vel_msg.angular.z=fabs(angular_speed);
	vel_msg.linear.x=0.0;	
	vel_msg.linear.y=0.0;
	vel_msg.linear.z=0.0;
	vel_msg.angular.x=0.0;
	vel_msg.angular.y=0.0;

	double t0=ros::Time::now().toSec();
	double Current_angle=0.0;
	ros::Rate loop_rate(100);

	do
	{
		pub.publish(vel_msg);
		double t1= ros::Time::now().toSec();
		Current_angle=angular_speed*(t1-t0);
		ros::spinOnce();
		loop_rate.sleep();
	}while(Current_angle<angle);
	vel_msg.angular.z=0.0;
	pub.publish(vel_msg);
}
double degree2radians(double angle_in_degree)
{
	return angle_in_degree*PI/180.0;
}

