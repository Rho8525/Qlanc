#ifndef ENEMY_H
#define ENEMY_H

#include "stdlib.h"
#include "raylib.h"
#include "raymath.h"

#define MAX_ENEMIES 500

typedef struct Enemy {
    Vector2 pos;
    Vector2 vel;
    double size;
    double csize;
    bool is_active;
} Enemy;

void init_enemy(Enemy* enemy, Vector2 p);
void update_enemy(Enemy* enemy, double dt, Vector2 target);
void draw_enemy(Enemy* enemy);

#endif // ENEMY_H