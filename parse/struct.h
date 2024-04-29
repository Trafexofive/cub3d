#include <mlx.h>
#include <stdbool.h>

typedef enum {
  north = 0,
  west = 1,
  east = 2,
  south = 3,

} t_comp;

typedef struct s_point // could be renamed to coordinate.
{
  unsigned int x;
  unsigned int y;
} t_point;
typedef struct s_args {
  char **av;
  int ac;
} t_args;

typedef struct s_info {
  t_point *player_pos;
    void    *mlx_ptr;
    void    *mlx_window;
    int win_size_x;
    int win_size_y;
  t_point *error_pos; // points to NULL if no error is found, print the map the
                     // error and the error location
  t_comp *spawn_position;

} t_info;

typedef struct s_map {
  char **map;
  t_info *info;
  bool debug;

} t_map;
