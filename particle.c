#include "particle.h"

void init_particle(Particle* particle, Vector2 p, Vector2 v, double s) {
    particle->pos = p;
    particle->vel = v;
    particle->size = s;
    particle->life = 1.0;
    particle->active = true;
}

void update_particle(Particle* particle, double dt) {
    particle->pos.x += particle->vel.x;
    particle->pos.y += particle->vel.y;

    particle->vel.x *= 0.98;
    particle->vel.y *= 0.98;

    particle->life -= 0.01;

    if (particle->life <= 0) particle->active = false;
}

void draw_particle(Particle* particle) {
    Color c = Fade(RED, particle->life);
    DrawCircleV(particle->pos, particle->size, c);
}