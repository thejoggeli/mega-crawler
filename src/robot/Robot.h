#ifndef __ROBOT__
#define __ROBOT__

#include <Arduino.h>
#include "Leg.h"
#include "CrawlerConfig.h"

class Robot {
public:

    Leg legs[NUM_LEGS];

    Robot();

    void init();
    void start();
    void update();

    bool doSimpleIK(Vector3 Q[NUM_LEGS], float phi[NUM_LEGS], float seconds);

};

#endif
