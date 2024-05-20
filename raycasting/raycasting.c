
// void key_hook(int key, t_game_info *game) {
//   if (key == W_KEY &&
//       check_collision(game->map[game->p_pos.y - 1][game->p_pos.x], game))
//     player_move(game, 0, -1);
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
#include "../inc/draw.h"
#include "../inc/macros.h"
#include "../inc/raycast.h"
#include "../inc/struct.h"

t_map load_map_data(t_map *map);

t_player *player_init(void) {
  t_player *player = malloc(sizeof(t_player));
  player->spawn.x = 50;
  player->spawn.y = 50;
  return (player);
}
void *info_init(t_info *info) {
  info->mlx = mlx_init();
  info->draw_pos.x = 100;
  info->draw_pos.y = 100;
  info->player_pos.x = 0;
  info->player_pos.y = 0;
  info->win_x = 1980;
  info->win_y = 1280;

  return NULL;
}

// typedef struct s_grid
// {
//     t_info *info;
//     int len;
//     int count
//
// } t_grid;

void render_player(t_map *map) {
  t_info *info = map->info;
  // info->draw_pos.x = 400;
  // info->draw_pos.y = 600;
  int centerX = map->player->spawn.x;
  int centerY = map->player->spawn.y;
  int radius = 15;

  drawcircle(centerX, centerY, radius, info);
  // draw_slant(info, 10, info->draw_pos, p);
  // draw_circle(info, 10, info->draw_pos);
}

void map_tile_morph(t_map *map) {
  int i = 0;
  int j = 0;
  t_info *info;

  info = map->info;

  int len = 30;

  while (map->map[i]) {

    while (map->map[i][j]) {
      if (map->map[i][j] == '1') {

        draw_tile(info, len, info->draw_pos);
      }
      if (map->map[i][j] == 'N' || map->map[i][j] == 'W' ||
          map->map[i][j] == 'S' || map->map[i][j] == 'E') {
        map->player->spawn.x = info->draw_pos.x;
        map->player->spawn.y = info->draw_pos.y;
        render_player(map);
      }
      info->draw_pos.x += len;
      j++;
    }
    info->draw_pos.y += len;
    info->draw_pos.x = 0;
    i++;
    j = 0;
  }
}

void render_minimap_term(t_map *map) {
  int i = 0;
  int fd = open("maps/map.cub", O_RDONLY);
  map->map = malloc(sizeof(char *));
  while (1) {
    map->map[i] = get_next_line(fd);
    printf("%s", map->map[i]);
    if (map->map[i] == NULL)
      break;
    i++;
  }
  close(fd);
  map_tile_morph(map);
}
//
// void new_image(t_img img, t_info *info) {
//   img.img = mlx_new_image(info->mlx, info->win_x - 1, info->win_y - 1);
// }

// void    hooks(t_info *info)
// {
//   mlx_loop_hook(info->mlx, ,void *param);
//
// }
//
//

// void    load_textures(t_texture *textures);

void renderer(t_map *map) {
  t_info *info = map->info;

  info_init(info);
  info->mlx_win = mlx_new_window(info->mlx, info->win_x, info->win_y, "Cub3d");
  map->player = player_init();
  // hooks(info);

  render_minimap_term(map);
  mlx_loop(info->mlx);
}
