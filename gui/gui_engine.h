#include "../inc/struct.h"
#include "../inc/macros.h"

#ifndef GUI
#define GUI

//----------------------------------- MACROS
//

#define DEFAULT_WIDTH 20
#define DEFAULT_HEIGHT 20

typedef struct s_pos // could be renamed to coordinate.
{
  int x;
  int y;
} t_pos;

typedef struct s_box {
  int height;
  int width;

} t_box;

typedef enum {
  DEFAULT = 0,
  BUTTON = 1,
  TEXT = 2

} t_type;

typedef struct s_element {
  t_mlx *mlx;

  int async_priority;

  bool selected;
  bool visibility;
  bool hoverable; // if not jump to next element
  bool overlap;

  t_box dimensions;
  t_pos position;

  struct s_element *next;

} t_elem;

//------------------------------------------
//

// void draw_box(t_mlx *mlx, t_box box);
t_elem *instantiate_element(t_elem *head, t_type type);

#endif
