#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>W
#endif
#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Int16.h>

// Setting booleans for forward activation
const bool left_fwd = false;
const bool right_fwd = false;
// Pin variables for motors.
// Right Side Motor
// Analog Speed Pin
const int right_pwm_pin = 9;
// Digital Output Pins
const int right_direction_pin = 8;
const int right_direction_pin2 = 7;
// Left Side Motor
// Analog Speed Pin
const int left_pwm_pin = 3;
// Digital Output Pins
const int left_direction_pin = 5;
const int left_direction_pin2 = 4;
// Robot dimensions. In cm.
const float wheel_distance = 20.0;
// Default speed 
const int default_velocity = 140;
int current_velocity = default_velocity;
const int maximium_velocity = 255;

ros::NodeHandle  nh;

// function to update motor speeds as per instructions
void update_speed(const geometry_msgs::Twist & msg) {
  // Read incoming twist message
  // Extract the linear x and angular z information
  const float x = msg.linear.x;
  const float z = msg.angular.z;
  // Calculate the percentage speed for the motors
  float right_percent = (-z*1.8)/2.0 + x;
  float left_percent = 2.0*x - right_percent; 
  // Calculate the directions for the motors
  bool right_direction = (right_percent>0)? right_fwd : !right_fwd; 
  bool left_direction = (left_percent>0)? left_fwd : !left_fwd; 
  //output the new directions to the motors
  digitalWrite(right_direction_pin, right_direction); 
  digitalWrite(right_direction_pin2, !right_direction); 
  digitalWrite(left_direction_pin, left_direction); 
  digitalWrite(left_direction_pin2, !left_direction); 
  //calculate the speed of the motors
  int right_speed = int( maximium_velocity * right_percent); 
  int left_speed = int( maximium_velocity * left_percent ); 
  // if signalled to break, call movestop function
  if (x == 0 && z == 0){ 
      MoveStop();
  }
  // ensure speeds are positive numbers
  int abs_right_speed = abs(right_speed); 
  int abs_left_speed =  abs(left_speed); 
  // output speed to motors
  analogWrite(right_pwm_pin, abs_right_speed); 
  analogWrite(left_pwm_pin,  abs_left_speed); 
}

// fuction to apply break to all motor
void MoveStop() {
  digitalWrite(right_direction_pin, right_fwd);
  digitalWrite(left_direction_pin, left_fwd);
  digitalWrite(right_direction_pin2, right_fwd);
  digitalWrite(left_direction_pin2, left_fwd);
  analogWrite(right_pwm_pin, 0);
  analogWrite(left_pwm_pin, 0);
}

ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel", update_speed);


void setup() {
  //activate all the required pins
  pinMode(right_pwm_pin, OUTPUT);    
  pinMode(right_direction_pin, OUTPUT);
  pinMode(right_direction_pin2, OUTPUT);
  pinMode(left_pwm_pin, OUTPUT);
  pinMode(left_direction_pin, OUTPUT);
  pinMode(left_direction_pin2, OUTPUT);
  //initilization test, turn motors on and forward for a second
  // Set initial values for directions. Set both to forward.
  digitalWrite(right_direction_pin, right_fwd);
  digitalWrite(right_direction_pin2, !right_fwd); 
  digitalWrite(left_direction_pin, left_fwd);
  digitalWrite(left_direction_pin2, !left_fwd);
  pinMode(13, OUTPUT);
  // Send forward command.
  analogWrite(right_pwm_pin, default_velocity);
  analogWrite(left_pwm_pin, default_velocity);
  delay(1000);
  //end of test
  MoveStop();
  nh.initNode();
  nh.subscribe(sub);
}

void loop() {
  nh.spinOnce();
  delay(1);
}
