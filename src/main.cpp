// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// LineTrackerB         line          B               
// LineTrackerA         line          A               
// LineTrackerC         line          C               
// Motor10              motor         10              
// Motor1               motor         1               
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// LineTrackerE         line          E               
// LineTrackerA         line          A               
// LineTrackerC         line          C               
// Motor10              motor         10              
// Motor1               motor         1               
// ---- END VEXCODE CONFIGURED DEVICES ----
#include "LineReaderLibrary.h"

using namespace ReadLineLibrary;

void pre_auton(void){
  vexcodeInit();
}

int main() {
  //Initialize
  pre_auton();

  //A line pointer array set to robot's 3-wire config of line reader

  line* lineArray = new line[3] {LineTrackerA, LineTrackerC, LineTrackerB};

  LRH _lrh;
  //call init to start calibration system and save file system
  if(!_lrh.Init(lineArray,_lrh)){
    //This is for error checking
    return 1;
  }
  
  // Note : above threshold means dark, and below means light

  //Exit program
  return 0;
}