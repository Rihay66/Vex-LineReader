#include "LineReaderLibrary.h"

using namespace ReadLineLibrary;

//Create vex classes
competition _competition;
controller _controller;

//This type is only used locally in this script
bool setVariable;

//Call sd card class to a specific function and this function is local
void saveFile(LineReadCalibration* cal, bool toOverwrite, float thresholdArr[3]){
  SDCARD* ptr = new SDCARD(toOverwrite, thresholdArr, cal);
  wait(2, sec);
  delete ptr;
}

int LRH::Init(line lineArray[3], LRH _lrh){
  //Initialize
  if(!checkForFile()){
    return 1;
  }
  LineReadCalibration* cal = new LineReadCalibration;

  //Depending on the result of file check it will either
  //Make a new file or read/overwrite file if it exists
  if(!fileExist){
    //File doesn't exist
    for(int i = 0; i < 3;){
      int x = 1 + i;

      Brain.Screen.clearScreen();
      Brain.Screen.setCursor(1, 1);
      Brain.Screen.print("In loop %d", x);
      cal->Threshold[i] = cal->calibration(lineArray[i], x, _lrh);
      i++;

      Brain.Screen.clearScreen();
      Brain.Screen.print("CALIBRATION COMPLETED");

      wait(2, sec);

      //Save to file the treshold array
      saveFile(cal, cal->toOverwrite, cal->Threshold);
    }

  }else{
    //File does exist
    saveFile(cal, cal->toOverwrite, cal->Threshold);
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print("FILE ALREADY EXISTS");
  }

  Brain.Screen.newLine();
  Brain.Screen.print("FILE check done");
  
  //Free memory
  for(int i = 0; i < 3;){
    trArray[i] = cal->Threshold[i];
    i++;
  }
  
  delete cal;

  wait(4, sec);

  //Confirm class completion
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print("Calibration system complete");

  return 0;
}


bool LRH::overwriteOption(){

  Brain.Screen.newLine();
  Brain.Screen.print("Press B for overwrite and X to read current file");

  while(1){
    if(_controller.ButtonB.pressing()){
      // Button B for yes to overwrite
      return true;
    }else if(_controller.ButtonX.pressing()){
      // Button X for no to overwrite
      break;
    }
  }
  return false;
}

void LRH::userControl(void){
  while(1){
    if(_controller.ButtonA.pressing()){
      setVariable = true; 
    }else{
      setVariable = false;
    }
  }
}

bool LRH::moduleDetectionInverted(line module, float thresh){

  //Used to detect line reader value on inverted surfaces

  if(module.value(analogUnits::pct) < thresh){
    //Dark surface detection
    return true;
  }else{
    //Light surface detection
    return false;
  }
}

bool LRH::moduleDetection(line module, float thresh){

  //Used to detect line reader value

  if(module.value(analogUnits::pct) > thresh){
    //Dark detection
    return true;
  }else{
    //Light detection
    return false;
  }
}

float LineReadCalibration::calibration(line module, int x, LRH _lrh){

  setVariable = false;
  bool isCaliLight = true;
  bool loopCali = true;

  float DarkThreshold = 0;
  float LightThreshold = 0;

  float tr;

  wait(2, sec);
  
  _competition.drivercontrol(_lrh.userControl);

  while(loopCali == true){
    //Updating every 25 millisecond

    //Clear screen to make room for other responses and remove the already acknowledged values
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print("Module detection value is %d and in loop %d", module.value(analogUnits::pct), x);

    if(setVariable == true && isCaliLight == true){
      Brain.Screen.clearScreen();
      LightThreshold = module.value(percentUnits::pct);

      setVariable = false;

      Brain.Screen.setCursor(1, 1);
      Brain.Screen.print("Light set and light val is %4f", LightThreshold);

      wait(3, sec);

      isCaliLight = false;
    }else if(setVariable == true && isCaliLight == false){
      Brain.Screen.clearScreen();
      setVariable = false;
      DarkThreshold = module.value(percentUnits::pct);

      Brain.Screen.setCursor(1, 1);
      Brain.Screen.print("Dark set and dark val is %4f", DarkThreshold);

      wait(2, sec);
      Brain.Screen.clearScreen();
      loopCali = false;
    }
    wait(150, msec);
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
SDCARD::SDCARD(bool toOverwrite, float arr[3], LineReadCalibration* cal){
  //Init the file or load the file if it exists

  //[]Search for the file first and if not make a new one
  if(Brain.SDcard.isInserted()){

    ReadDATAFILE.open("SAVE.txt", std::ios::in);

    if(ReadDATAFILE.is_open() && !toOverwrite){
      Brain.Screen.newLine();
      //Brain.Screen.print("Save file exists and is already open");
      //Read file and set each line to the calibration threshold array
      
      Brain.Screen.clearScreen();
      Brain.Screen.setCursor(1, 1);
      Brain.Screen.print("Opening file");

      wait(2, sec);

      translateToProgram(cal);

      wait(5, sec);

    }else if(!ReadDATAFILE.is_open() || toOverwrite){
      Brain.Screen.print("Save file doesn't exist");
      wait(2, sec);

      //Init file
      WriteDATAFILE.open("SAVE.txt", std::ios::out);

      //get threshold array set to Line calirabtion threshold array
      translateToFile(arr);
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
    if(!ReadDATAFILE.is_open() || WriteDATAFILE.is_open()){
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

        uintptr_t num = (uintptr_t)tmpThreshold[x];

        Brain.Screen.print(num);
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
}

void SDCARD::translateToProgram(LineReadCalibration* cal){
  if(ReadDATAFILE.is_open()){
    Brain.Screen.newLine();
    Brain.Screen.print("Reading file...");
    Brain.Screen.newLine();

    float val;
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
      cal->Threshold[i] = tmpThreshold[i];
      uintptr_t num = (uintptr_t)cal->Threshold[i];
      Brain.Screen.print(num);
      Brain.Screen.newLine();
      i++;
    }

  }else{
    Brain.Screen.clearScreen();
    Brain.Screen.print("ERROR: FILE doesn't exist");
  }
}

void SDCARD::translateToFile(float arr[3]){

  //Translate the txt file to code and set the values to the threshold array on the LineReadCalibration class

  //set a error code for when the read can't find the existance of the txt file

  for(int i = 0; i < 3;){
    tmpThreshold[i] = arr[i];
    i++;
  }

  //Message for debug
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print("Translate complete");
}
