#ifndef MAIN_H_
#define MAIN_H_

#include <API.h>

#include "pigeon.h"
#include "flywheel.h"

#ifdef __cplusplus
extern "C" {
#endif



// Competition:

void autonomous();
void initializeIO();
void initialize();
void operatorControl();


// Robot:

extern Pigeon * pigeon;
extern Flywheel * flywheel;
extern Encoder flywheelEncoder;



// End C++ export structure
#ifdef __cplusplus
}
#endif

#endif
