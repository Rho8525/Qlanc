#ifndef PARTICLE_H
#define PARTICLE_H

#include <stdlib.h>
#include "raylib.h"

#define MAX_PARTICLES 500 // max particle allowed in the game

typedef struct Particle {
    Vector2 pos; // position
    Vector2 vel; // velocity
    double size; // size
    double life; // opacity
    bool active; // is active/inactive
} Particle; // particle class

void init_particle(Particle* particle, Vector2 p, Vector2 v); // function for initializing particle
void update_particle(Particle* particle, double dt); // function for updating particle
void draw_particle(Particle* particle); // function for drawing particle

#endif // PARTICLE_H
