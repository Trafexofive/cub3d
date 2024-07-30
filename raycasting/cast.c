
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
#define SCREEN_W (MAP_W * TILE_SIZE)
#define SCREEN_H (MAP_H * TILE_SIZE)

int world_map[MAP_H][MAP_W] = {
    {1, 1, 1, 1, 1, 1, 1, 1}, {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 0, 1, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 0, 1, 0, 1}, {1, 0, 1, 0, 0, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 1}, {1, 1, 1, 1, 1, 1, 1, 1}};

typedef struct {
  double x;
  double y;
} vec2;


static void draw_line(int x1, int y1, int x2, int y2, t_info *info) {
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

void visual_raycast(vec2 pos, double angle, t_info *info) {
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

  // Draw the ray
  int end_x = pos.x + dir.x * dist;
  int end_y = pos.y + dir.y * dist;
  draw_line((int)pos.x, (int)pos.y, end_x, end_y, info);
}

void render_map(t_info *info) {
  for (int y = 0; y < MAP_H; y++) {
    for (int x = 0; x < MAP_W; x++) {
      if (world_map[y][x] == 1) {
        // Draw a filled square for walls
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


void test_cast(t_info *info) {
  vec2 player_pos = {4.5 * TILE_SIZE, 4.5 * TILE_SIZE};
  static double player_angle = 0.1;

  usleep(5000);
  render_map(info);
  player_angle += 0.1;
  printf("p angle : %f\n", player_angle);

  visual_raycast(player_pos, player_angle, info);
  usleep(1000);

  // In a real application, you'd have a game loop here
  // and you'd update the player position and angle based on input

}

