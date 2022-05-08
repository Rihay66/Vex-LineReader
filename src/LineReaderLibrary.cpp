#include "LineReaderLibrary.h"
#include "vex.h"
#include "string"

using namespace std;
using namespace ReadLine;
using namespace vex;

bool setVariable;

controller Controller;
competition Competition;

void userControl(void){
  while(1){
    if(Controller.ButtonA.pressing()){
      setVariable = true; 
      Brain.Screen.print("BUTTON");
      wait(5, msec);
      Brain.Screen.clearScreen();
    }
  }
}

bool LineRead::moduleDetectionInverted(line module, int thresh){

  //Used to detect line reader value on inverted surfaces

  if(module.value(analogUnits::pct) < thresh){
    //Dark surface detection
    return true;
  }else{
    //Light surface detection
    return false;
  }
}

bool LineRead::moduleDetection(line module, int thresh){

  //Used to detect line reader value

  if(module.value(analogUnits::pct) > thresh){
      //Dark detection
      return true;
  }else{
    //Light detection
    return false;
  }
}

int LineRead::Update(line module1, line module2, line module3){

/*
  while(1){
    //Note: The Calibration function can be used to find the value on a surface

  
    float tr1 = 55;
    float tr2 = 53;
    float tr3 = 61;

    bool line1 = moduleDetection(module1, tr1);
    bool line2 = moduleDetection(module2, tr2);
    bool line3 = moduleDetection(module3, tr3);
    
    bool line1Inv = moduleDetectionInverted(module1, Threshold);
    bool line2Inv = moduleDetectionInverted(module2, Threshold);
    bool line3Inv = moduleDetectionInverted(module3, Threshold);
    
    //DEBUG MODE
    int temp = 1;
    
    //Testing the value of LineTrackerD
    Brain.Screen.print("%d %d %d ", line1, line2, line3);
    Brain.Screen.print(" %d %d %d", module1.value(analogUnits::pct), module2.value(analogUnits::pct), module3.value(analogUnits::pct));
    Brain.Screen.setCursor(temp, 1);

    if(line1 && line2 && line3){
      Brain.Screen.print("Center");
      Motor1.spin(vex::forward, 2, pct);
      Motor10.spin(vex::forward, 2, pct);
      break;
    }else{
      if(line1 && line2 && !line3){
        Brain.Screen.print("Left");
        Motor1.spin(vex::forward, 2, pct);
        Motor10.spin(vex::forward, 1, pct);
        wait(10, msec);
        break;
      }else if(!line1 && line2 && line3){
        Brain.Screen.print("Right");
        Motor1.spin(vex::forward, 1, pct);
        Motor10.spin(vex::forward, 2, pct);
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
*/
  return 1;
}

