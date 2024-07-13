#include "../inc/struct.h"
#include "../inc/macros.h"

#ifndef GUI
#define GUI

//----------------------------------- MACROS
//

#define DEFAULT_WIDTH 20
#define DEFAULT_HEIGHT 20

// typedef struct s_point// could be renamed to coordinate.
// {
//   int x;
//   int y;
// } t_point;

typedef struct s_box {
  int height;
  int width;

} t_box;

typedef enum {
  DEFAULT = 0,
  BUTTON = 1,
  TEXT = 2,
  MENU = 3

} t_type;

typedef struct s_element {
  t_mlx *mlx;

  int async_priority;

  bool selected;
  bool visibility;
  bool hoverable; // if not jump to next element
  bool overlap;

  t_box dimensions;
  t_point position;
  int   type;

  struct s_element *next;

} t_elem;

//------------------------------------------
//

// void draw_box(t_mlx *mlx, t_box box);
t_elem *instantiate_element(t_elem *head, t_type type);
void gui_entry_point(t_mlx *);


#endif
