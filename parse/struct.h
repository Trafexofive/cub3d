

typedef enum {
  north = 0,
  west = 1,
  east = 2,
  south = 3,

} t_comp;

typedef struct s_args {
  char **av;
  int ac;
} t_args;

typedef struct s_point // could be renamed to coordinate.
{
  unsigned int x;
  unsigned int y;
} t_point;

typedef struct s_map {
  char **map;
  t_point *player_pos;
  t_point *error_pos;
  bool debug;

} t_map;