int LineReadCalibration::calibration(line module, int i){

  setVariable = false;
  bool isCaliLight = true;
  bool loopCali = true;

  float DarkThreshold = 0;
  float LightThreshold = 0;

  float tr;

  wait(2, sec);
  
  Competition.drivercontrol(userControl);

  while(loopCali == true){
    //Updating every 25 millisecond

    wait(250, msec);

    //Clear screen to make room for other responses and remove the already acknowledged values
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print("Module detection value is %d and in loop %d", module.value(analogUnits::pct), i);

    if(setVariable == true && isCaliLight == true){
      Brain.Screen.clearScreen();
      LightThreshold = module.value(analogUnits::pct);

      setVariable = false;

      Brain.Screen.setCursor(1, 1);
      Brain.Screen.print("Light set and light val is %4f", LightThreshold);

      wait(3, sec);

      isCaliLight = false;
    }else if(setVariable == true && isCaliLight == false){
      Brain.Screen.clearScreen();
      DarkThreshold = module.value(analogUnits::pct);

      Brain.Screen.setCursor(1, 1);
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
    tr = (LightThreshold + DarkThreshold) / 2;
    Brain.Screen.print("Threshold is %4f", tr);
    wait(1.8f, sec);
    return tr;
  }

  return 0;
}

//SD card constructor which can be created to initialize or do something while the object exists
SDCARD::SDCARD(LineReadCalibration cal){
  //Init the file or load the file if it exists

  //[]Search for the file first and if not make a new one
  if(Brain.SDcard.isInserted()){

    ReadDATAFILE.open("SAVE.txt", std::ios::in);

    if(ReadDATAFILE.is_open() && !cal.toOverwrite){
      Brain.Screen.newLine();
      //Brain.Screen.print("Save file exists and is already open");
      //Read file and set each line to the calibration threshold array
      
      Brain.Screen.clearScreen();
      Brain.Screen.setCursor(1, 1);
      Brain.Screen.print("Opening file");

      wait(2, sec);

      wait(5, sec);
      //ReadDATAFILE.getline(tmp, 30);

      //Brain.Screen.newLine();
     // Brain.Screen.print("Reading from file: %s ", tmp);

    }else{
      Brain.Screen.print("Save file doesn't exist making");
      //Init file
      WriteDATAFILE.open("SAVE.txt", std::ios::out);

      //get threshold array set to Line calirabtion threshold array
      translateToFile(cal);
    }
  }else{
    Brain.Screen.print("ERROR: no SD Card inserted");
  }
  //[]Store the values of the thresholds

  //[]if file exist call translate function
}

//SD card destructor which can destroy the created object and do last functions
SDCARD::~SDCARD(){
  //Save the file
  if(Brain.SDcard.isInserted()){
    //Save file if read is not available
    if(!ReadDATAFILE.is_open()){
      Brain.Screen.newLine();
      Brain.Screen.print("Saving file");

      //get the threshold array from the SD card class and put into file

      for(int x = 0; x < 3;){
        WriteDATAFILE << tmpThreshold[x] << endl;
        x++;
      }
      
      //Check for each value in the file

      wait(2, sec);
      //debug
      Brain.Screen.clearScreen();
      Brain.Screen.setCursor(1, 1);
      for(int x = 0; x < 3;){
        Brain.Screen.print(tmpThreshold[x]);
        Brain.Screen.newLine();
        x++;
      }
      
      WriteDATAFILE.close();

      Brain.Screen.newLine();
      Brain.Screen.print("FILE SAVED");
    }
  }else{
    Brain.Screen.print("ERROR: no SD Card inserted");
  }
  //[] Find the file

  //[] Read and display what it contains

  //[] call the translate function to set the Threshold
}

void SDCARD::translateToProgram(LineReadCalibration cal){
  if(ReadDATAFILE.is_open()){
    Brain.Screen.newLine();
    Brain.Screen.print("Reading file...");

    int val;
    string readVal;

    for(int i = 0; i < 3;){
      getline(ReadDATAFILE, readVal);

      istringstream iss(readVal);

      if(iss >> val){
        tmpThreshold[i] = val;
        i++;
      }
    }

    for(int i = 0; i < 3;){
      cal.Threshold[i] = tmpThreshold[i];
      Brain.Screen.print(cal.Threshold[i]);
      i++;
    }

  }else{
    Brain.Screen.clearScreen();
    Brain.Screen.print("ERROR: FILE doesn't exist");
  }
}

void SDCARD::translateToFile(LineReadCalibration cal){

  //Translate the txt file to code and set the values to the threshold array on the LineReadCalibration class

  //set a error code for when the read can't find the existance of the txt file

  for(int i = 0; i < 3;){
    tmpThreshold[i] = cal.Threshold[i];
    i++;
  }

  //Message for debug
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print("Translate complete");
}

bool LineReadCalibration::overwriteOption(){

  Brain.Screen.newLine();
  Brain.Screen.print("Press B for overwrite and X to read current file");

  while(1){
    if(Controller.ButtonB.pressing()){
      // Button B for yes to overwrite
      return true;
    }else if(Controller.ButtonX.pressing()){
      // Button X for no to overwrite
      break;
    }
  }
  return false;
}