#include "main.h"
#include "flywheel.h"

void operatorControl()
{
    flywheelRun(flywheel);
    while (true)
    {
        delay(20);
    }
    // Note: never exit
}
