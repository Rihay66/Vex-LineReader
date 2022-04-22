#include "LineReaderLibrary.h"
#include "vex.h"

using namespace ReadLine;
using namespace vex;

int LineRead::LateUpdate(void){
  while(1){
    /*
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
    */
  }

  return 0;
}

bool LineReadCalibration::moduleDetectionInverted(line module, int thresh){

  //Used to detect line reader value on inverted surfaces

  if(module.value(analogUnits::pct) < thresh){
    //Dark surface detection
    return true;
  }else{
    //Light surface detection
    return false;
  }
}

bool LineReadCalibration::moduleDetection(line module, int thresh){

  //Used to detect line reader value

  if(module.value(analogUnits::pct) > thresh){
      //Dark detection
      return true;
  }else{
    //Light detection
    return false;
  }
}

int LineRead::Update(){
  
  while(1){
    //Note: The Calibration function can be used to find the value on a surface

    float tr1 = 55;
    float tr2 = 53;
    float tr3 = 61;

    bool line1 = moduleDetection(module1, tr1);
    bool line2 = moduleDetection(module2, tr2);
    bool line3 = moduleDetection(module3, tr3);
    /*
    bool line1Inv = moduleDetectionInverted(module1, Threshold);
    bool line2Inv = moduleDetectionInverted(module2, Threshold);
    bool line3Inv = moduleDetectionInverted(module3, Threshold);
    */
    //DEBUG MODE
    int temp = 1;
    
    //Testing the value of LineTrackerD
    Brain.Screen.print("%d %d %d ", line1, line2, line3);
    Brain.Screen.print(" %d %d %d", module1.value(analogUnits::pct), module2.value(analogUnits::pct), module3.value(analogUnits::pct));
    Brain.Screen.setCursor(temp, 1);

    if(line1 && line2 && line3){
      Brain.Screen.print("Center");
      Motor1.spin(forward, 2, pct);
      Motor10.spin(forward, 2, pct);
      break;
    }else{
      if(line1 && line2 && !line3){
        Brain.Screen.print("Left");
        Motor1.spin(forward, 2, pct);
        Motor10.spin(forward, 1, pct);
        wait(10, msec);
        break;
      }else if(!line1 && line2 && line3){
        Brain.Screen.print("Right");
        Motor1.spin(forward, 1, pct);
        Motor10.spin(forward, 2, pct);
        wait(10, msec);
        break;
        }
    }

    Brain.Screen.setCursor(temp, 1);

    temp += 1;
    wait(15, msec);
    //Update every 1 millisecond per frames
    Brain.Screen.clearScreen();
  }

  return 1;
}

void LineReadCalibration::calibration(line module){

  bool setVariable = true;
  bool isCaliLight = true;
  bool loopCali = true;

  float DarkThreshold = 0;
  float LightThreshold = 0;

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
    //Threshold = (LightThreshold + DarkThreshold) / 2;
    Brain.Screen.print("Threshold is %4f", Threshold);
    wait(1.8f, sec);
  }
}