
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

void draw_box(t_mlx *mlx, t_elem *elements, t_point starting_position) {
  t_box box = elements->dimensions;
  draw_line(mlx, box.height, starting_position, VER);
  starting_position.x += box.width;
  draw_line(mlx, box.height, starting_position, VER);
  starting_position.x -= box.width;
  draw_line(mlx, box.width, starting_position, HOR);
  starting_position.y += box.height;
  draw_line(mlx, box.width, starting_position, HOR);
}

t_elem *instantiate_element(t_elem *head, t_type type) {
  t_elem *new_element;

  new_element = NULL;
  if (type == DEFAULT) {
    while (head->next) {
      head = head->next;
    }
    new_element = malloc(sizeof(t_elem));
    element_init(new_element);
    head->next = new_element;
    head->next->next = NULL;
  }
  // if (type == default)
  return (new_element);
}

void render_button(t_elem *elements) {
  t_mlx *mlx = elements->mlx;
  t_point p = elements->position;

  draw_box(mlx, elements, p);
}

void render_menu(t_elem *elements) { (void)elements; }

void render_selected_button(t_elem *elements) {
  // t_box box = elements->dimensions;

  render_button(elements);
  // draw_line(mlx, box.height, starting_position, VER);
  // starting_position.x += box.width;
  // draw_line(mlx, box.height, starting_position, VER);
  // starting_position.x -= box.width;
  // draw_line(mlx, box.width, starting_position, HOR);
  // starting_position.y += box.height;
  // draw_line(mlx, box.width, starting_position, HOR);
}

void render_elements(t_elem *elements) {
  if (elements->visibility == true) {
    if (elements->selected == true && elements->type == BUTTON)
      render_selected_button(elements);
    else if (elements->type == MENU)
      render_menu(elements);

  } else {
    return;
  }
}

bool render_ui(t_elem *elements) { // remove t_mlx from args already passing it in struct
  t_box box;
  t_point p;

  p.x = 100;
  p.y = 100;
  box.width = 300;
  box.height = 100;
  elements->position = p;
  elements->dimensions = box;

  while (elements->next) {
    render_elements(elements);
    elements = elements->next;
  }
  return (true);
}

void gui_entry_point(t_mlx *mlx) {
  t_elem *elements;

  //need to make the mlx struct work somehow, lazy thing to do is to pass it to every single instance, however there could be ways to improve it
  elements = malloc(sizeof(t_elem));
  element_init(elements);
  // puts("hello");
  instantiate_element(elements, DEFAULT);
  render_ui(elements);
}
