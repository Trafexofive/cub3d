#ifndef GUI
#define GUI

//----------------------------------- MACROS
//

#include <typeinfo>
#define DEFAULT_WIDTH 20
#define DEFAULT_HEIGHT 20

typedef struct s_pos // could be renamed to coordinate.
{
  int x;
  int y;
} t_pos;

typedef struct s_mlx {
  void *mlx;
  void *mlx_win;
} t_mlx;

typedef struct s_box {
  int height;
  int width;

} t_box;

typedef enum {
  text_only = 0,
  button = 1,


} t_type;

typedef struct s_element {
  t_mlx *mlx;

  int async_priority;

  bool selected;
  bool visibility;
  bool hoverable; // if not jump to next element

  t_box dimensions;
  t_pos position;

  s_element *next;

} t_elem;

#endif
