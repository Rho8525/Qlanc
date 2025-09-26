#ifndef TIMER_H
#define TIMER_H

#include "raylib.h"

typedef struct Timer {
    double time;
    double timer;
    bool active;
} Timer;

void init_timer(Timer* timer, double t);
void update_timer(Timer* timer, double dt);

#endif // TIMER_H