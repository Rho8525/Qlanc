#include "stdlib.h"
#include "stdio.h"
#include "raylib.h"
#include "raymath.h"
#include "player.h"
#include "barrier.h"
#include "enemy.h"
#include "timer.h"

const int width = 800;
const int height = 450;

Timer spawn_enemy;

Player player;

Barrier* barriers[MAX_BARRIERS];
Enemy* enemies[MAX_ENEMIES];

int main(void) {

    InitWindow(width, height, "Qlanc");

    init_timer(&spawn_enemy, 0.5);

    init_player(&player, (Vector2) { 0, 0 });

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        double dt = GetFrameTime();

        update_timer(&spawn_enemy, dt);

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

        update_player(&player, dt);

        player.fwd = 0;
        player.dir = 0;
        if (IsKeyDown(KEY_W)) player.fwd -= 1;
        if (IsKeyDown(KEY_S)) player.fwd += 1;
        if (IsKeyDown(KEY_A)) player.dir -= 1;
        if (IsKeyDown(KEY_D)) player.dir += 1;

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

        for (int i=0; i<MAX_ENEMIES; i++) {
            if (enemies[i] != NULL) {
                update_enemy(enemies[i], dt, player.pos);
                if (!enemies[i]->is_active) {
                    free(enemies[i]);
                    enemies[i] = NULL;
                }
            }
        }

        BeginDrawing();

        ClearBackground(RAYWHITE);

        char label[20];
        sprintf(label, "%f", spawn_enemy.timer);
        DrawText(label, 10, 10, 16, BLACK);

        draw_player(&player);

        for (int i=0; i<MAX_ENEMIES; i++) {
            if (enemies[i] != NULL) {
                draw_enemy(enemies[i]);
            }
        }

        for (int i=0; i<MAX_BARRIERS; i++) {
            if (barriers[i] != NULL) {
                draw_barrier(barriers[i]);
            }
        }

        EndDrawing();
    }

    CloseWindow();

    for (int i=0; i<MAX_ENEMIES; i++) {
        if (enemies[i] != NULL) free(enemies[i]);
    }

    for (int i=0; i<MAX_BARRIERS; i++) {
        if (barriers[i] != NULL) free(barriers[i]);
    }

    return 0;
}