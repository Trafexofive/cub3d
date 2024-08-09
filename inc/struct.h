
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
  double x;
  double y;
} t_point;

typedef struct s_vector {
    t_point start;
    t_point end;
    double  len;
} t_vector;

typedef struct s_img {
  void *img;
  char *addr;
  int bpp;
  int line_length;
  int endian;
} t_img;

typedef struct s_game_vars {
    t_point draw_cursor;
    t_point player_position;
    double player_fov;
    
}t_game;

typedef struct s_player {
  double dirX, dirY;     // Player's direction vector
  double planeX, planeY; // Camera plane
    double angle;
  t_point spawn;
  double fov;
  t_comp player_dir;
  t_point position;
  t_vector last_ray;
  t_vector vector;
  bool spawned;

} t_player;

// rename to compositioning struct, map should only contain map related content
typedef struct s_map {
  t_player *player;
  t_mlx *mlx;
  char **map;
  struct s_menu **menus;
  struct s_menu *current_menu;
  bool debug;

} t_map;

// for spawnables (enemies / players)
//  typedef struct s_entities {
//
//
//  }t_entities;


typedef struct s_info {
  // t_point player_pos; player info in player struct
  // t_point draw_pos; irrelevent to infop
  t_mlx *mlx;
  char  wall_side;
  t_map *map; // could have multiple maps
  t_player *player;
  t_game *vars;
  t_img img;
  // maybe a game var struct could be implemented
  // int win_x; drawing function shouldnt rely on info struct, they should be
  // stand alone. int win_y; better defined as macros

} t_info;




typedef struct s_texture {
  t_img *img;
} t_texture;

#endif
