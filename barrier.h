#ifndef BARRIER_H
#define BARRIER_H

#include <stdlib.h>
#include "raylib.h"
#include "raymath.h"
#include "enemy.h"

#define MAX_BARRIERS 500 // max barrier node in the game

typedef struct Barrier {
    Vector2 pos; // position
    Vector2 vel; // velocity
    Vector2 center; // barrier center
    double size; // size
    double life; // opacity, if it get to zero, the barrier become inactive
    bool active; // active/inactive
} Barrier; // barrier class, its barrier node actually

void init_barrier(Barrier* barrier, Vector2 c, Vector2 p, Vector2 v); // function for initializing barrier
void update_barrier(Barrier* barrier, double dt); // function for updating barrier
void draw_barrier(Barrier* barrier); // function for drawing barrier node
void repel_barrier(Barrier* barrier, Enemy* enemy); // function for checking it it collide with enemy, if yes it will keep the enemy outside from the barrier center

#endif // BARRIER_H
