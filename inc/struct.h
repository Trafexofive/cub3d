
#ifndef STRUCT_H
# define STRUCT_H

#include <mlx.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include "../lib/get_next_line/get_next_line.h"
//#include <fcntl.h>


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

typedef struct s_info {
  t_point *player_pos;
    t_point draw_pos;
    void    *mlx;
    void    *mlx_win;
    int win_size_x;
    int win_size_y;
  t_point *error_pos; // points to NULL if no error is found, print the map the
                     // error and the error location
  t_comp *spawn_position;

} t_info;

typedef struct s_map {
  t_info *info;
  char **map;
  bool debug;

} t_map;

// typedef struct s_grid
// {
//
// } t_grid;
//

typedef struct	s_img{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

#endif
