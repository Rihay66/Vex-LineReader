#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
line LineTrackerC = line(Brain.ThreeWirePort.C);
line LineTrackerD = line(Brain.ThreeWirePort.D);
line LineTrackerE = line(Brain.ThreeWirePort.E);
motor Motor10 = motor(PORT10, ratio36_1, true);
motor Motor1 = motor(PORT1, ratio36_1, false);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}