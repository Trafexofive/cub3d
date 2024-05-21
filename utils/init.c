

#include "../inc/utils.h"


t_map load_map_data(t_map *map);

t_player *player_init(void) {
  t_player *player = malloc(sizeof(t_player));
  player->spawn.x = 0;
  player->spawn.y = 0;
  return (player);
}

void *info_init(t_info *info) {
  info->mlx = mlx_init();
  info->draw_pos.x = 0;
  info->draw_pos.y = 100;
  info->player_pos.x = 0;
  info->player_pos.y = 0;
    // info->spawn_position = north;

  info->win_x = 1980;
  info->win_y = 1280;

  return NULL;
}
