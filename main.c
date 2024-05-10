
#include "inc/raycast.h"
#include "inc/struct.h"
#include <stdio.h>
#include <stdlib.h>

// typedef struct s_info {
//   t_point *player_pos;
//     void    *mlx_ptr;
//     void    *mlx_window;
//     int win_size_x;
//     int win_size_y;
//   t_point *error_pos; // points to NULL if no error is found, print the map
//   the
//                      // error and the error location
//   t_comp *spawn_position;
//
// } t_info;
//

void clear_window(t_info *info) {

  mlx_clear_window(info->mlx_ptr, info->mlx_window);
}

// t_map   load_map_data(info)

void render_screen(t_info *info) {

  void *window;
  t_data img;
  void *mlx;
  void *mlx_win;

  mlx = info->mlx_ptr;
  window = mlx_new_window(info->mlx_ptr, info->win_size_x, info->win_size_y,
                          "hello");
  info->mlx_window = window;
  mlx_win = info->mlx_window;
  mlx_string_put(info->mlx_ptr, info->mlx_window, 100, 100, 100, "hello world");
  // clear_window(info);
  img.img = mlx_new_image(mlx, 1920, 1080);
  img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                               &img.endian);
  img.img = mlx_new_image(mlx, 1920, 1080);
  img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                               &img.endian);
  mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
  mlx_pixel_put(mlx, &img, 5, 5, 0x00FF0000);
  mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
}

void *info_init(t_info *info) {
  info->mlx_ptr = mlx_init();
  info->win_size_x = 1280;
  info->win_size_y = 1080;

  return NULL;
}

void entry_point(t_info *info) {
  info_init(info);
  fprintf(stderr, "%s\n", "break");
  render_screen(info);
  mlx_loop(info->mlx_ptr);
}

int main() {
  t_info *info;
  t_map *map;
  void *mlx;

  info = malloc(sizeof(t_info));
  map = malloc(sizeof(t_map));
  map->info = info;
  entry_point(info);
  mlx = info->mlx_ptr;
  // img.img = mlx_new_image(info->mlx_ptr, 1920, 1080);

  /*
  ** After creating an image, we can call `mlx_get_data_addr`, we pass
  ** `bits_per_pixel`, `line_length`, and `endian` by reference. These will
  ** then be set accordingly for the *current* data address.
  */
  // img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
  // &img.line_length,
  //                              &img.endian);

  free(info);
  return 1;
}
