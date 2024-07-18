

#include "../inc/utils.h"

t_map load_map_data(t_map *map);

t_player *player_init(void) {
  t_player *player = malloc(sizeof(t_player));
  player->spawn.x = 0;
  player->spawn.y = 0;
  player->position.x = 0;
  player->position.y = 0;
  player->spawned = false;
  return (player);
}

// void info_init(t_info *info) {
//
//
//
//   return;
// }
