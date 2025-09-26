#ifndef PARTICLE_H
#define PARTICLE_H

#include <stdlib.h>
#include "raylib.h"

#define MAX_PARTICLES 500

typedef struct Particle {
    Vector2 pos;
    Vector2 vel;
    double size;
    double life;
    bool active;
} Particle;

void init_particle(Particle* particle, Vector2 p, Vector2 v);
void update_particle(Particle* particle, double dt);
void draw_particle(Particle* particle);

#endif // PARTICLE_H