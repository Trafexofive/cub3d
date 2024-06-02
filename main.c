
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

void free_all(t_map *map) {

  mlx_destroy_window(map->info->mlx, map->info->mlx_win);
  free(map->info);
  free(map->player);
  free_arr(map->map);
  free(map);
  exit(EXIT_FAILURE);
}

void player_move_w(t_map *map) { map->player->spawn.y -= MOVE_SPEED; }
void player_move_s(t_map *map) { map->player->spawn.y += MOVE_SPEED; }
void player_move_a(t_map *map) { map->player->spawn.x -= MOVE_SPEED; }
void player_move_d(t_map *map) { map->player->spawn.x += MOVE_SPEED; }

void key_hook(int key, t_map *map) {
  printf("key value = %X\n", key);
  if (key == W_KEY)
    player_move_w(map);
  if (key == S_KEY)
    player_move_s(map);
  if (key == A_KEY)
    player_move_a(map);
  if (key == D_KEY)
    player_move_d(map);
  if (key == ESC_KEY)
    free_all(map);
}
// }

//make map an arr to make it possible creating multiple windows and pulling them by index
void new_window(t_map *map) {

  map->info->mlx_win = mlx_new_window(map->info->mlx, map->info->win_x,
                                      map->info->win_y, "Cub3d");
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

bool game_init(t_map *map) {

  new_window(map);
  init_minimap(map);
  mlx_loop_hook(map->info->mlx, (void *)renderer, map);
  mlx_key_hook(map->info->mlx_win, (void *)key_hook, map);
  mlx_hook(map->info->mlx_win, 17, 0, (void *)free_all, map);
  clear_window(map->info);
  mlx_loop(map->info->mlx);
  return true;
}

t_map *vars_init() {

  t_info *info;
  t_map *map;

  info = malloc(sizeof(t_info));
  map = malloc(sizeof(t_map));
  map->info = info;
  info_init(map->info);
  map->player = player_init();
  return (map);
}

int main() {
  game_init(vars_init());
  return 1;
}
