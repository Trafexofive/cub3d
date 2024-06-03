#ifndef RAYCAST_H
#define RAYCAST_H

#include <math.h>
#include <mlx.h>
#include "struct.h"
#include "utils.h"
#include <fcntl.h>
#include <stdio.h>


void player_move_w(t_map *map);
void player_move_s(t_map *map);
void player_move_a(t_map *map);
void player_move_d(t_map *map);
void    renderer(t_map *map);
t_map   load_map_data(t_map *map);
void    clear_window(t_info *info);
void    raycaster(t_map *map);

#endif
