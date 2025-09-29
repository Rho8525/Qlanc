#include <stdlib.h>
#include "raylib.h"
#include "raymath.h"
#include "player.h"
#include "particle.h"
#include "barrier.h"
#include "enemy.h"
#include "timer.h"

// window size
const int width = 800;
const int height = 450;

// create timer for spawning enemy
Timer spawn_enemy_timer;

// create player
Player player;

// create barriers and enemies container
Particle* particles[MAX_PARTICLES];
Barrier* barriers[MAX_BARRIERS];
Enemy* enemies[MAX_ENEMIES];

// create function for spawning particles
void spawn_particles(Vector2 p);

int main(void) {
    // init window
    InitWindow(width, height, "Qlanc");

    // init spawn enemy timer
    init_timer(&spawn_enemy_timer, 0.5);

    // init player
    init_player(&player, (Vector2) { 0, 0 });

    // make it 60 fps if possible
    SetTargetFPS(60);

    // main game loop
    while (!WindowShouldClose()) {
        // get delta time
        double dt = GetFrameTime();

        // update timer
        update_timer(&spawn_enemy_timer, dt);

        // spawn enemy
        if (spawn_enemy_timer.active) {
            spawn_enemy_timer.active = false;
            int spawned = 0;
            for (int i=0; i<MAX_ENEMIES && spawned < 1; i++) {
                if (enemies[i] == NULL) {
                    enemies[i] = (Enemy*)malloc(sizeof(Enemy));
                    init_enemy(enemies[i], (Vector2) { 0, 0 });
                    spawned++;
                }
            }
        }

        // update player
        update_player(&player, dt);
        
        // check if any enemy with small size collide with the player
        // if yes then destroy it
        for (int i=0; i<MAX_ENEMIES; i++) {
            if (enemies[i] != NULL) {
                if (collide_with_enemy(&player, enemies[i])) {
                    if (enemies[i]->csize <= 10) {
                        enemies[i]->is_active = false;
                    }
                }
            }
        }

        // player movement
        player.fwd = 0;
        player.dir = 0;
        if (IsKeyDown(KEY_W)) player.fwd -= 1;
        if (IsKeyDown(KEY_S)) player.fwd += 1;
        if (IsKeyDown(KEY_A)) player.dir -= 1;
        if (IsKeyDown(KEY_D)) player.dir += 1;

        // player barrier
        if (IsKeyPressed(KEY_SPACE)) {
            if (player.can_barrier) player.is_barriering = true;
            spawn_particles(player.pos);
        }

        // player deploy barrier when pressing space button
        if (player.is_barriering) {
            player.is_barriering = false;
            player.csize -= 5.0;
            if (player.csize <= 5.0) {
                player.layer--;
                player.csize = player.size;
            }
            int spawned = 0;
            for (int i=0; i<MAX_BARRIERS && spawned < 45; i++) {
                if (barriers[i] == NULL) {
                    barriers[i] = (Barrier*)malloc(sizeof(Barrier));
                    double angle = (2 * PI / 45) * spawned;
                    init_barrier(barriers[i], player.pos, player.pos, (Vector2){ cos(angle) * (double) 500.0, sin(angle) * (double) 500.0 });
                    spawned++;
                }
            }
        }

        // update particles
        for (int i=0; i<MAX_PARTICLES; i++) {
            if (particles[i] != NULL) {
                update_particle(particles[i], dt);
                if (!particles[i]->active) {
                    free(particles[i]);
                    particles[i] = NULL;
                }
            }
        }

        // update barrier
        for (int i=0; i<MAX_BARRIERS; i++) {
            if (barriers[i] != NULL) {
                update_barrier(barriers[i], dt);
                for (int j=0; j<MAX_ENEMIES; j++) {
                    if (enemies[j] != NULL) {
                        repel_barrier(barriers[i], enemies[j]);
                    }
                }
                if (!barriers[i]->active) {
                    spawn_particles(barriers[i]->pos);
                    free(barriers[i]);
                    barriers[i] = NULL;
                }
            }
        }

        // update enemy
        for (int i=0; i<MAX_ENEMIES; i++) {
            if (enemies[i] != NULL) {
                update_enemy(enemies[i], dt, player.pos);
                if (!enemies[i]->is_active) {
                    spawn_particles(enemies[i]->pos);
                    free(enemies[i]);
                    enemies[i] = NULL;
                }
            }
        }

        // start drawing on the screen
        BeginDrawing();

        // background
        ClearBackground(BLACK);

        // draw particles
        for (int i=0; i<MAX_PARTICLES; i++) {
            if (particles[i] != NULL) {
                draw_particle(particles[i]);
            }
        }

        // draw the player
        draw_player(&player);

        // draw enemies
        for (int i=0; i<MAX_ENEMIES; i++) {
            if (enemies[i] != NULL) {
                draw_enemy(enemies[i]);
            }
        }

        // draw barriers
        for (int i=0; i<MAX_BARRIERS; i++) {
            if (barriers[i] != NULL) {
                draw_barrier(barriers[i]);
            }
        }

        // stop drawing
        EndDrawing();
    }

    // close window
    CloseWindow();

    // clean containers
    for (int i=0; i<MAX_PARTICLES; i++) {
        if (particles[i] != NULL) free(particles[i]); particles[i] == NULL;
    }

    for (int i=0; i<MAX_ENEMIES; i++) {
        if (enemies[i] != NULL) free(enemies[i]); enemies[i] = NULL;
    }

    for (int i=0; i<MAX_BARRIERS; i++) {
        if (barriers[i] != NULL) free(barriers[i]); barriers[i] = NULL;
    }

    return 0;
}

// spawn particles function
void spawn_particles(Vector2 p) {
    int spawned = 0;
    for (int i=0; i<MAX_PARTICLES && spawned < 3; i++) {
        if (particles[i] == NULL) {
            particles[i] = (Particle*)malloc(sizeof(Particle));
            
            double angle = GetRandomValue(0, 359) * (PI / 180.0f);
            double speed = GetRandomValue(100.0, 300.0);
            Vector2 velocity = { cos(angle) * speed, sin(angle) * speed };

            init_particle(particles[i], p, velocity);
            spawned++;
        }
    }
}
