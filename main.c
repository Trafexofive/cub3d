
#include "gui/gui_engine.h"
#include "inc/macros.h"
#include "inc/raycast.h"
#include "inc/struct.h"
#include "inc/utils.h"
#include "mlx_linux/mlx.h"
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

int is_valid_position(t_info *info, double x, double y) {
  int map_x = (int)(x / TILE_SIZE);
  int map_y = (int)(y / TILE_SIZE);

  if (map_x < 0 || map_x >= 10 || map_y < 0 || map_y >= 40) {
    return 0; // Out of bounds
  }

  return (info->map->map[map_y][map_x] == '0'); // '0' represents empty space
}

void update_player_position(t_info *info, double move_speed,
                            double strafe_speed) {
    t_player *player = info->player;
  double move_x = cos(player->angle) * move_speed;
  double move_y = sin(player->angle) * move_speed;

  double strafe_x = cos(player->angle + M_PI / 2) * strafe_speed;
  double strafe_y = sin(player->angle + M_PI / 2) * strafe_speed;

  double new_x = player->vector.start.x + move_x + strafe_x;
  double new_y = player->vector.start.y + move_y + strafe_y;

  // if (is_valid_position(info, new_x, new_y)) {
    player->vector.start.x = new_x;
    player->vector.start.y = new_y;
  // }
}

void handle_player_movement(t_info *info, int key) {
  double move_speed = 5.0; // Adjust this value to change movement speed
  // double rotation_speed = 0.1; // Adjust this value to change rotation speed

  if (key == W_KEY)
    update_player_position(info, move_speed, 0);
  if (key == S_KEY)
    update_player_position(info, -move_speed, 0);
  if (key == A_KEY)
    update_player_position(info, 0, -move_speed);
  if (key == D_KEY)
    update_player_position(info, 0, move_speed);

  // if (info->keys[LEFT_KEY]) {
  //     player->angle -= rotation_speed;
  //     if (player->angle < 0) player->angle += 2 * M_PI;
  // }
  // if (info->keys[RIGHT_KEY]) {
  //     player->angle += rotation_speed;
  //     if (player->angle > 2 * M_PI) player->angle -= 2 * M_PI;
  // }
}

// void player_move_w(t_player *player) { player->vector.start.y -= MOVE_SPEED; }
// void player_move_s(t_player *player) { player->vector.start.y += MOVE_SPEED; }
// void player_move_a(t_player *player) { player->vector.start.x -= MOVE_SPEED; }
// void player_move_d(t_player *player) { player->vector.start.x += MOVE_SPEED; }

void player_look_left(t_player *player) {

  player->angle -= 0.1;
}

void player_look_right(t_player *player) {

  player->angle += 0.1;
}
//
void key_hook(int key, t_info *info) {
  // printf("key value = %X\n", key);
  // printf("decimal key value = %d\n", key);
  t_player *player = info->player;

  if (key == RIGHT_KEY)
    player_look_right(player);
  else if (key == LEFT_KEY)
    player_look_left(player);
  else if (key == ESC_KEY)
    free_all(info);
  else {
    handle_player_movement(info, key);
  }
}

// make map an arr to make it possible creating multiple windows and pulling
// them by index
void new_window(t_mlx *mlx) {

  mlx->mlx_win = mlx_new_window(mlx->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3d");
}

void init_minimap(t_map *map, const char *map_path) {
  int i = 0;
  (void)map_path;
  int fd = open(map_path, O_RDONLY);
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

  // assign RGB value to a pixel

  // mlx_do_sync(map->info->mlx);
  init_minimap(map, "maps/map.cub");
  mlx_hook(mlx->mlx_win, 2, 1L << 0, (void *)key_hook, info);
  mlx_hook(mlx->mlx_win, 17, 0, (void *)free_all, info);
  // mlx_key_hook(mlx->mlx_win, (void *)key_hook, info);
  // mlx_key_hook(mlx->mlx_win, (void *)navigation_key_hook, menu);
  // clear_window(mlx);
  mlx_loop_hook(mlx->mlx, (void *)renderer, info);
  mlx_loop(mlx->mlx);
  return true;
}

void init_mlx(t_mlx *mlx) { mlx->mlx = mlx_init(); }

t_info *vars_init() {

  t_info *info;
  t_map *map;
  t_mlx *mlx;

  info = malloc(sizeof(t_info));
  map = malloc(sizeof(t_map));
  mlx = malloc(sizeof(t_mlx));

  init_mlx(mlx);
  map->mlx = mlx;
  info->mlx = mlx;
  info->map = map;

  info->player = player_init();
  info->player->vector.len = -1;
  return (info);
}

int main() {
  game_init(vars_init());
  return 1;
}
