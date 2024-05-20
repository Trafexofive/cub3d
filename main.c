
#include "inc/raycast.h"
#include "inc/struct.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  t_info *info;
  t_map *map;
  // void *mlx;

  info = malloc(sizeof(t_info));
  map = malloc(sizeof(t_map));
  map->info = info;
  // entry_point(info);

  renderer(map);
  free(info);
  free(map);
  return 1;
}
