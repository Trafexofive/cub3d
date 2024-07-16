
#include "gui_engine.h"
#include "../inc/draw.h"
#include "../inc/macros.h"
#include "../inc/struct.h"
#include "../lib/libft/libft.h"
#include <stdio.h>

void navigation_key_hook(int key, t_menu *menu) {
  printf("key value = %X\n", key);
  printf("decimal key value = %d\n", key);

  if (key == J_KEY)
    scroll_down(menu->selected, menu);
  if (key == K_KEY)
    scroll_up(menu->selected, menu);
  // if (key == ESC_KEY)
  //   free_all(map);
}

void element_init(t_elem *element, t_mlx *mlx) {
  element->mlx = mlx;
  element->async_priority = 0;
  element->selected = NIL;
  element->visibility = true;
  element->dimensions.width = DEFAULT_ELEMENT_WIDTH;
  element->dimensions.height = DEFAULT_ELEMENT_HEIGHT;
  element->position.x = 10;
  element->position.y = 10;
  element->next = NULL;
  element->type = BUTTON;
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

// t_elem *instantiate_menu(t_elem *elements, t_type type, t_mlx *mlx)
// {
//
//
// }

void rename_menu(t_menu *menu, const char *name) {
  menu->name = ft_strdup(name);
}

t_elem *instantiate_element(t_menu *menu, t_type type, t_mlx *mlx) {
  t_elem *new_element;
  t_elem *head;

  new_element = NULL;
  if (!menu->head) {
    new_element = malloc(sizeof(t_elem));
    element_init(new_element, mlx);
    return (new_element);
  } else
    head = menu->head;

  while (head->next) {
    head = head->next;
  }
  (void)type;
  new_element = malloc(sizeof(t_elem));
  element_init(new_element, mlx);
  head->next = new_element;
  new_element->prev = head;
  // if (type == default)
  return (new_element);
}

void render_button(t_elem *elements) {
  t_mlx *mlx = elements->mlx;
  t_point p = elements->position;
  // t_box box = elements->dimensions;

  // printf("box W :%d\n", box.width);
  // printf("box H :%d\n", box.height);
  draw_box(mlx, elements, p);
}

void render_selected_button(t_elem *elements) {
  t_point pos = elements->position;

  render_button(elements);
  elements->dimensions.height *= SCALE_FACTOR;
  elements->dimensions.width *= SCALE_FACTOR;
  elements->position.x /= SCALE_FACTOR;
  drawcircle(elements->position.x, elements->position.y, 13, elements->mlx);
  // elements->position.y /= SCALE_FACTOR;
  // printf("scaled box W :%d\n", box.width);
  // printf("scaled box H :%d\n", box.height);
  // render_button(elements);
  elements->position = pos;
}

void render_elements(t_menu *menu, t_elem *elements) {
    (void) menu;
  if (elements->visibility == true) {
    if (elements->selected == true && elements->type == BUTTON)
      render_selected_button(elements);
    // else if (elements->type == MENU)
    //   render_menu(menu);
    else if (elements->selected == NIL && elements->type == BUTTON)
      render_button(elements);

  } else {
    return;
  }
}

bool render_ui(t_menu *menu) {
  // remove t_mlx from args already passing it in struct
  t_elem *elements = menu->head;

  while (elements) {
    render_elements(menu, elements);
    elements = elements->next;
    if (elements == NULL)
      break;
    elements->position.x = 320 + elements->prev->position.x;
  }
  return (true);
}

//

void menu_init(t_menu *menu, t_mlx *mlx) {
  menu->next = NULL;
  menu->prev = NULL;
  menu->head = NULL;
  menu->mlx = mlx;
}

void gui_entry_point(t_menu *menu) {

  t_elem *elem_ptr;
  t_mlx *mlx = menu->mlx;
  // need to make the mlx struct work somehow, lazy thing to do is to pass it to
  // every single instance, however there could be ways to improve it

  menu_init(menu, mlx);
  menu->head = instantiate_element(menu, DEFAULT, mlx);
  instantiate_element(menu, DEFAULT, mlx);
  elem_ptr = instantiate_element(menu, DEFAULT, mlx);
  elem_ptr->selected = true;
  menu->selected = elem_ptr;

  instantiate_element(menu, DEFAULT, mlx);
  instantiate_element(menu, DEFAULT, mlx);
  instantiate_element(menu, DEFAULT, mlx);
  instantiate_element(menu, DEFAULT, mlx);
  instantiate_element(menu, DEFAULT, mlx);
  instantiate_element(menu, DEFAULT, mlx);

  render_ui(menu);
}
