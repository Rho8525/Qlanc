#include "stdlib.h"
#include "barrier.h"

void init_barrier(Barrier* barrier, Vector2 p, Vector2 v) {
    if (barrier != NULL) {
        barrier->pos = p;
        barrier->vel = v;
        barrier->size = 5.0;
        barrier->life = 1.0;
        barrier->active = true;
    }
}

void update_barrier(Barrier* barrier, double dt) {
    if (barrier != NULL) {
        barrier->pos.x += barrier->vel.x * dt;
        barrier->pos.y += barrier->vel.y * dt;

        barrier->vel.x *= 0.9;
        barrier->vel.y *= 0.9;

        barrier->life -= 0.01;

        if (barrier->life <= 0) barrier->active = false;
    }
}

void draw_barrier(Barrier* barrier) {
    if (barrier != NULL) {
        Color c = Fade(MAROON, barrier->life);
        DrawCircleV(barrier->pos, barrier->size, c);
    }
}