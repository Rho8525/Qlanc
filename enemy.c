#include "enemy.h"

void init_enemy(Enemy* enemy, Vector2 p) {
    if (enemy != NULL) {
        enemy->pos = p;
        enemy->vel = (Vector2) { 0, 0 };
        enemy->speed = 75.0;
        enemy->max_speed = 200.0;
        enemy->size = 25.0;
        enemy->csize = enemy->size;
        enemy->is_active = true;
    }
}

void update_enemy(Enemy* enemy, double dt, Vector2 target) {
    if (enemy != NULL) {
        double angle = atan2(target.y - enemy->pos.y, target.x - enemy->pos.x);
        enemy->vel.x *= 0.9;
        enemy->vel.y *= 0.9;
        enemy->vel.x = cos(angle) * (enemy->speed + (enemy->size - enemy->csize) / enemy->size * (enemy->max_speed - enemy->speed));
        enemy->vel.y = sin(angle) * (enemy->speed + (enemy->size - enemy->csize) / enemy->size * (enemy->max_speed - enemy->speed));

        enemy->pos.x += enemy->vel.x * dt;
        enemy->pos.y += enemy->vel.y * dt;

        enemy->csize -= 0.05;
        if (enemy->csize <= 5.0) {
            enemy->is_active = false;
        }
    }
}

void draw_enemy(Enemy* enemy) {
    if (enemy != NULL) {
        DrawCircleV(enemy->pos, enemy->csize, RED);
    }
}