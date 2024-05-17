
#include "../inc/raycast.h"
#include "../inc/struct.h"

t_map load_map_data(t_map *map);

void *info_init(t_info *info) {
  info->mlx = mlx_init();
  info->win_size_x = 1280;
  info->win_size_y = 1080;

  return NULL;
}

void clear_window(t_info *info) { mlx_clear_window(info->mlx, info->mlx_win); }

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
  // draw_square(map);
}

void    init_img(t_img img)
{


}

void draw_test(t_info *info) {
  t_img img;

  img.img = mlx_new_image(info->mlx, 32, 32);
  img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                               &img.endian);
  mlx_put_image_to_window(info->mlx, info->mlx_win, img.img, 40, 40);
  mlx_pixel_put(info->mlx, &img, 40, 40, 0x00FF0000);
    fprintf(stderr, "%s\n", "break");

  mlx_put_image_to_window(info->mlx, info->mlx_win, img.img, 0, 0);
  // mlx_put_image_to_window(info->mlx, info->mlx_win, img.img, 0, 0);
  // mlx_put_image_to_window(info->mlx, info->mlx_win, img.img, 0, 0);
  // mlx_put_image_to_window(info->mlx, info->mlx_win, img.img, 0, 0);
  // mlx_put_image_to_window(info->mlx, info->mlx_win, img.img, 0, 0);
  // mlx_put_image_to_window(info->mlx, info->mlx_win, img.img, 0, 0);
}
void render_screen(t_info *info) {
  // t_data img;

    draw_test(info);
  // mlx_string_put(info->mlx, info->mlx_win, 100, 100, 100, "hello world");
  //  clear_window(info);

  // img.img = mlx_new_image(mlx, 1920, 1080);
  // img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
  // &img.line_length,
  //                              &img.endian);
}

void renderer(t_map *map) {
    t_info *info = map->info;

  // void    load_textures(t_texture *textures);
  //render_minimap_term(map);

    info_init(info);
  info->mlx_win = mlx_new_window(info->mlx, info->win_size_x, info->win_size_y, "hello");
    draw_test(info);
    mlx_loop(info->mlx);
}
