#ifndef FLYWHEEL_H_
#define FLYWHEEL_H_

#include <stdbool.h>
#include "pigeon.h"
#include "control.h"
#include "shims.h"

#ifdef __cplusplus
extern "C" {
#endif



// Typedefs {{{

typedef void (*FlywheelHandler)(void*);

struct Flywheel;
typedef struct Flywheel Flywheel;

typedef enum
FlywheelController
{
    FLYWHEEL_BANGBANG,
    FLYWHEEL_PID,
    FLYWHEEL_TBH
}
FlywheelController;

typedef struct
FlywheelSetup
{
    char * id;
    Pigeon * pigeon;

    float gearing;
    float smoothing;

    ControlSetup controlSetup;
    ControlUpdater controlUpdater;
    ControlResetter controlResetter;
    ControlHandle control;

    EncoderGetter encoderGetter;
    EncoderResetter encoderResetter;
    EncoderHandle encoder;

    MotorSetter motorSetters[8];
    MotorHandle motors[8];

    unsigned int priorityReady;
    unsigned int priorityActive;
    unsigned long frameDelayReady;
    unsigned long frameDelayActive;

    float thresholdError;
    float thresholdDerivative;
    int checkCycle;

    FlywheelHandler onready;
    void * onreadyHandle;
    FlywheelHandler onactive;
    void * onactiveHandle;
}
FlywheelSetup;

// }}}



// Methods {{{

Flywheel *
flywheelInit(FlywheelSetup setup);

void
flywheelRun(Flywheel * flywheel);

void
flywheelSet(Flywheel * flywheel, float rpm);

void
waitUntilFlywheelReady(Flywheel * flywheel, const unsigned long blockTime);

// }}}



// End C++ export structure
#ifdef __cplusplus
}
#endif

// End include guard
#endif
