#include "stdlib.h"
#include "stdio.h"
#include "raylib.h"
#include "raymath.h"
#include "player.h"
#include "barrier.h"
#include "enemy.h"
#include "timer.h"

// window size
const int width = 800;
const int height = 450;

Timer spawn_enemy;

// create player
Player player;

// create barriers and enemies container
Barrier* barriers[MAX_BARRIERS];
Enemy* enemies[MAX_ENEMIES];

int main(void) {
    // init window
    InitWindow(width, height, "Qlanc");

    // init spawn enemy timer
    init_timer(&spawn_enemy, 0.5);

    // init player
    init_player(&player, (Vector2) { 0, 0 });

    // make it 60 fps if possible
    SetTargetFPS(60);

    // main game loop
    while (!WindowShouldClose()) {
        // get delta time
        double dt = GetFrameTime();

        // update timer
        update_timer(&spawn_enemy, dt);

        // spawn enemy
        if (spawn_enemy.active) {
            spawn_enemy.active = false;
            int spawned = 0;
            for (int i=0; i<MAX_ENEMIES && spawned < 1; i++) {
                if (enemies[i] == NULL) {
                    enemies[i] = (Enemy*)malloc(sizeof(Enemy));
                    double angle = (2 * PI / 15) * spawned;
                    init_enemy(enemies[i], (Vector2) { 0, 0 });
                    spawned++;
                }
            }
        }

        // update player
        update_player(&player, dt);

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
        }

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
                    free(enemies[i]);
                    enemies[i] = NULL;
                }
            }
        }

        // start drawing on the screen
        BeginDrawing();

        ClearBackground(RAYWHITE);

        // draw spawn enemy timer
        char label[20];
        sprintf(label, "%f", spawn_enemy.timer);
        DrawText(label, 10, 10, 16, BLACK);

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
    for (int i=0; i<MAX_ENEMIES; i++) {
        if (enemies[i] != NULL) free(enemies[i]);
    }

    for (int i=0; i<MAX_BARRIERS; i++) {
        if (barriers[i] != NULL) free(barriers[i]);
    }

    return 0;
}