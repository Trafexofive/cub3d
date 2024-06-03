
#ifndef DRAW_H
#define DRAW_H

#include "struct.h"
#include <mlx.h>
#include <stdio.h>

void clear_window(t_info *info);
void draw_line(t_info *info, int len, t_point starting_position, bool mode);
void draw_anyline(t_map *map, t_point start, t_point end);
void draw_slant(t_info *info, t_point position, t_point target);
void draw_tile(t_info *info, int len, t_point starting_position);
void draw_wall_ver(t_info *info, int len, int count, t_point starting_position);
void draw_wall_hor(t_info *info, int len, int count, t_point starting_position);
void draw_grid(t_info *info, int len, int count, t_point starting_position);
void circle_octants(int centerX, int centerY, int x, int y, t_info *info);
void drawcircle(int centerx, int centery, int radius, t_info *info);
void draw_anyline(t_map *, t_point , t_point);
void    test(t_map *);

#endif
