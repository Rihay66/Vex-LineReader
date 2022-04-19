using namespace vex;

extern brain Brain;

// VEXcode devices
extern line LineTrackerA;
extern line LineTrackerB;
extern line LineTrackerC;
extern motor Motor10;
extern motor Motor1;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );