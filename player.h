#ifndef PLAYER_H
#define PLAYER_H

#include <stdlib.h>
#include "raylib.h"
#include "raymath.h"
#include "enemy.h"

typedef struct Player {
    Vector2 pos; // position
    Vector2 vel; // velocity
    double speed; // speed
    int dir; // x direction
    int fwd; // y direction
    bool can_barrier; // can deploy barrier
    bool is_barriering; // is it about to deploy barrier
    double size; // base size
    double csize; // current size
    int layer; // layer
} Player; // player class

void init_player(Player* player, Vector2 p); // function for initializing player
void update_player(Player* player, double dt); // function for updating player
void draw_player(Player* player); // function for drawing player
bool collide_with_enemy(Player* player, Enemy* enemy); // function for checking if its colliding with enemy

#endif // PLAYER_H
