#include "stdlib.h"
#include "math.h"
#include "enemy.h"

void init_enemy(Enemy* enemy, Vector2 p) {
    if (enemy != NULL) {
        enemy->pos = p;
        enemy->vel = (Vector2) { 0, 0 };
    }
}

void update_enemy(Enemy* enemy, double dt, Vector2 target) {
    if (enemy != NULL) {
        double angle = atan2(target.y - enemy->pos.y, target.x - enemy->pos.x);
        enemy->vel.x *= 0.9;
        enemy->vel.y *= 0.9;
        enemy->vel.x = cos(angle) * 200.0;
        enemy->vel.y = sin(angle) * 200.0;

        enemy->pos.x += enemy->vel.x * dt;
        enemy->pos.y += enemy->vel.y * dt;
    }
}

void draw_enemy(Enemy* enemy) {
    if (enemy != NULL) {
        DrawCircleV(enemy->pos, enemy->csize, MAROON);
    }
}