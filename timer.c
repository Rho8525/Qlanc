#include "timer.h"

void init_timer(Timer* timer, double t) {
    timer->time = t;
    timer->timer = 0.0;
    timer->active = false;
}

void update_timer(Timer* timer, double dt) {
    if (!timer->active) timer->timer += dt;
    if (timer->timer >= timer->time) {
        timer->timer = 0.0;
        timer->active = true;
    }
}