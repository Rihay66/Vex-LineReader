#include "vex.h"
#include "LineReaderLibrary.h"
#include "iostream"

using namespace std;
using namespace ReadLine;
using namespace vex;

controller Controller;

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
  /*
  while(module.Threshold == 0)
  { 
    module.calibration(LineTrackerE);
  }
  */

  //Current ClawBot has a line reader config of CED
  //            right         center        left
  while(1){
    module.Update(LineTrackerC, LineTrackerE, LineTrackerD);
  }
  // Note : above threshold means dark, and below means light
  
}