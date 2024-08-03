
#include "../inc/draw.h"
#include "../inc/macros.h"
#include "../inc/mlx_struct.h"
#include "../inc/struct.h"
#include <math.h>
#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAP_W 40
#define MAP_H 40

// double  angle_add(double angle, double angle_to_add)
// {
//     double new_angle = (angle + angle_to_add) ;
//     new_angle = new_angle % 360.0;
//
//     return (new_angle);
// }

void draw_line2(t_vector vector, t_info *info) {
  int x1 = vector.start.x;
  int y1 = vector.start.y;
  int x2 = vector.end.x;
  int y2 = vector.end.y;
  int dx = abs(x2 - x1), sx = x1 < x2 ? 1 : -1;
  int dy = -abs(y2 - y1), sy = y1 < y2 ? 1 : -1;
  int err = dx + dy, e2;
  t_img *image = &info->img;
  t_point point;

  point.x = 0;
  point.y = 0;

  while (1) {
    point.x = x1;
    point.y = y1;
    put_pixel(image, point, COLOR);
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

void fill_image(t_info *info, int color) {
  t_img *image = &info->img;
  t_point point;

  point.x = 0;
  point.y = 0;
  while (point.y < SCREEN_HEIGHT) {

    while (point.x < SCREEN_WIDTH) {
      put_pixel(image, point, color);
      point.x += 1;
    }
    point.x = 0;
    point.y += 1;
  }
}

void clear_image(t_info *info) {
  t_img *image = &info->img;
  t_point point;

  point.x = 0;
  point.y = 0;
  while (point.y < SCREEN_HEIGHT) {

    while (point.x < SCREEN_WIDTH) {
      put_pixel(image, point, 0);
      point.x += 1;
    }
    point.x = 0;
    point.y += 1;
  }
}

double visual_raycast(t_point pos, double angle, t_vector *vector,
                      t_info *info) {
  t_point dir = {cos(angle), sin(angle)};
  t_point ray_step = {fabs(TILE_SIZE / dir.x), fabs(TILE_SIZE / dir.y)};
  int map_x = (int)(pos.x / TILE_SIZE);
  int map_y = (int)(pos.y / TILE_SIZE);
  t_point ray_len;
  t_point step;
  char **map = info->map->map;

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
        map[map_y][map_x] != '0') {
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

// void render_map(t_info *info) {
//   t_img *image = &info->img;
//   t_point point;
//
//   char **map = info->map->map;
//   for (point.y = 0; point.y < MAP_H; point.y++) {
//     for (point.x = 0; point.x < MAP_W; point.x++) {
//       if (map[(int)point.y][(int)point.x] == '1') {
//         for (int dy = 0; dy < TILE_SIZE; dy++) {
//           for (int dx = 0; dx < TILE_SIZE; dx++) {
//             put_pixel(image, point, COLOR);
//           }
//         }
//       }
//     }
//   }
// }

void render_map(t_info *info) {
  t_img *image = &info->img;
  t_point point;

  char **map = info->map->map;
  for (int y = 0; y < MAP_H; y++) {
    for (int x = 0; x < MAP_W; x++) {
      if (map[y][x] == '1') {
        for (int dy = 0; dy < TILE_SIZE; dy++) {
          for (int dx = 0; dx < TILE_SIZE; dx++) {
            point.x = x * TILE_SIZE + dx;
            point.y = y * TILE_SIZE + dy;
            put_pixel(image, point, COLOR);
          }
        }
      }
    }
  }
}

void draw_wall_strip(t_info *info, int x, double dist, double angle) {
  t_img *image = &info->img;
  t_point point;

  (void)angle;
  double wall_height = (SCREEN_HEIGHT / dist) * TILE_SIZE;
  int draw_start = (SCREEN_HEIGHT - wall_height) / 2;
  if (draw_start < 0)
    draw_start = 0;
  int draw_end = (SCREEN_HEIGHT + wall_height) / 2;
  if (draw_end >= SCREEN_HEIGHT)
    draw_end = SCREEN_HEIGHT - 1;

  int color = COLOR;
  int shade = (int)(dist / TILE_SIZE * 25);
  if (shade > 255)
    shade = 255;
  color = (color & 0xFFFFFF) | (shade << 24);

  point.x = x;
  for (int y = draw_start; y <= draw_end; y++) {
    point.y = y;
    put_pixel(image, point, COLOR);
  }
}

void set_player_spawn(t_info *info) {
  char **map = info->map->map;
  int i = 0;
  int j = 0;

  while (map[j]) {
    while (map[j][i]) {
      if (map[j][i] == 'N' || map[j][i] == 'S' || map[j][i] == 'W' ||
          map[j][i] == 'E') {
        info->player->vector.start.x = i * TILE_SIZE;
        info->player->vector.start.y = j * TILE_SIZE;
        break;
      }
      i++;
    }
    i = 0;
    j++;
  }
}

void test_cast(t_info *info) {
  if (info->player->vector.len == -1) {
    set_player_spawn(info);
    info->player->vector.len = -2;
  }
  t_player *player = info->player;
  double dist;
  t_vector vector;

  clear_image(info);

  // render_map(info);

  fill_image(info, GREEN);
  double fov = M_PI / 1.5; // 60 degree field of view
  for (int x = 0; x < SCREEN_WIDTH; x++) {
    double ray_angle =
        player->angle - fov / 2 + (x / (double)SCREEN_WIDTH) * fov;
    dist = visual_raycast(info->player->vector.start, ray_angle, &vector, info);
    // draw_line2(vector, info);
    draw_wall_strip(info, x, dist, ray_angle);
  }

  // visual_raycast(info->player->vector.start, player_angle, &vector);
  // drawcircle(vector.end.x, vector.end.y, 13, info->mlx);

  if (player->angle > 2 * M_PI)
    player->angle -= 2 * M_PI;

  // printf("p angle : %f\n", player->angle);
  // usleep(150000);
}
