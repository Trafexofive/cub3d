
#include "../inc/raycast.h"
#include "../inc/struct.h"

#define COLOR 0xFF5733
#define VER false
#define HOR true

t_map load_map_data(t_map *map);

void *info_init(t_info *info) {
  info->mlx = mlx_init();
  info->draw_pos.x = 0;
  info->draw_pos.y = 0;
  info->win_size_x = 1280;
  info->win_size_y = 1080;

  return NULL;
}

void clear_window(t_info *info) { mlx_clear_window(info->mlx, info->mlx_win); }

// left sided draw
void draw_line(t_info *info, int len, t_point starting_position, bool mode) {
  int i = 0;
  int x = starting_position.x;
  int y = starting_position.y;

  if (mode == true) {
    while (i < len) {
      mlx_pixel_put(info->mlx, info->mlx_win, x, y, COLOR);
      x++;
      i++;
    }
  } else {
    while (i < len) {
      mlx_pixel_put(info->mlx, info->mlx_win, x, y, COLOR);
      y++;
      i++;
    }
  }
}

void    draw_tile(t_info *info, int len, t_point starting_position)
{
  draw_line(info, len, starting_position, VER);
    starting_position.x += len;
  draw_line(info, len, starting_position, VER);
    starting_position.x -= len;
  draw_line(info, len, starting_position, HOR);
    starting_position.y += len;
  draw_line(info, len, starting_position, HOR);
}

void    draw_wall_ver(t_info *info, int len , int count, t_point starting_position)
{
    int i = 0;

    while (i < count)
    {
        draw_tile(info, len, starting_position);
        starting_position.y += len;
        i++;
    } 
}

void    draw_wall_hor(t_info *info, int len , int count, t_point starting_position)
{
    int i = 0;

    while (i < count)
    {
        draw_tile(info, len, starting_position);
        starting_position.x += len;
        i++;
    } 
}

void draw_grid(t_info *info) 
{

    (void) info;
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
  // draw_grid(map);
  // draw_square(map);
}

// void    init_img(t_img img)
// {
//
//
// }

void renderer(t_map *map) {
  t_info *info = map->info;

  // void    load_textures(t_texture *textures);
  // render_minimap_term(map);

  info_init(info);
  info->mlx_win =
      mlx_new_window(info->mlx, info->win_size_x, info->win_size_y, "hello");
  // draw_test(info);
  t_point p;

  p.x = 5;
  p.y = 50;
    draw_wall_hor(info, 100, 10, p);
    p.y += 100;
    draw_wall_hor(info, 100, 10, p);
  mlx_loop(info->mlx);
}
