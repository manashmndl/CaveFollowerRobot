#include "CaveFollower.h"

#define MAX_DISTANCE 40
#define FRONT_MAX_DISTANCE 40
#define BACK_MAX_DISTANCE 30

using namespace cfr;

byte rm[2] = {3, 4};
byte lm[2] = {5, 6};

byte tx_rx[2] = {51, 50};

//TRIG > ECHO > MAX_DISTANCE
byte f_sonar[3] = {11, 10 , FRONT_MAX_DISTANCE};
byte l_sonar[3] = {9, 8, MAX_DISTANCE};
byte r_sonar[3] = {13, 12, MAX_DISTANCE};
byte b_sonar[3] = {31, 30, BACK_MAX_DISTANCE};

Robot r(lm, rm, l_sonar , f_sonar, r_sonar, b_sonar,tx_rx);



void setup()
{
  Serial.begin(9600);
  Serial.println("Begin!\n");
  Robot::global_speed = 150;
  Robot::global_right_speed = Robot::global_speed; //- 32;
  r.setKp(3.5);
  r.setKd(.1);
  r.ping_number = 2;
  //Optimum -> 150 speed, 3.5 kp and 0.1 kd
 // r.run(Robot::global_speed, 0, Robot::Forward, Robot::Forward);

 
}

void loop() {
  bool left_rotation = false;

  //When Both walls are available, it uses PD Algorithm
  while(r.leftMedianDistance() > 2 && r.rightMedianDistance() > 2) r.followWall();

  //Halts if front obstacle is detected and no wall on the right side
//  while(r.frontMedianDistance() > 25 && r.rightMedianDistance() <= 0 && r.leftMedianDistance() > 2) r.run(Robot::global_speed, Robot::global_speed, Robot::Forward, Robot::Forward);

  //Halts if front obstacle is detected and no wall on the left side
//  while(r.frontMedianDistance() > 25 && r.rightMedianDistance() > 2 && r.leftMedianDistance() <= 0) r.run(Robot::global_speed, Robot::global_speed, Robot::Forward, Robot::Forward);
  
//  r.run();
//  delay(1);


  //Rotates clockwise if desired direction is right
  while (r.frontMedianDistance() != 0 && r.leftMedianDistance() > 4){
    r.run(Robot::global_speed, Robot::global_speed, Robot::Clockwise);
//    r.run(255, Robot::global_speed, Robot::Right);
    //delay(2);

  }

  //Rotates anticlockwise if desired direction is left
   while (r.frontMedianDistance() != 0 && r.rightMedianDistance() > 4){
    r.run(Robot::global_speed, Robot::global_speed, Robot::AntiClockwise);
//    r.run(255, Robot::global_speed, Robot::Right);
    //delay(2);

  }


  //Goes forward if right side is open
  while(r.rightMedianDistance() == 0 && r.leftMedianDistance() > 10) {r.run(Robot::global_speed, Robot::global_speed, Robot::Forward, Robot::Forward);}

  //Goes forward if left side is open

  while(r.leftMedianDistance() == 0 && r.rightMedianDistance() > 10) {r.run(Robot::global_speed, Robot::global_speed, Robot::Forward, Robot::Forward);}
//
//  if (r.bluetooth->read() == 'a') r.printViaBluetooth();
//
//  r.run();

  while(r.leftMedianDistance() > 2 && r.rightMedianDistance() > 2 && r.frontMedianDistance() > 2) r.run(Robot::Nowhere);
 
}

