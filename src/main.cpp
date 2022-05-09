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
#include "stdio.h"
#include "memory"
#include "stdexcept"

using namespace std;
using namespace ReadLine;
using namespace vex;

LineRead read;
LineReadCalibration* cal;

bool press;
line *lineArray = new line[3] {LineTrackerA, LineTrackerC, LineTrackerB};

void pre_auton(void){
  vexcodeInit();
}

void saveFile(LineReadCalibration* cal, bool toOverwrite, float *thresholdArr[3]){
  SDCARD* ptr = new SDCARD(toOverwrite, thresholdArr, cal);
  wait(2, sec);
  delete ptr;
}

int main() {
  //Initialize
  pre_auton();
  
  bool tmpB = false;

  ifstream DATAFILE;
  DATAFILE.open("SAVE.txt", ios::in);

  if(DATAFILE.is_open()){
    Brain.Screen.print("Save file found");
    if(cal->overwriteOption()){
      tmpB = true;
      cal->toOverwrite = true;
    }else{
      tmpB = false;
      cal->toOverwrite = false;
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

   for(int i = 0;i < 3;){
    //Loop through each module and add to threshold array

    int x = i + 1;

    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print("In loop %d", x);
    cal->Threshold[i] = cal->calibration(lineArray[i], i);
    i++;
   }

    Brain.Screen.clearScreen();
    Brain.Screen.print("CALIBRATION COMPLETED");

    wait(2, sec);

    //Save to file the treshold array
    saveFile(cal, cal->toOverwrite, cal->Threshold);
  }else{
    saveFile(cal, cal->toOverwrite, cal->Threshold);
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print("FILE ALREADY EXISTS");
  }

  Brain.Screen.newLine();
  Brain.Screen.print("FILE check done bruv");
  
  //Free memory
  float *tmpArray[3] = {cal->Threshold[0], cal->Threshold[1], cal->Threshold[2]};
  
  delete cal;

  wait(4, sec);

  //[] Set the cal threshold to the sd card tmpThreshold

  //Learn how to move a motorgroup

  //Current ClawBot has a line reader config of CED
  //            right         center        left

  while(1){
    read.Update(lineArray[0], lineArray[1], lineArray[2], tmpArray);
  }
  
  // Note : above threshold means dark, and below means light

  //Exit program
  return 0;
}