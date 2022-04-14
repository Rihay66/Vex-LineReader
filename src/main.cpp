/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\onthe.LAPTOP-LTNLPS3L                            */
/*    Created:      Tue Mar 01 2022                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// LineTrackerC         line          C               
// LineTrackerD         line          D               
// LineTrackerE         line          E               
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

// Used to tell if system being calibrated for line reader
// bool isCalib;

LineReadModule module;

void pre_auton(void){
  vexcodeInit();
}

void userControl(void){
  while(1){
    if(Controller.ButtonA.pressing()){
      module.setVariable = true;
    }else{
      module.setVariable = false;
    }
  }
}

competition Competition;

int main() {
  //Initialize
  Competition.drivercontrol(userControl);
  pre_auton();
  
  //Learn how to move a motorgroup

  module.Threshold = 0;
  module.loopCali = true;
  module.isCaliLight = true;
  module.LightThreshold = 0;
  module.DarkThreshold = 0;

  Brain.Screen.print("Calibrating");

  //Update to until Threshold is found
  while(module.Threshold == 0)
  { 
    module.calibration(LineTrackerE);
  }

  module.Update(LineTrackerC, LineTrackerE, LineTrackerD);
  // Note : above threshold means dark, and below means light
  
}