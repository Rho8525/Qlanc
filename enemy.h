#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"

typedef struct Enemy {
    Vector2 pos;
    Vector2 vel;
    double size;
    double csize;
} Enemy;

void init_enemy(Enemy* enemy, Vector2 p);
void update_enemy(Enemy* enemy, double dt, Vector2 target);
void draw_enemy(Enemy* enemy);

#endif // ENEMY_H