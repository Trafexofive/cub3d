
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

t_player *player_init(void)
{
    t_player *player = malloc (sizeof(t_player));
    player->spawn.x = 50;
    player->spawn.y = 50;
    return (player);
}
void *info_init(t_info *info) {
  info->mlx = mlx_init();
  info->draw_pos.x = 100;
  info->draw_pos.y = 100;
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

  printf("diffx == %d\n", diff_x);
  printf("diffy == %d\n", diff_y);
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

// void draw_circle(t_info *info, int radius, t_point position) {
//   if (!position.x || !position.y)
//     position = info->draw_pos;
// }

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

void circle_octants(int centerX, int centerY, int x, int y, t_info *info) {
  // Draw points in all eight octants
  mlx_pixel_put(info->mlx, info->mlx_win, centerX + x, centerY + y,
                COLOR); // Octant 1
  mlx_pixel_put(info->mlx, info->mlx_win, centerX + x, centerY - y,
                COLOR); // Octant 1
  mlx_pixel_put(info->mlx, info->mlx_win, centerX - x, centerY - y,
                COLOR); // Octant 1
  mlx_pixel_put(info->mlx, info->mlx_win, centerX - x, centerY + y,
                COLOR); // Octant 1
  mlx_pixel_put(info->mlx, info->mlx_win, centerX + y, centerY + x,
                COLOR); // Octant 1
  mlx_pixel_put(info->mlx, info->mlx_win, centerX - y, centerY + x,
                COLOR); // Octant 1
  mlx_pixel_put(info->mlx, info->mlx_win, centerX - y, centerY - x,
                COLOR); // Octant 1
  mlx_pixel_put(info->mlx, info->mlx_win, centerX + y, centerY - x,
                COLOR); // Octant 1
}

void drawCircle(int centerX, int centerY, int radius, t_info *info) {
  int x = 0;
  int y = radius;
  int d = 3 - 2 * radius;

  // Draw the initial points on the circle
  circle_octants(centerX, centerY, x, y, info);

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
    circle_octants(centerX, centerY, x, y, info);
  }
}

void render_player(t_map *map) {
  t_info *info = map->info;
  // info->draw_pos.x = 400;
  // info->draw_pos.y = 600;
  int centerX = map->player->spawn.x;
  int centerY = map->player->spawn.y;
  int radius = 15;

  drawCircle(centerX, centerY, radius, info);
  // draw_slant(info, 10, info->draw_pos, p);
  // draw_circle(info, 10, info->draw_pos);
}

void map_tile_morph(t_map *map) {
  int i = 0;
  int j = 0;
  t_info *info;

  info = map->info;

  int len = 30;

  while (map->map[i]) {

    while (map->map[i][j]) {
      if (map->map[i][j] == '1') {

        draw_tile(info, len, info->draw_pos);
      } if (map->map[i][j] == 'N' || map->map[i][j] == 'W' ||
                 map->map[i][j] == 'S' || map->map[i][j] == 'E') {
        map->player->spawn.x = info->draw_pos.x;
        map->player->spawn.y = info->draw_pos.y;
        render_player(map);
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

void renderer(t_map *map) {
  t_info *info = map->info;
  // void    load_textures(t_texture *textures);
  // render_minimap_term(map);

  info_init(info);
  info->mlx_win =
      mlx_new_window(info->mlx, info->win_size_x, info->win_size_y, "Cub3d");
  // draw_test(info);
  // t_point p;
    map->player = player_init();

  // mlx_loop_hook(info->mlx, ,void *param);

  render_minimap_term(map);
  mlx_loop(info->mlx);
}

// Function to draw the 8 symmetrical points of the circle

// Function to draw a circle using Bresenham's Algorithm
