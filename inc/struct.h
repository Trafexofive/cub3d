
#ifndef STRUCT_H
#define STRUCT_H

#include "../lib/get_next_line/get_next_line.h"

#include "../inc/mlx_struct.h"
#include "../lib/libft/libft.h"
#include <mlx.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
// #include <fcntl.h>

typedef enum {
  north = 0,
  west = 1,
  east = 2,
  south = 3,

} t_comp;

typedef struct s_point // could be renamed to coordinate.
{
  int x;
  int y;
} t_point;

typedef struct s_args {
  char **av;
  int ac;
} t_args;
typedef struct s_player {
  double dirX, dirY;     // Player's direction vector
  double planeX, planeY; // Camera plane
  t_point spawn;
  t_comp player_dir;
  t_point position;
  bool spawned;

} t_player;

typedef struct s_info {
  t_point player_pos;
  t_point draw_pos;
  void *mlx;
  void *mlx_win;
  int win_x;
  int win_y;

  t_comp player_dir;
} t_info;

// rename to compositioning struct, map should only contain map related content
typedef struct s_map {
  t_player *player;
  t_info *info;
  t_mlx *mlx;
  char **map;
  struct s_menu **menus;
  struct s_menu *current_menu;
  bool debug;

} t_map;

// typedef struct s_grid
// {
//
// } t_grid;
//

typedef struct s_img {
  void *img;
  char *addr;
  int bits_per_pixel;
  int line_length;
  int endian;
} t_img;

typedef struct s_texture {
  t_img *img;
} t_texture;

#endif
