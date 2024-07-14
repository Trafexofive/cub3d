
#include "gui_engine.h"
#include "../inc/draw.h"
#include "../inc/macros.h"
#include "../inc/struct.h"

void element_init(t_elem *element, t_mlx *mlx) {
  element->mlx = mlx;
  element->async_priority = 0;
  element->selected = NIL;
  element->visibility = true;
  element->dimensions.width = DEFAULT_WIDTH;
  element->dimensions.height = DEFAULT_HEIGHT;
  element->position.x = 10;
  element->position.y = 10;
  element->next = NULL;
  element->type = BUTTON;
}

void draw_box(t_mlx *mlx, t_elem *elements, t_point starting_position) {
  t_box box = elements->dimensions;
  puts("hello");
  draw_line(mlx, box.height, starting_position, VER);
  starting_position.x += box.width;
  draw_line(mlx, box.height, starting_position, VER);
  starting_position.x -= box.width;
  draw_line(mlx, box.width, starting_position, HOR);
  starting_position.y += box.height;
  draw_line(mlx, box.width, starting_position, HOR);
}

t_elem *instantiate_element(t_elem *head, t_type type, t_mlx *mlx) {
  t_elem *new_element;

  new_element = NULL;
  if (type == DEFAULT) {
    while (head->next) {
      head = head->next;
    }
    new_element = malloc(sizeof(t_elem));
    element_init(new_element, mlx);
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

void render_menu(t_elem *elements) { 

    // when current element is menu, disable visibility for for all other buttons or make menus have pointer arrays for there own buttons;

    (void)elements; }

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
    else if (elements->selected == NIL && elements->type == BUTTON)
        render_button(elements);

  } else {
    return;
  }
}

t_element   *instatiate_menu(t_elem *elements, t_type type, t_mlx *mlx)
{

}

bool render_ui(t_elem *elements) {
  // remove t_mlx from args already passing it in struct
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

  // need to make the mlx struct work somehow, lazy thing to do is to pass it to
  // every single instance, however there could be ways to improve it
  elements = malloc(sizeof(t_elem));
  element_init(elements, mlx);
  // puts("hello");
  instantiate_element(elements, DEFAULT, mlx);
    
  instantiate_menu(elements, MENU, mlx);
  instantiate_menu(elements, MENU, mlx);
  render_ui(elements);
}
