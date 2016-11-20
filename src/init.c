#include "main.h"

#include <API.h>
#include "flywheel.h"
#include "control.h"
#include "shims.h"

#define UNUSED(x) (void)(x)

Pigeon * pigeon = NULL;
Flywheel * flywheel = NULL;
Encoder flywheelEncoder = NULL;

static float flywheelEstimator(float target);
static void flywheelReadied(void*);
static void flywheelActivated(void*);
static char * pigeonGets(char * buffer, int maxSize);
static void pigeonPuts(const char * message);

void initializeIO()
{
    // Note: kernal mode, scheduler paused
    // Purpose:
    //  - Set default pin modes (pinMode)
    //  - Set port states (digitalWrite)
    //  - Configure UART (usartOpen), but not LCD (lcdInit)
}

void initialize()
{
    // Note: no joystick, no link, exit promptly
    // Purpose:
    //  - Init sensors, LCDs, Global vars, IMEs
    flywheelEncoder = encoderInit(3, 4, true);

    pigeon = pigeonInit(pigeonGets, pigeonPuts, millis);

    FlywheelSetup flywheelSetup =
    {
        .id = "flywheel",
        .pigeon = pigeon,

        .gearing = 1.0f,
        .smoothing = 0.2f,

        .controlSetup = tbhSetup,
        .controlUpdater = tbhUpdate,
        .controlResetter = tbhReset,
        .control = tbhInit(0.2f, 10.0f, flywheelEstimator),

        .encoderGetter = encoderGetter,
        .encoderResetter = encoderResetter,
        .encoder = encoderGetHandle(flywheelEncoder),

        .motorSetters =
        {
            motorSetter
        },
        .motors =
        {
            motorGetHandle(1, false)
        },

        .priorityReady = 2,
        .priorityActive = 2,
        .frameDelayReady = 200,
        .frameDelayActive = 60,

        .thresholdError = 10.0f,
        .thresholdDerivative = 100.0f,
        .checkCycle = 20,

        .onready = flywheelReadied,
        .onreadyHandle = NULL,
        .onactive = flywheelActivated,
        .onactiveHandle = NULL,
    };
    flywheel = flywheelInit(flywheelSetup);

    pigeonReady(pigeon);
}

static float
flywheelEstimator(float target)
{
    return 18.195f + 2.2052e-5f * target * target;
}

static void
flywheelReadied(void * handle)
{
    UNUSED(handle);
}

static void
flywheelActivated(void * handle)
{
    UNUSED(handle);
}

static char *
pigeonGets(char * buffer, int maxSize)
{
    return fgets(buffer, maxSize, stdout);
}

static void
pigeonPuts(const char * message)
{
    puts(message);
}
