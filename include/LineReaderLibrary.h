#include "vex.h"
#include "fstream"
#include "iostream"
#include "sstream"

using namespace vex;

namespace ReadLine{
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
      bool overwriteOption();

      float calibration(line module, int i); //Function to do calibration of the line reader
  };

  class LineRead{
    public:
      //int LateUpdate(void); //Used to update function and variables very late and will be run seperately but parallel to other loops
      int Update(line modules1, line module2, line module3, float thresholdArr[3]); //Used to update functions and variables

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