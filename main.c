
#include "gui/gui_engine.h"
#include "inc/macros.h"
#include "inc/raycast.h"
#include "inc/struct.h"
#include "inc/utils.h"
#include <stdio.h>
#include <stdlib.h>

void free_arr(char **arr) {
  int i = 0;
  while (arr[i] != NULL) {
    free(arr[i]);
  }
}

void free_all(t_info *info) {

  void *mlx;
  void *mlx_win;

  mlx = info->mlx->mlx;
  mlx_win = info->mlx->mlx_win;

  mlx_destroy_window(mlx, mlx_win);
  free(info);
  free(info->player);
  free_arr(info->map->map);
  free(info->map);
}

void player_move_w(t_map *map) { map->player->spawn.y -= MOVE_SPEED; }
void player_move_s(t_map *map) { map->player->spawn.y += MOVE_SPEED; }
void player_move_a(t_map *map) { map->player->spawn.x -= MOVE_SPEED; }
void player_move_d(t_map *map) { map->player->spawn.x += MOVE_SPEED; }

static void key_hook(int key, t_info *info) {
  printf("key value = %X\n", key);
  printf("decimal key value = %d\n", key);
  t_map *map = info->map;

  if (key == W_KEY)
    player_move_w(map);
  if (key == S_KEY)
    player_move_s(map);
  if (key == A_KEY)
    player_move_a(map);
  if (key == D_KEY)
    player_move_d(map);
  if (key == ESC_KEY)
    free_all(info);
}

// make map an arr to make it possible creating multiple windows and pulling
// them by index
void new_window(t_mlx *mlx) {

  mlx->mlx_win = mlx_new_window(mlx->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3d");
}

void init_minimap(t_map *map) {
  int i = 0;
  int fd = open("maps/map.cub", O_RDONLY);
  map->map = malloc(20 * sizeof(char *));
  while (1) {
    map->map[i] = get_next_line(fd);
    printf("%s", map->map[i]);
    if (map->map[i] == NULL)
      break;
    i++;
  }
  close(fd);
}

bool game_init(t_info *info) {

  // t_menu *menu;
  t_mlx *mlx;
  t_map *map = info->map;

  // menu = malloc(sizeof(t_menu));
  mlx = info->mlx;
  // menu->mlx = mlx;
  // map->current_menu = menu;
  new_window(mlx);
  // mlx_do_sync(map->info->mlx);
  init_minimap(map);
  mlx_loop_hook(mlx->mlx, (void *)renderer, map);
  mlx_hook(mlx->mlx_win, 17, 0, (void *)free_all, info);
  mlx_key_hook(mlx->mlx_win, (void *)key_hook, map);
  // mlx_key_hook(mlx->mlx_win, (void *)navigation_key_hook, menu);
  clear_window(mlx);
  mlx_loop(mlx->mlx);
  return true;
}

void init_mlx(t_mlx *mlx) { mlx->mlx = mlx_init(); }

t_info *vars_init() {

  t_info *info;
  t_map *map;
  t_mlx *mlx;

  info = malloc(sizeof(t_info));
  map = malloc(sizeof(t_map));
  mlx = malloc(sizeof(t_mlx));

  init_mlx(mlx);
  map->mlx = mlx;
  info->map = map;

  // info_init(info);
  info->player = player_init();
  return (info);
}

int main() {
  game_init(vars_init());
  return 1;
}
