#include "particle.h"

void init_particle(Particle* particle, Vector2 p, Vector2 v) {
    if (particle != NULL) {
        particle->pos = p;
        particle->vel = v;
        particle->size = 3.0;
        particle->life = 1.0;
        particle->active = true;
    }
}

void update_particle(Particle* particle, double dt) {
    if (particle != NULL) {
        particle->pos.x += particle->vel.x * dt;
        particle->pos.y += particle->vel.y * dt;

        particle->vel.x *= 0.98;
        particle->vel.y *= 0.98;

        particle->life -= 0.01;

        if (particle->life <= 0) particle->active = false;
    }
}

void draw_particle(Particle* particle) {
    if (particle != NULL) {
        Color c = Fade(RED, particle->life);
        DrawCircleV(particle->pos, particle->size, c);
    }
}