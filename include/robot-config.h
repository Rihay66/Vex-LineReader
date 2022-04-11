using namespace vex;

extern brain Brain;

// VEXcode devices
extern line LineTrackerC;
extern line LineTrackerD;
extern line LineTrackerE;
extern motor Motor10;
extern motor Motor1;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );