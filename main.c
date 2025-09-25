#include "stdlib.h"
#include "math.h"
#include "raylib.h"
#include "player.h"
#include "barrier.h"
#include "enemy.h"

const int width = 800;
const int height = 450;

Player player;
Enemy enemy;

Barrier* barriers[MAX_BARRIERS];

int main(void) {

    InitWindow(width, height, "RHALQ");

    init_player(&player, (Vector2) { 0, 0 });

    init_enemy(&enemy, (Vector2) { 0, 0 });

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        double dt = GetFrameTime();

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
            int spawned = 0;
            for (int i=0; i<MAX_BARRIERS && spawned < 15; i++) {
                if (barriers[i] == NULL) {
                    barriers[i] = (Barrier*)malloc(sizeof(Barrier));
                    double angle = (2 * PI / 15) * spawned;
                    init_barrier(barriers[i], player.pos, (Vector2){ cos(angle) * (double) 500.0, sin(angle) * (double) 500.0 });
                    spawned++;
                }
            }
        }

        for (int i=0; i<MAX_BARRIERS; i++) {
            if (barriers[i] != NULL) {
                update_barrier(barriers[i], dt);
                if (!barriers[i]->active) {
                    free(barriers[i]);
                    barriers[i] = NULL;
                }
            }
        }

        update_enemy(&enemy, dt, player.pos);

        BeginDrawing();

        ClearBackground(RAYWHITE);

        draw_player(&player);

        for (int i=0; i<MAX_BARRIERS; i++) {
            if (barriers[i] != NULL) {
                draw_barrier(barriers[i]);
            }
        }
        
        draw_enemy(&enemy);

        EndDrawing();
    }

    CloseWindow();

    for (int i=0; i<MAX_BARRIERS; i++) {
        if (barriers[i] != NULL) free(barriers[i]);
    }

    return 0;
}