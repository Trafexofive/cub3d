
#include "inc/raycast.h"
#include "inc/struct.h"
#include "inc/utils.h"
#include <stdio.h>
#include <stdlib.h>


void    free_arr(char **arr)
{
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
  free(info);
  free(map->player);
    free_arr(map->map);
  free(map);
  return 1;
}
