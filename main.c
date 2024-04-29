
#include "parse/struct.h"
#include <stdio.h>
#include <stdlib.h>

void    render_screen(t_info *info)
{

    void    *window;
/*
** Create a new window.
**
** @param	void *mlx_ptr	the mlx instance pointer;
** @param	int  size_x		the width of the window;
** @param	int  size_y		the height of the window;
** @param	char *title		the title of the window;
** @return	void*			the window instance pointer.
*/
    window = mlx_new_window(info->mlx_ptr, info->win_size_x, info->win_size_y, "hello");
    info->mlx_window = window;
    while (true) {

    }

}

void    *info_init(t_info *info)
{
    info->win_size_x = 100;
    info->win_size_y = 100;

    return NULL;
}

void    entry_point(t_info *info)
{
    info_init(info);
    fprintf(stderr, "%s\n", "break");
    info->mlx_ptr = mlx_init();
    render_screen(info);
}


int main()
{
    t_info  *info;


    info = malloc(sizeof(t_info));
    entry_point(info);

    return 1;
}
