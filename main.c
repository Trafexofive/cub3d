
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

void free_all(t_map *map) {

  void *mlx;
  void *mlx_win;

  mlx = map->mlx->mlx;
  mlx_win = map->mlx->mlx_win;

  mlx_destroy_window(mlx, mlx_win);
  free(map->info);
  free(map->player);
  free_arr(map->map);
  free(map);
}

void player_move_w(t_map *map) { map->player->spawn.y -= MOVE_SPEED; }
void player_move_s(t_map *map) { map->player->spawn.y += MOVE_SPEED; }
void player_move_a(t_map *map) { map->player->spawn.x -= MOVE_SPEED; }
void player_move_d(t_map *map) { map->player->spawn.x += MOVE_SPEED; }

void key_hook(int key, t_map *map) {
    t_menu *menu;
    menu = map->current_menu;
  printf("key value = %X\n", key);
  printf("decimal key value = %d\n", key);

  if (key == W_KEY)
    player_move_w(map);
  if (key == S_KEY)
    player_move_s(map);
  if (key == A_KEY)
    player_move_a(map);
  if (key == D_KEY)
    player_move_d(map);
  if (key == J_KEY)
    scroll_down(menu);
  if (key == K_KEY)
    scroll_up(menu);
    if (key == ESC_KEY)
      free_all(map);
}
// }

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

bool game_init(t_map *map) {

  t_mlx *mlx;

  mlx = map->mlx;
  new_window(mlx);
  // mlx_do_sync(map->info->mlx);
  init_minimap(map);
  mlx_loop_hook(mlx->mlx, (void *)renderer, map);
  mlx_hook(mlx->mlx_win, 17, 0, (void *)free_all, map);
  mlx_key_hook(mlx->mlx_win, (void *)key_hook, map);
  clear_window(mlx);
  mlx_loop(mlx->mlx);
  return true;
}

void init_mlx(t_mlx *mlx) { mlx->mlx = mlx_init(); }

t_map *vars_init() {

  t_info *info;
  t_map *map;
  t_mlx *mlx;

  info = malloc(sizeof(t_info));
  map = malloc(sizeof(t_map));
  mlx = malloc(sizeof(t_mlx));

  map->info = info;
  init_mlx(mlx);
  map->mlx = mlx;

  info_init(map->info);
  map->player = player_init();
  return (map);
}

int main() {
  game_init(vars_init());
  return 1;
}
