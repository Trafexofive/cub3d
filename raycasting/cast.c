
#include "../inc/draw.h"
#include "../inc/macros.h"
#include "../inc/mlx_struct.h"
#include "../inc/struct.h"
#include <math.h>
#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAP_W 8
#define MAP_H 8
#define SCREEN_W (MAP_W * TILE_SIZE * 1.7)
#define SCREEN_H (MAP_H * TILE_SIZE * 1.7)

int world_map[MAP_H][MAP_W] = {
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 0, 1, 0, 1},
    {1, 0, 1, 0, 0, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1}
};

void draw_line2(t_vector vector, t_info *info) {
    int x1 = vector.start.x;
    int y1 = vector.start.y;
    int x2 = vector.end.x;
    int y2 = vector.end.y;
    int dx = abs(x2 - x1), sx = x1 < x2 ? 1 : -1;
    int dy = -abs(y2 - y1), sy = y1 < y2 ? 1 : -1;
    int err = dx + dy, e2;

    while (1) {
        mlx_pixel_put(info->mlx->mlx, info->mlx->mlx_win, x1, y1, COLOR);
        if (x1 == x2 && y1 == y2)
            break;
        e2 = 2 * err;
        if (e2 >= dy) {
            err += dy;
            x1 += sx;
        }
        if (e2 <= dx) {
            err += dx;
            y1 += sy;
        }
    }
}

double visual_raycast(t_point pos, double angle, t_vector *vector) {
    t_point dir = {cos(angle), sin(angle)};
    t_point ray_step = {fabs(TILE_SIZE / dir.x), fabs(TILE_SIZE / dir.y)};
    int map_x = (int)(pos.x / TILE_SIZE);
    int map_y = (int)(pos.y / TILE_SIZE);
    t_point ray_len;
    t_point step;

    if (dir.x < 0) {
        step.x = -1;
        ray_len.x = (pos.x - map_x * TILE_SIZE) * ray_step.x / TILE_SIZE;
    } else {
        step.x = 1;
        ray_len.x = ((map_x + 1) * TILE_SIZE - pos.x) * ray_step.x / TILE_SIZE;
    }
    if (dir.y > 0) {
        step.y = 1;
        ray_len.y = ((map_y + 1) * TILE_SIZE - pos.y) * ray_step.y / TILE_SIZE;
    } else {
        step.y = -1;
        ray_len.y = (pos.y - map_y * TILE_SIZE) * ray_step.y / TILE_SIZE;
    }

    int hit = 0;
    double dist = 0;
    while (!hit && map_x >= 0 && map_x < MAP_W && map_y >= 0 && map_y < MAP_H) {
        if (ray_len.x < ray_len.y) {
            map_x += step.x;
            dist = ray_len.x;
            ray_len.x += ray_step.x;
        } else {
            map_y += step.y;
            dist = ray_len.y;
            ray_len.y += ray_step.y;
        }
        if (map_x >= 0 && map_x < MAP_W && map_y >= 0 && map_y < MAP_H &&
            world_map[map_y][map_x] > 0) {
            hit = 1;
        }
    }

    int end_x = pos.x + dir.x * dist;
    int end_y = pos.y + dir.y * dist;
    vector->start = pos;
    vector->end.x = end_x;
    vector->end.y = end_y;

    return dist;
}

void render_map(t_info *info) {
    for (int y = 0; y < MAP_H; y++) {
        for (int x = 0; x < MAP_W; x++) {
            if (world_map[y][x] == 1) {
                for (int dy = 0; dy < TILE_SIZE; dy++) {
                    for (int dx = 0; dx < TILE_SIZE; dx++) {
                        mlx_pixel_put(info->mlx->mlx, info->mlx->mlx_win,
                                      x * TILE_SIZE + dx, y * TILE_SIZE + dy, COLOR);
                    }
                }
            }
        }
    }
}

void draw_wall_strip(t_info *info, int x, double dist, double angle) {
    (void) angle;
    double wall_height = (SCREEN_HEIGHT / dist) * TILE_SIZE;
    int draw_start = (SCREEN_HEIGHT - wall_height) / 2;
    if (draw_start < 0) draw_start = 0;
    int draw_end = (SCREEN_HEIGHT + wall_height) / 2;
    if (draw_end >= SCREEN_HEIGHT) draw_end = SCREEN_HEIGHT - 1;

    int color = COLOR;
    int shade = (int)(dist / TILE_SIZE * 25);
    if (shade > 255) shade = 255;
    color = (color & 0xFFFFFF) | (shade << 24);  // Assuming COLOR is in ARGB format

    for (int y = draw_start; y <= draw_end; y++) {
        mlx_pixel_put(info->mlx->mlx, info->mlx->mlx_win, x, y, color);
    }
}


void test_cast(t_info *info) {
    if (info->player->vector.len == -1) {
        info->player->vector.start.x = 4.5 * TILE_SIZE;
        info->player->vector.start.y = 4.5 * TILE_SIZE;
        info->player->vector.len = -2;
    }

    static double player_angle = 0.1;
    t_vector vector;
    double dist;

    // render_map(info);

    double fov = M_PI / 1.5;  // 60 degree field of view
    for (int x = 0; x < SCREEN_WIDTH; x++) {
        double ray_angle = player_angle - fov / 2 + (x / (double)SCREEN_WIDTH) * fov;
        dist = visual_raycast(info->player->vector.start, ray_angle, &vector);
        draw_wall_strip(info, x, dist, ray_angle);
    }

    // Draw the central ray for visualization (optional)
    // visual_raycast(info->player->vector.start, player_angle, &vector);
    // draw_line2(vector, info);
    // drawcircle(vector.end.x, vector.end.y, 13, info->mlx);

    player_angle += 0.1;
    if (player_angle > 2 * M_PI) player_angle -= 2 * M_PI;

    printf("p angle : %f\n", player_angle);
    usleep(150000);
    clear_window(info->mlx);
}

// Assume main function and other necessary setup code is elsewhere
