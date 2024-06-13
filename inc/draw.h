
#ifndef DRAW_H
#define DRAW_H

#include "struct.h"
#include <mlx.h>
#include <stdio.h>

void clear_window(t_info *info);
void draw_line(t_mlx *mlx, int len, t_point starting_position, bool mode);
void draw_slant(t_info *info, t_point position, t_point target);
void draw_tile(t_mlx *mlx, int len, t_point starting_position);
void draw_wall_ver(t_mlx *mlx, int len, int count, t_point starting_position);
void draw_wall_hor(t_mlx *mlx, int len, int count, t_point starting_position);
void draw_grid(t_mlx *mlx, int len, int count, t_point starting_position);
void circle_octants(int centerX, int centerY, int x, int y, t_mlx *mlx);
void drawcircle(int centerx, int centery, int radius, t_mlx *mlx);
void draw_anyline(t_map *, t_point , t_point);
void    test(t_map *);

#endif
