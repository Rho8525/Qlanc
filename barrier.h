#ifndef BARRIER_H
#define BARRIER_H

#include "stdlib.h"
#include "raylib.h"
#include "raymath.h"
#include "enemy.h"

#define MAX_BARRIERS 500

typedef struct Barrier {
    Vector2 pos;
    Vector2 vel;
    Vector2 center;
    double speed;
    double size;
    double life;
    bool active;
} Barrier;

void init_barrier(Barrier* barrier, Vector2 c, Vector2 p, Vector2 v);
void update_barrier(Barrier* barrier, double dt);
void draw_barrier(Barrier* barrier);
void repel_barrier(Barrier* barrier, Enemy* enemy);

#endif // BARRIER_H
