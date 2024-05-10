
#include "inc/struct.h"
#include "inc/raycast.h"
#include <stdio.h>
#include <stdlib.h>

// typedef struct s_info {
//   t_point *player_pos;
//     void    *mlx_ptr;
//     void    *mlx_window;
//     int win_size_x;
//     int win_size_y;
//   t_point *error_pos; // points to NULL if no error is found, print the map
//   the
//                      // error and the error location
//   t_comp *spawn_position;
//
// } t_info;
//

void clear_window(t_info *info) {

  mlx_clear_window(info->mlx_ptr, info->mlx_window);
}

// t_map   load_map_data(info)

void render_screen(t_info *info) {

  void *window;
  window = mlx_new_window(info->mlx_ptr, info->win_size_x, info->win_size_y,
                          "hello");
  info->mlx_window = window;
  mlx_string_put(info->mlx_ptr, info->mlx_window, 100, 100, 100, "hello world");
  // clear_window(info);
}

void *info_init(t_info *info) {
  info->mlx_ptr = mlx_init();
  info->win_size_x = 1000;
  info->win_size_y = 1000;

  return NULL;
}

void entry_point(t_info *info) {
  info_init(info);
  fprintf(stderr, "%s\n", "break");
  render_screen(info);
  mlx_loop(info->mlx_ptr);
}

int main() {
  t_info *info;

  info = malloc(sizeof(t_info));
  entry_point(info);

  free(info);

  return 1;
}
