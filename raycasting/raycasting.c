
#include "../gui/gui_engine.h"
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
  drawcircle(map->player->spawn.x, map->player->spawn.y, HIT_BOX, map->mlx);
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

void print_point(t_point point) {
  printf("x = %d\n", point.x);
  printf("y = %d\n", point.y);
}

void map_tile_morph(t_map *map) {
  int i = 0;
  int j = 0;
  t_info *info;
  t_mlx *mlx;

  info = map->info;
  mlx = map->mlx;

  int len = TILE_SIZE;
  int tmp = info->draw_pos.x;

  while (map->map[i]) {

    while (map->map[i][j]) {
      if (map->map[i][j] == '1') {

        draw_tile(mlx, len, info->draw_pos);

      } else if (map->map[i][j] == 'N' || map->map[i][j] == 'W' ||
                 map->map[i][j] == 'S' || map->map[i][j] == 'E') {
        if (map->player->spawned == false) {
          map->player->spawn.x = info->draw_pos.x + (len / 2);
          map->player->spawn.y = info->draw_pos.y + (len / 2);
          update_player_dir(map, i, j);
          render_player(map);
          map->player->spawned = true;
        }
      }
      info->draw_pos.x += len;
      j++;
    }
    // print_point(info->draw_pos);
    info->draw_pos.y += len;
    info->draw_pos.x = tmp;
    i++;
    j = 0;
  }
}

// void    load_textures(t_texture *textures);

void fps(t_map *map) {
  static int frames = 0;
  char *string;
  t_mlx *mlx = map->mlx;

  string = ft_itoa(frames);
  mlx_string_put(mlx->mlx, mlx->mlx_win, 150, 50, COLOR, string);
  mlx_string_put(mlx->mlx, mlx->mlx_win, 40, 50, COLOR, "frames :");
  if (frames == 60)
    frames = 0;
  else
    frames++;
  free(string);
}

void reset_player_info(t_info *info) {
  info->draw_pos.x = 100;
  info->draw_pos.y = 100;
}

// void cast_rays(t_map *map) {
//   int w = SCREEN_WIDTH;
//   double posX = 22, posY = 12;      // x and y start position
//   double dirX = -1, dirY = 0;       // initial direction vector
//   double planeX = 0, planeY = 0.66; // the 2d raycaster version of camera plane
//   t_point camera;
//   int x = 0;
//
//   camera.x = 2 * x / w - 1;
//   while ()
// }

// void raycaster(t_map *map) { cast_rays(map); }

void renderer(t_map *map) {

  t_mlx *mlx = map->mlx;
  clear_window(mlx);
  // mlx_hook(map->info->mlx_win, 119, 0, (void *) player_move_w, map);
  // usleep(100000);

  gui_entry_point(mlx);
  // fps(map);
  // map_tile_morph(map);
  // render_player(map);
  // raycaster(map);
  reset_player_info(map->info);
}
