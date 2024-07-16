
#ifndef GUI
#define GUI

//----------------------------------- MACROS
//

#include "../inc/macros.h"
#include "../inc/mlx_struct.h"
#include "../inc/struct.h"
#include <stdbool.h>
#define DEFAULT_WIDTH 20
#define DEFAULT_HEIGHT 20
#define DEFAULT_MENU_HEIGHT 200
#define DEFAULT_MENU_WIDTH 400

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
  void *menu;
  bool visibility;
  bool hoverable; // if not jump to next element
  bool overlap;

  t_box dimensions;
  t_point position;
  int type;

  struct s_element *next;
  struct s_element *prev;

} t_elem;

typedef struct s_menu {
  t_mlx *mlx;
  const char *name;

  t_elem *head;
  t_elem *selected;

  struct s_menu *next;
  struct s_menu *prev;

} t_menu;
//------------------------------------------
//

// void draw_box(t_mlx *mlx, t_box box);
t_elem *instantiate_element(t_menu *menu, t_type type, t_mlx *);
void gui_entry_point(t_mlx *);
void scroll_down(t_menu *menu);
void scroll_up(t_menu *menu);

#endif
