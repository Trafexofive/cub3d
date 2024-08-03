
#include "../gui/gui_engine.h"
#include "../inc/draw.h"
#include "../inc/macros.h"
#include "../inc/raycast.h"
#include "../inc/struct.h"
#include "../inc/utils.h"
#include "../lib/libft/libft.h"
#include <stdio.h>


void render_player(t_map *map) {
  drawcircle(map->player->spawn.x, map->player->spawn.y, HIT_BOX, map->mlx);
}

void update_player_dir(t_map *map, int i, int j) {
  if (map->map[i][j] == 'N') {
    map->player->player_dir = north;
  }
  if (map->map[i][j] == 'W')
    map->player->player_dir = west;
  if (map->map[i][j] == 'S')
    map->player->player_dir = south;
  if (map->map[i][j] == 'E')
    map->player->player_dir = east;
}

void print_point(t_point point) {
  printf("x = %f\n", point.x);
  printf("y = %f\n", point.y);
}

// void map_tile_morph(t_info *info) {
//   int i = 0;
//   int j = 0;
//   t_mlx *mlx;
//   t_point draw_pos;
//   t_map *map = info->map;
//
//   draw_pos.x = 0;
//   draw_pos.y = 0;
//
//   mlx = info->mlx;
//
//   int len = TILE_SIZE;
//   int tmp = draw_pos.x;
//
//   while (map->map[i]) {
//
//     while (map->map[i][j]) {
//       if (map->map[i][j] == '1') {
//
//         draw_tile(mlx, len, draw_pos);
//
//       } else if (map->map[i][j] == 'N' || map->map[i][j] == 'W' ||
//                  map->map[i][j] == 'S' || map->map[i][j] == 'E') {
//         if (map->player->spawned == false) {
//           map->player->spawn.x = draw_pos.x + (len / 2);
//           map->player->spawn.y = draw_pos.y + (len / 2);
//           update_player_dir(map, i, j);
//           render_player(map);
//           map->player->spawned = true;
//         }
//       }
//       draw_pos.x += len;
//       j++;
//     }
//     // print_point(info->draw_pos);
//     draw_pos.y += len;
//     draw_pos.x = tmp;
//     i++;
//     j = 0;
//   }
// }

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

void reset_player_info(t_player *player) {
    player->position.x = 0;
    player->position.y = 0;
    
}

// void cast_rays(t_map *map) {
//   // int w = SCREEN_WIDTH;
//   // double posX = 22, posY = 12;      // x and y start position
//   // double dirX = -1, dirY = 0;       // initial direction vector
//   // double planeX = 0, planeY = 0.66; // the 2d raycaster version of camera
//   // plane t_point camera; int x = 0;
//   //
//   // camera.x = 2 * x / w - 1;
// }

void raycaster(t_info *info) { 
    // t_player    *player = info->player;

    
    test_cast(info);

    // cast_rays(info->map); 

}

void renderer(t_info *info) {

  // t_menu *menu;
  // t_map *map;
  // t_player *player = info->player;

  // map = info->map;
  // map->player = player;
  // menu = map->current_menu;
  t_mlx *mlx = info->mlx;
  clear_window(mlx);
  // fprintf(stderr,"mlx = %p\n", mlx->mlx);
  // menu->mlx = mlx;
  // clear_window(mlx);

  // gui_entry_point(menu);
  // fps(map);
  // map_tile_morph(map);
  // render_player(map);
  raycaster(info);
  mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, info->img.img, 0, 0);

  // reset_player_info(player);
}
