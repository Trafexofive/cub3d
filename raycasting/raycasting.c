
#include "../inc/raycast.h"
#include "../inc/struct.h"

void renderer(t_map *map) {
  // void    load_textures(t_texture *textures);
  int i = 0;
  int fd = open("maps/map.cub", RDONLY);
  char **map = get_next_line(fd);
  while (map[i]) {
    printf("%s\n", map[i]);
    i++;
  }
}

void clear_window(t_info *info) { mlx_clear_window(info->mlx, info->mlx_win); }

t_map load_map_data(t_map *map);

// void render_screen(t_info *info) {
//
//   void *window;
//   t_data img;
//   void *mlx;
//   void *mlx_win;
//
//   mlx = info->mlx_ptr;
//   window = mlx_new_window(info->mlx_ptr, info->win_size_x, info->win_size_y,
//                           "hello");
//   info->mlx_window = window;
//   mlx_win = info->mlx_window;
//   mlx_string_put(info->mlx_ptr, info->mlx_window, 100, 100, 100, "hello
//   world");
//   // clear_window(info);
//   img.img = mlx_new_image(mlx, 1920, 1080);
//   img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
//   &img.line_length,
//                                &img.endian);
//   img.img = mlx_new_image(mlx, 1920, 1080);
//   img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
//   &img.line_length,
//                                &img.endian);
//   mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
//   mlx_pixel_put(mlx, &img, 5, 5, 0x00FF0000);
//   mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
// }

void *info_init(t_info *info) {
  info->mlx_ptr = mlx_init();
  info->win_size_x = 1280;
  info->win_size_y = 1080;

  return NULL;
}
