#include "vex.h"
#include "fstream"
#include "iostream"
#include "sstream"

using namespace vex;
using namespace std;

namespace ReadLine{
  class LRH{
    public:
      //Calls the other classes and does the same thing as the current code on 'main.cpp'
      bool Input;
      bool fileExist;

      //Initialize program
      void Init(line* lineArray[3]);

      //Handles user input
      static void userControl(void);
      bool overwriteOption();

      //Create vex classes
      competition _competition;
      static controller _controller;
    private:
      void checkForFile(){
        //Make ifstream class used to read for a file name but not make one
        ifstream DATAFILE;
        DATAFILE.open("SAVE.txt", ios::in);

        if(DATAFILE.is_open()){
          Brain.Screen.print("Save file found");
          if(overwriteOption()){
            fileExist = true;
          }else{
            fileExist = false;
          }
        }else{
          Brain.Screen.print("No save file");
          fileExist = false;
        }

        //Close the check for file func
        DATAFILE.close();

        //Debug
        wait(1.5, sec);
      };
  };

  class LineReadCalibration
  {
    public:
    //Note: These constructor and destructor will be used later
    //  LineReadCalibration();
    //  ~LineReadCalibration();

      //-----------Used for Calibration--------------
      //Note: These will be changed as futher revision are made so some of these values may even not be used or removed

      // Make values or variables
      float Threshold[3];

      bool toOverwrite;

      float calibration(line module, int i, LRH _lrh); //Function to do calibration of the line reader
  };

  class LineRead{
    public:
      //int LateUpdate(void); //Used to update function and variables very late and will be run seperately but parallel to other loops
      float moduleArray[3];
      //---------------------------------------------
      //Used to return a value of what the line module 'sees'
      bool moduleDetection(line module, float thresh);//returnable
      bool moduleDetectionInverted(line module, float thresh);//returnable
  };

  class SDCARD{
    public:
      std::ifstream ReadDATAFILE;
      std::ofstream WriteDATAFILE;

      float tmpThreshold[3];

      SDCARD(bool toOverwrite, float arr[3], LineReadCalibration* cal); //Load file
      ~SDCARD(); //Save file

      void translateToFile(float arr[3]); //Read File and return a value
      void translateToProgram(LineReadCalibration* cal);
  };

};