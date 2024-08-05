
#include "gui/gui_engine.h"
#include "inc/macros.h"
#include "inc/raycast.h"
#include "inc/struct.h"
#include "inc/utils.h"
#include "mlx_linux/mlx.h"
#include <math.h>
// #include "parse/parse/cub.h"
#include <stdio.h>
#include <stdlib.h>

void free_arr(char **arr) {
  int i = 0;
  while (arr[i] != NULL) {
    free(arr[i]);
  }
}

void free_all(t_info *info) {

  void *mlx;
  void *mlx_win;

  mlx = info->mlx->mlx;
  mlx_win = info->mlx->mlx_win;

  mlx_destroy_window(mlx, mlx_win);
  free(info);
  free(info->player);
  free_arr(info->map->map);
  free(info->map);
}

int is_wall(t_info *info, int x, int y) {
  if (x < 0 || x >= 20 || y < 0 || y >= 40)
    return 1;
  return (info->map->map[y][x] == '1');
}

void update_player_position(t_info *info, double move_speed,
                            double strafe_speed) {
  t_player *player = info->player;
  double move_x = cos(player->angle) * move_speed;
  double move_y = sin(player->angle) * move_speed;

  double strafe_x = cos(player->angle + M_PI / 2) * strafe_speed;
  double strafe_y = sin(player->angle + M_PI / 2) * strafe_speed;

  int current_tile_x = (int)(player->vector.start.x / TILE_SIZE);
  int current_tile_y = (int)(player->vector.start.y / TILE_SIZE);

  double new_x = player->vector.start.x + move_x + strafe_x;
  double new_y = player->vector.start.y + move_y + strafe_y;
  int new_tile_x = (int)(new_x / TILE_SIZE);
  int new_tile_y = (int)(new_y / TILE_SIZE);

  // Check collision in X direction
  if (current_tile_x != new_tile_x) {
    int check_x = (move_x + strafe_x > 0) ? new_tile_x : current_tile_x;
    if (!is_wall(info, check_x, current_tile_y) &&
        !is_wall(info, check_x,
                 current_tile_y +
                     (int)(player->vector.start.y + PLAYER_SIZE / 2) /
                         (int)TILE_SIZE % 1) &&
        !is_wall(info, check_x,
                 current_tile_y +
                     (int)(player->vector.start.y - PLAYER_SIZE / 2) /
                         TILE_SIZE % 1)) {
      player->vector.start.x = new_x;
    }
  } else {
    player->vector.start.x = new_x;
  }

  if (current_tile_y != new_tile_y) {
    int check_y = (move_y + strafe_y > 0) ? new_tile_y : current_tile_y;
    if (!is_wall(info, current_tile_x, check_y) &&
        !is_wall(info,
                 current_tile_x +
                     (int)(player->vector.start.x + PLAYER_SIZE / 2) /
                         TILE_SIZE % 1,
                 check_y) &&
        !is_wall(info,
                 current_tile_x +
                     (int)(player->vector.start.x - PLAYER_SIZE / 2) /
                         TILE_SIZE % 1,
                 check_y)) {
      player->vector.start.y = new_y;
    }
  } else {
    player->vector.start.y = new_y;
  }
}

void handle_player_movement(t_info *info, int key) {
  double move_speed = 1.0;
  double rotation_speed = 0.1;
  t_player *player = info->player;

  if (key == W_KEY)
    update_player_position(info, move_speed, 0);
  if (key == S_KEY)
    update_player_position(info, -move_speed, 0);
  if (key == A_KEY)
    update_player_position(info, 0, -move_speed);
  if (key == D_KEY)
    update_player_position(info, 0, move_speed);
  if (key == RIGHT_KEY) {
    player->angle += rotation_speed;
    if (player->angle < 0)
      player->angle += 2 * M_PI;
  }
  if (key == LEFT_KEY) {
    player->angle -= rotation_speed;
    if (player->angle > 2 * M_PI)
      player->angle -= 2 * M_PI;
  }
}

void key_hook(int key, t_info *info) {
  // printf("key value = %X\n", key);
  // printf("decimal key value = %d\n", key);

  if (key == ESC_KEY)
    free_all(info);
  else {
    handle_player_movement(info, key);
  }
}

void new_window(t_mlx *mlx) {

  mlx->mlx_win = mlx_new_window(mlx->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3d");
}

void init_minimap(t_map *map, const char *map_path) {
  int i = 0;
  (void)map_path;
  int fd = open(map_path, O_RDONLY);
  map->map = malloc(50 * sizeof(char *));
  while (1) {
    map->map[i] = get_next_line(fd);
    if (map->map[i] == NULL)
      break;
    printf("%s\n", map->map[i]);
    i++;
  }
  close(fd);
}

void new_image(t_info *info) {
  info->img.addr = mlx_new_image(info->mlx->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
}

int get_offset(t_img image, t_point pixel) {
  int x = pixel.x;
  int y = pixel.y;

  int offset = (y * image.line_length + x * (image.bpp / 8));
  return (offset);
}

bool game_init(t_info *info) {

  // t_menu *menu;
  t_mlx *mlx;
  t_map *map = info->map;

  // menu = malloc(sizeof(t_menu));
  mlx = info->mlx;
  // menu->mlx = mlx;
  // map->current_menu = menu;

  t_img image;

  new_window(info->mlx);

  image.img = mlx_new_image(mlx->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
  if (image.img == NULL)
    return false;
  image.addr = mlx_get_data_addr(image.img, &image.bpp, &image.line_length,
                                 &image.endian);
  info->img = image;

  // mlx_do_sync(map->info->mlx);
  init_minimap(map, "maps/map.cub");
  mlx_hook(mlx->mlx_win, 2, 1L << 0, (void *)key_hook, info);
  mlx_hook(mlx->mlx_win, 17, 0, (void *)free_all, info);
  // mlx_key_hook(mlx->mlx_win, (void *)key_hook, info);
  // mlx_key_hook(mlx->mlx_win, (void *)navigation_key_hook, menu);
  mlx_loop_hook(mlx->mlx, (void *)renderer, info);
  mlx_loop(mlx->mlx);
  return true;
}

void init_mlx(t_mlx *mlx) { mlx->mlx = mlx_init(); }

t_info *vars_init(int ac, char **av) {

    // t_data *data;
    
  t_info *info;
  t_map *map;
  t_mlx *mlx;

  (void) av, (void)ac;
  // data = parse_entry(ac, av);
  info = malloc(sizeof(t_info));
  map = malloc(sizeof(t_map));
  mlx = malloc(sizeof(t_mlx));

  init_mlx(mlx);
  map->mlx = mlx;
  info->mlx = mlx;
  info->map = map;

  // map->map = data->map;
  info->player = player_init();
  return (info);
}

int main(int ac, char **av) {
  game_init(vars_init(ac, av));
  return 1;
}
