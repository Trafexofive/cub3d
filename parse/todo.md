



### parse idea dump:

----------------------

## Struct ideas;

```
enum for compasse dirs
typedef struct s_grid
{
  t_point *coordinate/tile;
  t_info  *tile_info;
  
}

typedef struct s_template
{
  char *relevent_info;
  t_walldir *direction
}

typedef struct s_info
{
  t_emplate *info;
}

```
## map structure

-- 0 and 1 for walls, W, N, E, S respectivly for the player spawn direction and location
