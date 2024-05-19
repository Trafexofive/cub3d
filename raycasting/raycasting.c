
// void key_hook(int key, t_game_info *game) {
//   if (key == W_KEY &&
//       check_collision(game->map[game->p_pos.y - 1][game->p_pos.x], game))
//     player_move(game, 0, -1);
//   else if (key == S_KEY &&
//            check_collision(game->map[game->p_pos.y + 1][game->p_pos.x],
//            game))
//     player_move(game, 0, 1);
//   else if (key == A_KEY &&
//            check_collision(game->map[game->p_pos.y][game->p_pos.x - 1],
//            game))
//     player_move(game, -1, 0);
//   else if (key == D_KEY &&
//            check_collision(game->map[game->p_pos.y][game->p_pos.x + 1],
//            game))
//     player_move(game, +1, 0);
//   else if (key == ESC_KEY)
//     free_all(game);
// }
#include "../inc/raycast.h"
#include "../inc/struct.h"

#define COLOR 0xFF5733
#define VER false
#define HOR true
#define TILE_SIZE 100

typedef enum s_keys {
  W_KEY = 0x0D,
  S_KEY = 0x01,
  A_KEY = 0x00,
  D_KEY = 0x02,
  ESC_KEY = 0x35,
} t_keys;

t_map load_map_data(t_map *map);

void *info_init(t_info *info) {
  info->mlx = mlx_init();
  info->draw_pos.x = 0;
  info->draw_pos.y = 0;
  info->player_pos.x = 0;
  info->player_pos.y = 0;
  info->win_size_x = 1280;
  info->win_size_y = 1080;

  return NULL;
}

void clear_window(t_info *info) { mlx_clear_window(info->mlx, info->mlx_win); }

// left sided draw
void draw_line(t_info *info, int len, t_point starting_position, bool mode) {
  int i = 0;
  int x = starting_position.x;
  int y = starting_position.y;

  if (mode == true) {
    while (i < len) {
      mlx_pixel_put(info->mlx, info->mlx_win, x, y, COLOR);
      x++;
      i++;
    }
  } else {
    while (i < len) {
      mlx_pixel_put(info->mlx, info->mlx_win, x, y, COLOR);
      y++;
      i++;
    }
  }
}

void draw_slant(t_info *info, int radius, t_point position, t_point target) {
  int diff_x = target.x - position.x + 1;
  int diff_y = target.y - position.y + 1;
  float ratio = diff_x / diff_y;

    printf("diffx == %d\n" ,diff_x);
    printf("diffy == %d\n" ,diff_y);
  const float remainder = ratio - (int)ratio;
    printf("remainder == %f\n", remainder);

  (void)position;
  (void)radius;
  while (diff_x < 100) {

    mlx_pixel_put(info->mlx, info->mlx_win, diff_x, diff_y, COLOR);
    diff_x++;
    diff_y++;
  }
}

void    draw_circle(t_info *info, int radius, t_point position)
{
    if (!position.x || !position.y)
        position = info->draw_pos;


}

void draw_tile(t_info *info, int len, t_point starting_position) {
  draw_line(info, len, starting_position, VER);
  starting_position.x += len;
  draw_line(info, len, starting_position, VER);
  starting_position.x -= len;
  draw_line(info, len, starting_position, HOR);
  starting_position.y += len;
  draw_line(info, len, starting_position, HOR);
}

void draw_wall_ver(t_info *info, int len, int count,
                   t_point starting_position) {
  int i = 0;

  while (i < count) {
    draw_tile(info, len, starting_position);
    starting_position.y += len;
    i++;
  }
}

// typedef struct s_grid
// {
//     t_info *info;
//     int len;
//     int count
//
// } t_grid;

void draw_wall_hor(t_info *info, int len, int count,
                   t_point starting_position) {
  int i = 0;

  while (i < count) {
    draw_tile(info, len, starting_position);
    starting_position.x += len;
    i++;
  }
}

void draw_grid(t_info *info, int len, int count, t_point starting_position) {
  int i = 0;

  while (i < count) {
    draw_wall_hor(info, len, count, starting_position);
    starting_position.y += len;
    i++;
  }
}

void map_tile_morph(t_map *map) {
  int i = 0;
  int j = 0;
  t_info *info;

  info = map->info;

  int len = 10;

  while (map->map[i]) {

    while (map->map[i][j]) {
      if (map->map[i][j] == '1') {

        draw_tile(info, len, info->draw_pos);
      }
      info->draw_pos.x += len;
      j++;
    }
    info->draw_pos.y += len;
    info->draw_pos.x = 0;
    i++;
    j = 0;
  }
}

void render_minimap_term(t_map *map) {
  int i = 0;
  int fd = open("maps/map.cub", O_RDONLY);
  map->map = malloc(sizeof(char *));
  while (1) {
    map->map[i] = get_next_line(fd);
    printf("%s", map->map[i]);
    if (map->map[i] == NULL)
      break;
    i++;
  }
  close(fd);
  map_tile_morph(map);
}

void render_player(t_map *map) {
  t_info *info = map->info;

  t_point p;
    info->draw_pos.x = 400;
    info->draw_pos.y = 600;

  p.x = 1000;
  p.y = 1500;

  draw_slant(info, 10, info->draw_pos, p);
    draw_circle(info, 10, info->draw_pos);
}

void renderer(t_map *map) {
  t_info *info = map->info;

  // void    load_textures(t_texture *textures);
  // render_minimap_term(map);

  info_init(info);
  info->mlx_win =
      mlx_new_window(info->mlx, info->win_size_x, info->win_size_y, "Cub3d");
  // draw_test(info);
  t_point p;

    draw_line(info)
  // mlx_loop_hook(info->mlx, ,void *param);

  // render_minimap_term(map);
  render_player(map);
  mlx_loop(info->mlx);
}
#include <stdio.h>

// Function to draw a pixel at (x, y)
// In a real graphics environment, you would use a graphics library to draw pixels on the screen.
void drawPixel(int x, int y) {
    printf("Drawing pixel at (%d, %d)\n", x, y);
}

// Function to draw the 8 symmetrical points of the circle
void drawCirclePoints(int centerX, int centerY, int x, int y) {
    // Draw points in all eight octants
    drawPixel(centerX + x, centerY + y); // Octant 1
    drawPixel(centerX - x, centerY + y); // Octant 4
    drawPixel(centerX + x, centerY - y); // Octant 8
    drawPixel(centerX - x, centerY - y); // Octant 5
    drawPixel(centerX + y, centerY + x); // Octant 2
    drawPixel(centerX - y, centerY + x); // Octant 3
    drawPixel(centerX + y, centerY - x); // Octant 7
    drawPixel(centerX - y, centerY - x); // Octant 6
}

// Function to draw a circle using Bresenham's Algorithm
void drawCircle(int centerX, int centerY, int radius) {
    int x = 0;
    int y = radius;
    int d = 3 - 2 * radius;

    // Draw the initial points on the circle
    drawCirclePoints(centerX, centerY, x, y);

    // Loop to draw the circle using Bresenham's algorithm
    while (y >= x) {
        x++;
        // Update the decision parameter based on its current value
        if (d > 0) {
            y--;
            d = d + 4 * (x - y) + 10;
        } else {
            d = d + 4 * x + 6;
        }
        // Draw the points for the current (x, y)
        drawCirclePoints(centerX, centerY, x, y);
    }
}

int main() {
    int centerX = 50; // Example center x-coordinate
    int centerY = 50; // Example center y-coordinate
    int radius = 20;  // Example radius

    drawCircle(centerX, centerY, radius);

    return 0;
}

