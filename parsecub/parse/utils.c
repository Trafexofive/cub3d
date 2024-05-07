/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 23:59:20 by mel-houd          #+#    #+#             */
/*   Updated: 2024/04/23 18:35:43 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	print_struct(t_tex_fd *tex)
{
	char	**map;
	int		i;

	printf("%d\n", tex->EA_fd);
	printf("%d\n", tex->WE_fd);
	printf("%d\n", tex->SO_fd);
	printf("%d\n", tex->EA_fd);
	printf("[%d %d %d]\n", tex->c_num[0], tex->c_num[1], tex->c_num[2]);
	printf("[%d %d %d]\n", tex->f_num[0], tex->f_num[1], tex->f_num[2]);
	map = tex->map;
	i = 0;
	while (map && map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
}

void	print_err(char *err_msg)
{
	write(2, err_msg, ft_strlen(err_msg));
}

bool	analyse_line(char *tmp)
{
	if (tmp[0] == '\n' && tmp[1] == '\0')
		return (false);
	return (true);
}

char	*replace(char **p_holder, char *set)
{
	char	*tmp;

	tmp = ft_strtrim(*p_holder, set);
	return (tmp);
}

bool check_tex(t_init_map *map)
{
    if (!map->c_color
        || !map->f_color
        || !map->EA_tex
        || !map->NO_tex
        || !map->SO_tex
        || !map->WE_tex)
    {
        return (false);
    }
    map->c_color = replace(&map->c_color, "C \n");
    map->f_color = replace(&map->f_color, "F \n");
    map->EA_tex = replace(&map->EA_tex, "EA \n");
    map->SO_tex = replace(&map->SO_tex, "SO \n");
    map->NO_tex = replace(&map->NO_tex, "NO \n");
    map->WE_tex = replace(&map->WE_tex, "WE \n");
    return (true);
}

void	free_int_convert(char **split)
{
	print_err("Error\ncolor value is not in [0 - 255] range\n");
	exit(1);
}

int	*convert_int(char *numb)
{
	char	**split;
	int		*arr;
	int		i;

	arr = gb_malloc(sizeof(int) * 3, 0);
	split = ft_split(numb, " ,");
	if (!arr || !split)
		exit(1);
	i = 0;
	while (i < 3)
	{
		if (ft_strlen(split[i]) > 3)
			free_int_convert(split);
		arr[i] = ft_atoi(split[i]);
		if (arr[i] < 0 || arr[i] > 255)
			free_int_convert(split);
		i++;
	}
	return (arr);
}
