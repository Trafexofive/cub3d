
#include "../inc/struct.h"
#include "../inc/macros.h"
#include "../inc/draw.h"
#include <mlx.h>

void clear_window(t_info *info) { mlx_clear_window(info->mlx, info->mlx_win); }

// left sided draw
void draw_line(t_info *info, int len, t_point starting_position, bool mode) {
  int i = 0;
  int x = starting_position.x;
  int y = starting_position.y;

  if (mode == true) {
    while (i < len) {
      mlx_pixel_put(info->mlx, info->mlx_win, x, y, COLOR);
      x++;
      i++;
    }
  } else {
    while (i < len) {
      mlx_pixel_put(info->mlx, info->mlx_win, x, y, COLOR);
      y++;
      i++;
    }
  }
}

void draw_slant(t_info *info, t_point position, t_point target) {
  int diff_x = target.x - position.x + 1;
  int diff_y = target.y - position.y + 1;
  float ratio = diff_x / diff_y;

  printf("diffx == %d\n", diff_x);
  printf("diffy == %d\n", diff_y);
  const float remainder = ratio - (int)ratio;
  printf("remainder == %f\n", remainder);

  (void)position;
  while (diff_x < 100) {
    mlx_pixel_put(info->mlx, info->mlx_win, diff_x, diff_y, COLOR);
    diff_x++;
    diff_y++;
  }
}

void draw_tile(t_info *info, int len, t_point starting_position) {
  draw_line(info, len, starting_position, VER);
  starting_position.x += len;
  draw_line(info, len, starting_position, VER);
  starting_position.x -= len;
  draw_line(info, len, starting_position, HOR);
  starting_position.y += len;
  draw_line(info, len, starting_position, HOR);
}

void draw_wall_ver(t_info *info, int len, int count,
                   t_point starting_position) {
  int i = 0;

  while (i < count) {
    draw_tile(info, len, starting_position);
    starting_position.y += len;
    i++;
  }
}

void draw_wall_hor(t_info *info, int len, int count,
                   t_point starting_position) {
  int i = 0;

  while (i < count) {
    draw_tile(info, len, starting_position);
    starting_position.x += len;
    i++;
  }
}

void draw_grid(t_info *info, int len, int count, t_point starting_position) {
  int i = 0;

  while (i < count) {
    draw_wall_hor(info, len, count, starting_position);
    starting_position.y += len;
    i++;
  }
}

void circle_octants(int centerX, int centerY, int x, int y, t_info *info) {
  // Draw points in all eight octants
  mlx_pixel_put(info->mlx, info->mlx_win, centerX + x, centerY + y,
                COLOR); // Octant 1
  mlx_pixel_put(info->mlx, info->mlx_win, centerX + x, centerY - y,
                COLOR); // Octant 1
  mlx_pixel_put(info->mlx, info->mlx_win, centerX - x, centerY - y,
                COLOR); // Octant 1
  mlx_pixel_put(info->mlx, info->mlx_win, centerX - x, centerY + y,
                COLOR); // Octant 1
  mlx_pixel_put(info->mlx, info->mlx_win, centerX + y, centerY + x,
                COLOR); // Octant 1
  mlx_pixel_put(info->mlx, info->mlx_win, centerX - y, centerY + x,
                COLOR); // Octant 1
  mlx_pixel_put(info->mlx, info->mlx_win, centerX - y, centerY - x,
                COLOR); // Octant 1
  mlx_pixel_put(info->mlx, info->mlx_win, centerX + y, centerY - x,
                COLOR); // Octant 1
}

void drawcircle(int centerx, int centery, int radius, t_info *info) {
  int x = 0;
  int y = radius;
  int d = 3 - 2 * radius;

  // Draw the initial points on the circle
  circle_octants(centerx, centery, x, y, info);

  // Loop to draw the circle using Bresenham's algorithm
  while (y >= x) {
    x++;
    // Update the decision parameter based on its current value
    if (d > 0) {
      y--;
      d = d + 4 * (x - y) + 10;
    } else {
      d = d + 4 * x + 6;
    }
    // Draw the points for the current (x, y)
    circle_octants(centerx, centery, x, y, info);
  }
}
