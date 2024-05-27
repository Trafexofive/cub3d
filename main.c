
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

int main() {
  t_info *info;
  t_map *map;
  // void *mlx;

  info = malloc(sizeof(t_info));
  map = malloc(sizeof(t_map));
  map->info = info;
  // entry_point(info);

  renderer(map);

  usleep(10000);
  mlx_destroy_window(info->mlx, info->mlx_win);
  free(info);
  free(map->player);
  free_arr(map->map);
  free(map);
  return 1;
}

// working main segment from solong;

// if (ac == 2)
// {
// 	game = parse(file_format(*(++av)));
// 	game->map[game->p_pos.y][game->p_pos.x] = '0';
// 	open_window(game);
// 	mlx_loop_hook(game->mlx, (void *)draw_map, game);
// 	mlx_key_hook(game->mlx_win, (void *)key_hook, game);
// 	mlx_hook(game->mlx_win, 17, 0, free_all, game);
// 	mlx_loop(game->mlx);
// }
// ft_exit(ERROR_6, 1);
