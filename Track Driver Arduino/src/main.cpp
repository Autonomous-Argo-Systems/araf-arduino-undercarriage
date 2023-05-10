#include <Arduino.h>
#include <ros.h>
#include <geometry_msgs/Twist.h>

#define LEFT_TRACK 9
#define RIGHT_TRACK 10

ros::NodeHandle nh;

void driveCommand( const geometry_msgs::Twist &twist){

  float left_speed;
  float right_speed;
  
  if (twist.linear.x > 0.1f ){
      left_speed = (142 + (twist.linear.x * 100.0f));
  } else if( twist.linear.x < -0.1f){
      left_speed = (128 +  (twist.linear.x * 100.0f));
  } else {
      left_speed = 0;
  }

  if (twist.linear.y > 0.1f ){
      right_speed = (142 + (twist.linear.y * 100.0f));
  } else if(twist.linear.y < -0.1f){
      right_speed = (128 +  (twist.linear.y * 100.0f));
  } else {
      right_speed = 0;
  }

  analogWrite(LEFT_TRACK, left_speed);
  analogWrite(RIGHT_TRACK, right_speed);
}

ros::Subscriber<geometry_msgs::Twist> subscriber("cmd_vel", &driveCommand);

void setup() {
  pinMode(LEFT_TRACK, OUTPUT);
  pinMode(RIGHT_TRACK, OUTPUT);
  nh.initNode();
  nh.subscribe(subscriber);
}

void loop() {
  nh.spinOnce();
  delay(1);
}