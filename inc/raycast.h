#ifndef RAYCAST_H
#define RAYCAST_H

#include <math.h>
#include <mlx.h>
#include "struct.h"
#include "utils.h"
#include <fcntl.h>
#include <stdio.h>


void    renderer(t_map *map);
t_map   load_map_data(t_map *map);
void    clear_window(t_info *info);



#endif
