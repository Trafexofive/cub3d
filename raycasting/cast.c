
#include "../inc/macros.h"
#include "../inc/mlx_struct.h"
#include "../inc/struct.h"
#include <math.h>
#include <mlx.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MAP_W 8
#define MAP_H 8
#define SCREEN_W 320
#define SCREEN_H 200

int world_map[MAP_H][MAP_W] = {
    {1, 1, 1, 1, 1, 1, 1, 1}, {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 0, 1, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 0, 1, 0, 1}, {1, 0, 1, 0, 0, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 1}, {1, 1, 1, 1, 1, 1, 1, 1}};

typedef struct {
  double x;
  double y;
} vec2;

void cast_ray(vec2 pos, double angle, int *wall_height, t_info *info) {
  (void)info;
  vec2 dir = {cos(angle), sin(angle)};
  vec2 ray_step = {fabs(TILE_SIZE / dir.x), fabs(TILE_SIZE / dir.y)};

  int map_x = (int)(pos.x / TILE_SIZE);
  int map_y = (int)(pos.y / TILE_SIZE);

  vec2 ray_len;
  vec2 step;

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

  double dist = 0;
  int hit = 0;

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

  if (hit) {
    *wall_height = (int)(SCREEN_H / (dist / TILE_SIZE + 0.00001));
  } else {
    *wall_height = 0;
  }
}

void render_frame(vec2 player_pos, double player_angle, t_info *info) {
  for (int x = 0; x < SCREEN_W; x++) {
    double ray_angle =
        player_angle - atan2(1, 1) + (x / (double)SCREEN_W) * atan2(1, 0.5);
    int wall_height;
    cast_ray(player_pos, ray_angle, &wall_height, info);

    if (wall_height > 0) {
      int draw_start = (SCREEN_H - wall_height) / 2;
      int draw_end = draw_start + wall_height;

      if (draw_start < 0)
        draw_start = 0;
      if (draw_end >= SCREEN_H)
        draw_end = SCREEN_H - 1;

      for (int y = draw_start; y <= draw_end; y++) {
        mlx_pixel_put(info->mlx->mlx, info->mlx->mlx_win, x, y, COLOR);
      }
    }
  }
}

void test_cast(t_info *info) {
  vec2 player_pos = {
      4.5 * TILE_SIZE,
      4.5 * TILE_SIZE}; // Player starts in the middle of tile (4,4)
  double player_angle = 0.0;

  while (1) {
    render_frame(player_pos, player_angle, info);

    // Handle player movement and rotation here
    // This part depends on your input handling system

    // Example movement (you'll need to implement actual input handling):
    // player_pos.x += cos(player_angle) * move_speed;
    // player_pos.y += sin(player_angle) * move_speed;
    // player_angle += rotation_speed;
  }
}
