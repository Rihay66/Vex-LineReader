#include "LineReaderLibrary.h"
#include "vex.h"

using namespace ReadLine;
using namespace vex;

int LineReadModule::LateUpdate(void){
  while(1){
    int temp = 1;
    wait(50, msec);
    if(moduleDetection(LineTrackerC, Threshold) == false && moduleDetection(LineTrackerD, Threshold) == false && moduleDetection(LineTrackerE, Threshold) == false){
      //Stop
      Brain.Screen.setCursor(temp, 1);
      Brain.Screen.print("STOPPED");
      Motor1.stop();
      Motor10.stop();
    }

    temp += 1;

    wait(1, sec);
    Brain.Screen.clearScreen();
  }

  return 0;
}

bool LineReadModule::moduleDetectionInverted(line module, int thresh){

  //Used to detect line reader value on inverted surfaces

  if(module.value(analogUnits::pct) < thresh){
    //Dark surface detection
    return true;
  }else{
    //Light surface detection
    return false;
  }
}

bool LineReadModule::moduleDetection(line module, int thresh){

  //Used to detect line reader value

  if(module.value(analogUnits::pct) > thresh){
      //Dark detection
      return true;
  }else{
    //Light detection
    return false;
  }
}

int LineReadModule::Update(line module1, line module2, line module3){

  while(1){

     bool line1 = moduleDetectionInverted(module1, Threshold);
     bool line2 = moduleDetectionInverted(module2, Threshold);
     bool line3 = moduleDetectionInverted(module3, Threshold);

    //Update every 25 millisecond frame
    int temp = 1;
    if(line2 == true){
      //Move forward
      Motor10.spin(forward, 5, percent);
      Motor1.spin(forward, 5, percent);
      wait(10, msec);
    }else{
      //Switch to check to move back into the line
      wait(5, msec);
      if(line1 == true || line3 == false){
        //Move right
        Motor1.spin(forward, 1, percent);
        Motor10.spin(forward, 3, percent);
        if(line1 == false || line3 == true){
          //Move left
          Motor1.spin(forward, 1, percent);
          Motor10.spin(forward, 3, percent);
        }
      }
    }
    temp += 1;

    //Update every 1 millisecond per frames
    Brain.Screen.clearScreen();
  }
}

void LineReadModule::calibration(line module){

  wait(2, sec);
  
  while(loopCali == true){
    //Updating every 25 millisecond

    wait(300, msec);

    //Clear screen to make room for other responses and remove the already acknowledged values
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1);

    if(setVariable == true && isCaliLight == true){
      Brain.Screen.clearScreen();
      LightThreshold = module.value(analogUnits::pct);

      setVariable = false;
      isCaliLight = false;

      Brain.Screen.print("Light set and light val is %4f", LightThreshold);
      wait(100, msec);
    }else if(setVariable == true && isCaliLight == false){
      //Brain.Screen.clearScreen();
      DarkThreshold = module.value(analogUnits::pct);

      Brain.Screen.print("Dark set and dark val is %4f", DarkThreshold);

      wait(2, sec);
      Brain.Screen.clearScreen();
      setVariable = false;
      loopCali = false;
    }
    wait(1, sec);
  }

  if(loopCali == false){
    Brain.Screen.setCursor(1, 1);
    Threshold = (LightThreshold + DarkThreshold) / 2;
    Brain.Screen.print("Threshold is %4f", Threshold);
    wait(1.8f, sec);
  }
}