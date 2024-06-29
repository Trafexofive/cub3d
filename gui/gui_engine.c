
#include "gui_engine.h"
#include "../inc/draw.h"
#include "../inc/macros.h"
#include "../inc/struct.h"

void element_init(t_elem *element) {
  element->async_priority = 0;
  element->selected = NIL;
  element->visibility = NIL;
  element->dimensions.width = DEFAULT_WIDTH;
  element->dimensions.height = DEFAULT_HEIGHT;
  element->position.x = 10;
  element->position.y = 10;
  element->next = NULL;
}

// void draw_box(t_mlx *mlx, t_box box) {}

t_elem *instantiate_element(t_elem *head, t_type type) {
  t_elem *new_element;

  while (head->next) {
    head = head->next;
  }
  new_element = malloc(sizeof(t_elem));
  element_init(new_element);
  head->next = new_element;
  // if (type == default)

  return (new_element);
}

// void    render_elements(t_elem *elements)
// {
//
// }

bool render_ui(t_elem *elements, t_mlx *mlx) {

  clear_window(mlx);
  // render_elements(elements);
}

void entry_point(t_mlx *mlx) {
  t_elem *elements;

  elements->next = NULL;
  instantiate_element(elements, 0);
  render_ui(elements, mlx);
}
