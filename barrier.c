#include "barrier.h"

void init_barrier(Barrier* barrier, Vector2 c, Vector2 p, Vector2 v) {
    if (barrier != NULL) {
        barrier->pos = p;
        barrier->vel = v;
        barrier->center = c;
        barrier->speed = 500.0;
        barrier->size = 5.0;
        barrier->life = 1.0;
        barrier->active = true;
    }
}

void update_barrier(Barrier* barrier, double dt) {
    if (barrier != NULL) {
        barrier->pos.x += barrier->vel.x * dt;
        barrier->pos.y += barrier->vel.y * dt;

        barrier->vel.x *= 0.93;
        barrier->vel.y *= 0.93;

        barrier->life -= 0.01;

        if (barrier->life <= 0) barrier->active = false;
    }
}

void draw_barrier(Barrier* barrier) {
    if (barrier != NULL) {
        Color c = Fade(MAROON, barrier->life);
        DrawCircleV(barrier->pos, barrier->size, c);
    }
}

void repel_barrier(Barrier* barrier, Enemy* enemy) {
    double dist = hypot(barrier->pos.x - enemy->pos.x, barrier->pos.y - enemy->pos.y);
    if (dist - barrier->size - enemy->csize <= 1) {
        double angle = atan2(enemy->pos.y - barrier->center.y, enemy->pos.x - barrier->center.x);
        double x = cos(angle) * (hypot(barrier->pos.x - barrier->center.x, barrier->pos.y - barrier->center.y) + barrier->size + enemy->csize);
        double y = sin(angle) * (hypot(barrier->pos.x - barrier->center.x, barrier->pos.y - barrier->center.y) + barrier->size + enemy->csize);
        enemy->pos = (Vector2) { barrier->center.x + x, barrier->center.y + y };
    }
}