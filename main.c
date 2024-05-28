
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

void free_all(t_map *map) {

  mlx_destroy_window(map->info->mlx, map->info->mlx_win);
  free(map->info);
  free(map->player);
  free_arr(map->map);
  free(map);
}

void key_hook(t_map *map) {
  (void)map;
  return;
}

void new_window(t_map *map) {

  map->info->mlx_win = mlx_new_window(map->info->mlx, map->info->win_x,
                                      map->info->win_y, "Cub3d");
}

int main() {
  t_info *info;
  t_map *map;
  // void *mlx;

  info = malloc(sizeof(t_info));
  map = malloc(sizeof(t_map));
  map->info = info;
  info_init(map->info);
  map->player = player_init();
  // entry_point(info);

  // renderer(map);

  // open_window(map);
  new_window(map);
  mlx_loop_hook(map->info->mlx, (void *)renderer, map);
  mlx_key_hook(info->mlx_win, (void *)key_hook, &map);
  mlx_hook(info->mlx_win, 17, 0, (void *)free_all, map);
  clear_window(info);
  mlx_loop(info->mlx);
  free_all(map);
  return 1;
}
