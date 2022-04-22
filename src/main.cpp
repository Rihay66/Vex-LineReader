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
#include "vex.h"
#include "LineReaderLibrary.h"
#include "iostream"

using namespace std;
using namespace ReadLine;
using namespace vex;

controller Controller;

LineRead read;

void pre_auton(void){
  vexcodeInit();
}
/*
void userControl(void){
  while(1){
    if(Controller.ButtonA.pressing()){
      
    }else{
      
    }
  }
}
*/
competition Competition;

int main() {
  //Initialize
  //Competition.drivercontrol(userControl);
  pre_auton();
  
  //Learn how to move a motorgroup

  Brain.Screen.print("Calibrating");

  //Update to until Threshold is found
  /*
  while(module.Threshold == 0)
  { 
    module.calibration(LineTrackerE);
  }
  */

  //Current ClawBot has a line reader config of CED
  //            right         center        left
  while(1){
    read.Update(LineTrackerB, LineTrackerC, LineTrackerA);
  }
  // Note : above threshold means dark, and below means light
  
}