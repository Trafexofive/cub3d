/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:52:27 by mel-houd          #+#    #+#             */
/*   Updated: 2024/04/23 21:48:58 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	close_window(t_mlx *mlx_ptr)
{
	mlx_destroy_window(mlx_ptr->mlx_srv, mlx_ptr->mlx_win);
	exit(0);
}

int	key_hook(int keycode, t_mlx *mlx_ptr)
{
	if (keycode == 53)
		close_window(mlx_ptr);
	return (0);
}

t_mlx	*init_mlx(void)
{
	t_mlx	*mlx_struct;

	mlx_struct = gb_malloc(sizeof(t_mlx), 0);
	mlx_struct->mlx_srv = mlx_init();
	mlx_struct->mlx_win = mlx_new_window(mlx_struct->mlx_srv, X, Y, TITLE);
	if (!mlx_struct->mlx_srv || !mlx_struct->mlx_win)
	{
		print_err("Error\nmlx init error\n");
		exit(1);
	}
	return (mlx_struct);
}

void	init_hooks(t_mlx *mlx_struct)
{
	mlx_key_hook(mlx_struct->mlx_win, &key_hook, mlx_struct);
	mlx_hook(mlx_struct->mlx_win, 17, 0, &close_window, mlx_struct);
}

void	draw_line(int *x, int y, t_mlx *mlx_ptr)
{
	int m = X / 25;
	int	old_x = *x;
	int	x_value = *x;
	while (x_value < X && old_x < x_value + m)
	{
		mlx_pixel_put(mlx_ptr->mlx_srv, mlx_ptr->mlx_win, x_value, y, 16755251);	
		x_value++;
	}
	*x = x_value;
}

void	draw_map(char **map, t_mlx *mlx_ptr)
{
	int	x;
	int	y;
	int	d = Y / 14;

	y = 0;
	while (y < Y)
	{
		x = 0;
		while (x < X && y % d != 0)
		{
			draw_line(&x, y, mlx_ptr);
		}
		y++;
	}
}