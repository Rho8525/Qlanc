#ifndef ENEMY_H
#define ENEMY_H

#include <stdlib.h>
#include "raylib.h"
#include "raymath.h"

#define MAX_ENEMIES 500 // max enemies in the game

typedef struct Enemy {
    Vector2 pos; // position
    Vector2 vel; // velocity
    double speed; // speed
    double max_speed; // max speed 
    double size; // base size
    double csize; // current size
    bool is_active; // is alive
} Enemy; // enemy class

// it got max speed because as the enemy shrink it become more faster

void init_enemy(Enemy* enemy, Vector2 p); // function for initialize enemy
void update_enemy(Enemy* enemy, double dt, Vector2 target); // function to updating enemy
void draw_enemy(Enemy* enemy); // function to draw enemy

#endif // ENEMY_H
