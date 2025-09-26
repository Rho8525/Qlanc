#include "player.h"

void init_player(Player* player, Vector2 p) {
    if (player != NULL) {
        player->pos = p;
        player->vel = (Vector2) { 20, 20 };
        player->speed = 200.0;
        player->dir = 0;
        player->fwd = 0;
        player->can_barrier = true;
        player->is_barriering = false;
        player->size = 25.0;
        player->csize = player->size;
        player->layer = 3;
    }
};

void update_player(Player* player, double dt) {
    if (player != NULL) {
        Vector2 input = { (float) player->dir, (float) player->fwd };
        if (input.x != 0 || input.y != 0) {
            input = Vector2Normalize(input);
            player->vel.x = input.x * player->speed;
            player->vel.y = input.y * player->speed;
        }

        player->pos.x += player->vel.x * dt;
        player->pos.y += player->vel.y * dt;

        player->vel.x *= 0.9;
        player->vel.y *= 0.9;

        if (player->csize <= player->size) {
            player->csize += 0.03;
        }

        if (player->csize > player->size) player->csize = player->size;
    }
}

void draw_player(Player* player) {
    if (player != NULL) {
        DrawCircleV(player->pos, player->csize, MAROON);
    }
}