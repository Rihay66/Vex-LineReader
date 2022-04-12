#include "vex.h"

using namespace vex;

namespace ReadLine{
  class LineReadModule
  {
    public:
      // Make values or variables
      // bool isCalib;
      bool setVariable;

      //-----------Used for Calibration--------------
      //Note: These will be changed as futher revision are made so some of these values may even not be used or removed
      bool isCaliLight;
      bool loopCali;

      float DarkThreshold;
      float LightThreshold;

      float Threshold;
      //---------------------------------------------
      //Used to return a value of what the line module 'sees'
      bool moduleDetection(line module, int thresh);//returnable
      bool moduleDetectionInverted(line module, int thresh);//returnable

      void calibration(line module); //Function to do calibration of the line reader

      int LateUpdate(void); //Used to update function and variables very late and will be run seperately but parallel to other loops
      int Update(line module1, line module2, line module3); //Used to update functions and variables
  };
};