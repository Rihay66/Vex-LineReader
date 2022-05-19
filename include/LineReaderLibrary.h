#include "LRH.h"

using namespace LineReadHeader;

namespace ReadLineLibrary{

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

      float calibration(line module, int i, LRH _lrh); //Function to do calibration of the line reader
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