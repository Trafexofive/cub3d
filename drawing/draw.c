
#include "../inc/draw.h"
#include "../inc/macros.h"
#include "../inc/struct.h"
#include <math.h>
#include <stdio.h>

void put_pixel(t_img *data, t_point pixel, int color) {
  char *dst;
  int x = pixel.x;
  int y = pixel.y;

  if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT) {
    dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
    *(unsigned int *)dst = color;
  }
}
