
#include "../inc/draw.h"
#include "../inc/macros.h"
#include "../inc/struct.h"
#include <math.h>
#include <mlx.h>

// in IT computer graphics vectors are considered as points. 

t_point add_vector(t_point start, t_point end)
{
    t_point vector;

    vector.x = start.x + end.x;
    vector.y = start.y + end.y;
    return (vector);

}
//return = (v1.x - v2.x).(v1.y - v2.y)
t_point subtract_vector(t_point start, t_point end)
{
    // returns the vecter pointing at start pos from end pos
    t_point vector;

    vector.x = start.x - end.x;
    vector.y = start.y - end.y;
    return (vector);
}

int vector_len(t_point vector)
{
    int len;
    int x  = vector.x;
    int y  = vector.y;

    len = sqrt((x * x) + (y * y));

    return (len);
}

int vector_len_sqrt(t_point vector)
{
    int len;
    int x  = vector.x;
    int y  = vector.y;

    len = (x * x) + (y * y);

    return (len);
}

void clear_window(t_mlx *mlx) { mlx_clear_window(mlx->mlx, mlx->mlx_win); }

// left sided draw
void draw_line(t_mlx *mlx, int len, t_point starting_position, bool mode) {
  int i = 0;
  int x = starting_position.x;
  int y = starting_position.y;

  if (mode == true) {
    while (i < len) {
      mlx_pixel_put(mlx->mlx, mlx->mlx_win, x, y, COLOR);
      x++;
      i++;
    }
  } else {
    while (i < len) {
      mlx_pixel_put(mlx->mlx, mlx->mlx_win, x, y, COLOR);
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
    mlx_pixel_put(info->mlx->mlx, info->mlx->mlx_win, diff_x, diff_y, COLOR);
    diff_x++;
    diff_y++;
  }
}

void draw_anyline(t_map *map, t_point start, t_point end) {
  int dx = fabs(end.x - start.x);
  int dy = fabs(end.y - start.y);
  int sx = start.x < end.x ? 1 : -1;
  int sy = start.y < end.y ? 1 : -1;
  int err = dx - dy;
  t_mlx *mlx = map->mlx;

  while (1) {
    mlx_pixel_put(mlx->mlx, mlx->mlx_win, start.x, start.y, COLOR);

    if (start.x == end.x && start.y == end.y)
      break;
    int e2 = 2 * err;
    if (e2 > -dy) {
      err -= dy;
      start.x += sx;
    }
    if (e2 < dx) {
      err += dx;
      start.y += sy;
    }
  }
}

void draw_tile(t_mlx *mlx , int len, t_point starting_position) {
  draw_line(mlx , len, starting_position, VER);
  starting_position.x += len;
  draw_line(mlx, len, starting_position, VER);
  starting_position.x -= len;
  draw_line(mlx, len, starting_position, HOR);
  starting_position.y += len;
  draw_line(mlx, len, starting_position, HOR);
}

void draw_wall_ver(t_mlx *mlx, int len, int count,
                   t_point starting_position) {
  int i = 0;

  while (i < count) {
    draw_tile(mlx, len, starting_position);
    starting_position.y += len;
    i++;
  }
}

void draw_wall_hor(t_mlx *mlx, int len, int count,
                   t_point starting_position) {
  int i = 0;

  while (i < count) {
    draw_tile(mlx, len, starting_position);
    starting_position.x += len;
    i++;
  }
}

void draw_grid(t_mlx *mlx , int len, int count, t_point starting_position) {
  int i = 0;

  while (i < count) {
    draw_wall_hor(mlx, len, count, starting_position);
    starting_position.y += len;
    i++;
  }
}

void circle_octants(int centerX, int centerY, int x, int y, t_mlx *mlx) {
  // Draw points in all eight octants
  mlx_pixel_put(mlx->mlx, mlx->mlx_win, centerX + x, centerY + y,
                COLOR); // Octant 1
  mlx_pixel_put(mlx->mlx, mlx->mlx_win, centerX + x, centerY - y,
                COLOR); // Octant 1
  mlx_pixel_put(mlx->mlx, mlx->mlx_win, centerX - x, centerY - y,
                COLOR); // Octant 1
  mlx_pixel_put(mlx->mlx, mlx->mlx_win, centerX - x, centerY + y,
                COLOR); // Octant 1
  mlx_pixel_put(mlx->mlx, mlx->mlx_win, centerX + y, centerY + x,
                COLOR); // Octant 1
  mlx_pixel_put(mlx->mlx, mlx->mlx_win, centerX - y, centerY + x,
                COLOR); // Octant 1
  mlx_pixel_put(mlx->mlx, mlx->mlx_win, centerX - y, centerY - x,
                COLOR); // Octant 1
  mlx_pixel_put(mlx->mlx, mlx->mlx_win, centerX + y, centerY - x,
                COLOR); // Octant 1
}

void drawcircle(int centerx, int centery, int radius, t_mlx *mlx) {
  int x = 0;
  int y = radius;
  int d = 3 - 2 * radius;

  // Draw the initial points on the circle
  circle_octants(centerx, centery, x, y, mlx);

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
    circle_octants(centerx, centery, x, y, mlx);
  }
}
