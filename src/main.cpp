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
#include "memory"
#include "stdexcept"

using namespace std;
using namespace ReadLine;
using namespace vex;

LineRead read;
LineReadCalibration cal;

bool press;

void pre_auton(void){
  vexcodeInit();
}

int main() {
  //Initialize
  pre_auton();
  
  bool tmpB = false;

  ifstream DATAFILE;
  DATAFILE.open("SAVE.txt", ios::in);

  if(DATAFILE.is_open()){
    Brain.Screen.print("Save file found");
    if(cal.overwriteOption()){
      tmpB = true;
      cal.toOverwrite = false;
    }else{
      tmpB = false;
      cal.toOverwrite = true;
    }
  }else{
    Brain.Screen.print("No save file");
    tmpB = true;
  }
  //Close the file to check for
  //Note: The file opened is not saved is only checked to see if it exists
  DATAFILE.close();

  wait(2, sec);

  Brain.Screen.clearScreen();

  if(tmpB == true){
    //Init the line array for the connected line trackersb
    line lineArray[] = {LineTrackerA, LineTrackerC, LineTrackerB};

    int arrSize = sizeof(lineArray)/sizeof(lineArray[0]);

   for(int i = 0;i < arrSize;){
    //Loop through each module and add to threshold array
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print("In loop %d", i);
    cal.Threshold[i] = cal.calibration(lineArray[i], i);
    i++;
   }

    Brain.Screen.clearScreen();
    Brain.Screen.print("CALIBRATION COMPLETED");

    //Save to file the treshold array
    SDCARD sd(cal);
  }else{
    SDCARD sd(cal);
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print("FILE ALREADY EXISTS");
  }

  Brain.Screen.newLine();
  Brain.Screen.print("FILE check done bruv");

  //Learn how to move a motorgroup

  //Brain.Screen.print("Calibrating");

  //Update to until Threshold is found
  /*
  while(module.Threshold == 0)
  { 
    module.calibration(LineTrackerE);
  }
  */

  //Current ClawBot has a line reader config of CED
  //            right         center        left
  /*
  while(1){
    read.Update(LineTrackerB, LineTrackerC, LineTrackerA);
  }
  */
  // Note : above threshold means dark, and below means light

  //Exit program
  return 0;
}