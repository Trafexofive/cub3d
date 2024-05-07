/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:36:20 by mel-houd          #+#    #+#             */
/*   Updated: 2024/04/23 20:57:59 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	main(int ac, char **av)
{
	t_tex_fd	*full_map;
	t_mlx		*mlx_struct;

	full_map = parse(ac, av);
	mlx_struct = init_mlx();

	draw_map(full_map->map, mlx_struct);

	//--------------------------
	init_hooks(mlx_struct);
	if (mlx_loop(mlx_struct->mlx_srv) != 0)
	{
		print_err("Error\nmlx error\n");
		exit(1);
	}
	return (0);
}