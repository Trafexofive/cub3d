
#include "../inc/draw.h"
#include "../inc/macros.h"
#include "../inc/raycast.h"
#include "../inc/struct.h"
#include "../inc/utils.h"
#include "../lib/libft/libft.h"
#include <stdio.h>

// typedef struct s_grid
// {
//     t_info *info;
//     int len;
//     int count
//
// } t_grid;

void render_player(t_map *map) {
  // info->draw_pos.x = 400;
  // info->draw_pos.y = 600;
  // map->player->spawn.x *= 1.5;
  // map->player->spawn.y *= 1.5;
  int centerX = map->player->spawn.x;
  int centerY = map->player->spawn.y;
  t_point relative = map->player->spawn;
  relative.y = map->player->spawn.y + TILE_SIZE;

  int radius = 10;

  drawcircle(centerX, centerY, radius, map->info);

  draw_anyline(map, map->player->spawn, relative);
  // draw_slant(info, 10, info->draw_pos, p);
  // draw_circle(info, 10, info->draw_pos);
}

void update_player_dir(t_map *map, int i, int j) {
  if (map->map[i][j] == 'N') {
    map->info->player_dir = north;
  }
  if (map->map[i][j] == 'W')
    map->info->player_dir = west;
  if (map->map[i][j] == 'S')
    map->info->player_dir = south;
  if (map->map[i][j] == 'E')
    map->info->player_dir = east;
}

void map_tile_morph(t_map *map) {
  int i = 0;
  int j = 0;
  t_info *info;

  info = map->info;

  int len = 30;
  int tmp = info->draw_pos.x;

  while (map->map[i]) {

    while (map->map[i][j]) {
      if (map->map[i][j] == '1') {

        draw_tile(info, len, info->draw_pos);
      }
      if (map->map[i][j] == 'N' || map->map[i][j] == 'W' ||
          map->map[i][j] == 'S' || map->map[i][j] == 'E') {
        map->player->spawn.x = info->draw_pos.x + (len / 2);
        map->player->spawn.y = info->draw_pos.y + (len / 2);
        update_player_dir(map, i, j);
        render_player(map);
      }
      info->draw_pos.x += len;
      j++;
    }
    info->draw_pos.y += len;
    info->draw_pos.x = tmp;
    i++;
    j = 0;
  }
}

//
// void new_image(t_img img, t_info *info) {
//   img.img = mlx_new_image(info->mlx, info->win_x - 1, info->win_y - 1);
// }

// void    hooks(t_info *info)
// {
//   mlx_loop_hook(info->mlx, ,void *param);
//
// }
//
//

// void    load_textures(t_texture *textures);

void fps(t_map *map) {
  static int frames = 0;
  char *string;

  string = ft_itoa(frames);
  mlx_string_put(map->info->mlx, map->info->mlx_win, 150, 50, COLOR, string);
  mlx_string_put(map->info->mlx, map->info->mlx_win, 40, 50, COLOR, "frames :");
  printf("%s\n", string);
  frames++;
  free(string);
}

void reset_player_info(t_info *info) {
  info->draw_pos.x = 100;
  info->draw_pos.y = 100;
}

void renderer(t_map *map) {

  // t_point a;
  // t_point b;
  //
  // a.x = 50;
  // a.y = 50;
  // b.x = 100;
  // b.y = 200;

  fps(map);
  // draw_anyline(map, a, b);
  map_tile_morph(map);
  usleep(FPS);
  reset_player_info(map->info);
  clear_window(map->info);
}
