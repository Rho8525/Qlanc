#ifndef BARRIER_H
#define BARRIER_H

#include "raylib.h"

#define MAX_BARRIERS 500

typedef struct Barrier {
    Vector2 pos;
    Vector2 vel;
    double size;
    double life;
    bool active;
} Barrier;

void init_barrier(Barrier* barrier, Vector2 p, Vector2 v);
void update_barrier(Barrier* barrier, double dt);
void draw_barrier(Barrier* barrier);

#endif // BARRIER_H
