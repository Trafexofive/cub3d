
#include "../inc/macros.h"
#include "../inc/mlx_struct.h"
#include "../inc/struct.h"
#include "../inc/draw.h"

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


static void draw_line2(t_vector vector, t_info *info) {
    
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

t_vector visual_raycast(vec2 pos, double angle) {
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
  t_point p1 = {end_x, end_y};
  t_point p2 = {pos.x, pos.y};

  t_vector vector = {p2, p1, -1};
  return (vector);
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
  t_vector vector;


  usleep(5000);
  render_map(info);
  player_angle += 0.01;
  printf("p angle : %f\n", player_angle);

  vector = visual_raycast(player_pos, player_angle);
  draw_line2(vector, info);
  drawcircle(vector.end.x, vector.end.y, 13, info->mlx);
  usleep(1000);

  // In a real application, you'd have a game loop here
  // and you'd update the player position and angle based on input

}

