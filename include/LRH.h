#include "vex.h"
#include "fstream"
#include "iostream"
#include "sstream"

using namespace vex;
using namespace std;

namespace LineReadHeader{
  class LRH{
    public:
      //Initialize program
      virtual int Init(line lineArray[3], LRH _lrh);

      //Handles user input
      static void userControl(void);

      //Public array used for line threshold 
      float trArray[3];

      //---------------------------------------------
      //Used to return a value of what the line module 'sees'
      bool moduleDetection(line module, float thresh);//returnable
      bool moduleDetectionInverted(line module, float thresh);//returnable

    private:     
      //Calls the other classes and does the same thing as the current code on 'main.cpp'
      bool Input;
      bool fileExist; 

      //Check for user input option to overwrite save file if it exists
      bool overwriteOption();

      //Private function to check for file (Only used in this class)
      //Note: don't use the returning value of this function mearly call the function like a void func
      bool checkForFile(){
        //Make ifstream class used to read for a file name but not make one
        if(Brain.SDcard.isInserted()){
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

          return true;
        }else{
          Brain.Screen.clearScreen();
          Brain.Screen.setCursor(1, 1);
          Brain.Screen.print("ERROR: NO SD CARD");
          return false;
        }
      };
  };
}