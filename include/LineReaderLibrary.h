#include "vex.h"
#include "fstream"
#include "iostream"

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

      //---------------------------------------------
      //Used to return a value of what the line module 'sees'
      bool moduleDetection(line module, int thresh);//returnable
      bool moduleDetectionInverted(line module, int thresh);//returnable

      void calibration(line module); //Function to do calibration of the line reader
  };

  class LineRead{
    public:
      int LateUpdate(void); //Used to update function and variables very late and will be run seperately but parallel to other loops
      int Update(line module1, line module2, line module3); //Used to update functions and variables
  };

  class SDCARD{
    public:
      std::ifstream ReadDATAFILE;
      std::ofstream WriteDATAFILE;

      SDCARD(); //Load file
      ~SDCARD(); //Save file

      int translate(); //Read File and return a value
  };
};