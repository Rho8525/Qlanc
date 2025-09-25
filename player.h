#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

typedef struct Player {
    Vector2 pos;
    Vector2 vel;
    double speed;
    int dir;
    int fwd;
    bool can_barrier;
    bool is_barriering;
    double size;
    double csize;
    int layer;
} Player;

void init_player(Player* player, Vector2 p);
void update_player(Player* player, double dt);
void draw_player(Player* player);
void player_barrier(Player* player);

#endif // PLAYER_H