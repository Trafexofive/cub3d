
#include "../inc/macros.h"
#include "../inc/struct.h"
#include "../inc/draw.h"
#include <math.h>
#include <stdio.h>

#define M_PI 3.14159265358979323846

typedef struct {
  int x, y;
} Point;

double degrees_to_radians(double degrees) { return degrees * (M_PI / 180.0); }

t_point calculate_endpoint(t_point start, double angle, double length) {
  t_point end;
  end.x = start.x + (int)(length * cos(angle));
  end.y = start.y + (int)(length * sin(angle));
  return end;
}

void test(t_map *map) {

  t_point center = map->player->spawn;// Center point
  double length = 50;          // Length of each line
  int num_lines = 50;          // Number of lines to draw
  double angle_increment = 360.0 / num_lines;
  int i = 0;

  while (i < num_lines) {
    double angle_deg = i * angle_increment;
    double angle_rad = degrees_to_radians(angle_deg);
    t_point end = calculate_endpoint(center, angle_rad, length);
    i++;
    draw_anyline(map, center, end);
  }
        usleep(100);
}
