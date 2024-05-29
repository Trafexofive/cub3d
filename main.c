
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
}

void player_move_w(t_map *map) {
  map->player->spawn.y = +1;
}

void key_hook(int key, t_map *map) {
  printf("key value = %X\n", key);
  map->player->spawn.y = +1;
  if (key == W_KEY)
    player_move_w(map);
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
}

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

int main() {
  t_info *info;
  t_map *map;
  // void *mlx;

  info = malloc(sizeof(t_info));
  map = malloc(sizeof(t_map));
  map->info = info;
  info_init(map->info);
  map->player = player_init();

  // open_window(map);
  new_window(map);
  init_minimap(map);
  mlx_loop_hook(map->info->mlx, (void *)renderer, map);
  mlx_key_hook(info->mlx_win, (void *)key_hook, &map);
  mlx_hook(info->mlx_win, 17, 0, (void *)free_all, map);
  clear_window(info);
  mlx_loop(info->mlx);
  free_all(map);
  return 1;
}
