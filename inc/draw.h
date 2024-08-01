
#ifndef DRAW_H
#define DRAW_H

#include "struct.h"
#include <mlx.h>
#include <stdio.h>


//###########################################################################
// Drawing functions

void clear_window(t_mlx *mlx);
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
void    put_pixel(t_img *img, t_point pixel, int color);


//##########################################################################
// Vector arithmetic


int vector_len(t_point vector);
t_point subtract_vector(t_point start, t_point end);
t_point add_vector(t_point start, t_point end);



#endif
