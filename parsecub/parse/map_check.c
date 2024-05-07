/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 00:56:07 by mel-houd          #+#    #+#             */
/*   Updated: 2024/04/23 18:35:29 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	validate_tex(t_list *head, t_init_map *init_data)
{
	if (assign_line(head, init_data) == NULL)
	{
		print_err("Error\ntexture parsing error 1\n");
		exit(1);
	}
	if (check_tex(init_data) == false)
	{
		print_err("Error\ntexture parsing error 2\n");
		exit(1);
	}
}

void	check_open(t_tex_fd *tex)
{
	// if (tex->EA_fd == -1 || tex->NO_fd == -1 || tex->SO_fd == -1 || tex->WE_fd == -1)
	// {
	// 	print_err("Error\nopening textures error\n");
	// 	// exit(0);
	// }
}

t_tex_fd	*open_fd(t_init_map *map_tex)
{
	t_tex_fd	*refined_map;

	refined_map = gb_malloc(sizeof(t_tex_fd), 0);
	if (!refined_map)
	{
		print_err("Error\nmalloc error\n");
		exit(1);
	}
	refined_map->EA_fd = open(map_tex->EA_tex, O_RDONLY, 644);
	refined_map->SO_fd = open(map_tex->SO_tex, O_RDONLY, 644);
	refined_map->NO_fd = open(map_tex->NO_tex, O_RDONLY, 644);
	refined_map->WE_fd = open(map_tex->WE_tex, O_RDONLY, 644);
	check_open(refined_map);
	refined_map->f_num = convert_int(map_tex->f_color);
	refined_map->c_num = convert_int(map_tex->c_color);
	return (refined_map);
}

bool	help_check(char *part, int mode)
{
	int	i;

	i = 0;
	if (mode == 0)
	{
		while (part[i] == ' ')
			i++;
		while (part[i])
		{
			if (part[i] != '1')
				return (false);
			i++;
		}
	}
	else if (mode == 1)
	{
		if (part[0] != '1' || part[ft_strlen(part) - 1] != '1')
			return (false);
	}
	
	return (true);
}

void	check_borders(t_list *map)
{
	bool	first;

	first  =true;
	while (map && map->content)
	{
		if (first || map->next == NULL)
		{
			if (!help_check(map->content, 0))
			{
				print_err("Error\ninvalid map\n");
				exit(1);
			}
			first = false;
		}
		else
		{
			if (!help_check(map->content, 1))
			{
				print_err("Error\ninvalid map\n");
				exit(1);
			}
		}
		map = map->next;
	}
}

bool	check_char(char *tmp)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		if (tmp[i] != ' '
			&& tmp[i] != '0'
			&& tmp[i] != '1'
			&& tmp[i] != 'N'
			&& tmp[i] != 'S'
			&& tmp[i] != 'W'
			&& tmp[i] != 'E')
		{	
			return (false);
		}
		i++;
	}
	return (true);
}

int	check_player(t_list *map)
{
	int		player;
	char	*tmp;
	int		i;

	player = -1;
	i = 0;
	while (map && map->content)
	{
		i = 0;
		tmp = map->content;
		while (tmp[i])
		{
			if (tmp[i] == 'S'
				|| tmp[i] == 'N'
				|| tmp[i] == 'W'
				|| tmp[i] == 'E')
			{
				player = -player;
			}
			i++;
		}
		map = map->next;
	}
	return (player);
}


bool	check_spaces_inside(t_list *map)
{
	char	**map_char;
	int		i;
	int		j;

	i = 0;
	map_char = gb_malloc(sizeof(char *) * ft_lstsize(map) + 1, 0);
	while (map && map->content)
	{
		map_char[i] = map->content;
		i++;
		map = map->next;
	}
	map_char[i] = NULL;
	i = 0;
	while (map_char[i])
	{
		j = 0;
		while (map_char[i][j])
		{
			if (map_char[i][j] == ' ')
			{
				if ((j != 0 && map_char[i][j - 1] != '1' && map_char[i][j - 1] != ' ')
					|| (j != ft_strlen(map_char[i]) - 1 && map_char[i][j + 1] != '1' && map_char[i][j + 1] != ' ')
					|| (i != 0 && map_char[i - 1][j] != '1' && map_char[i - 1][j] != ' ')
					|| (i != ft_lstsize(map) - 1 && map_char[i + 1][j] != '1' && map_char[i + 1][j] != ' '))
				{
					return (false);
				}
			}
			j++;
		}
		i++;
	}
	return (true);
}

void	check_map_elements(t_list *map)
{
	int		i;
	char	*tmp;

	i = 0;
	if (check_player(map) == -1)
	{
		print_err("Error\nno or too many players in map\n");
		exit(1);
	}
	if (check_spaces_inside(map) == false)
	{
		print_err("Error\nspaces error\n");
		exit(1);
	}
	while (map && map->content)
	{
		i = 0;
		tmp = map->content;
		if (check_char(tmp) == false)
		{
			print_err("Error\nunknown charater in map\n");
			exit(1);
		}
		map = map->next;
	}
}

char	**transfer_map(t_list *map)
{
	char	**map_char;
	int		i;

	map_char = gb_malloc(sizeof(char *) * ft_lstsize(map) + 1, 0);
	if (!map_char)
	{
		print_err("Error\nerror malloc\n");
		exit(1);
	}
	i = 0;
	while (map && map->content)
	{
		map_char[i] = map->content;
		i++;
		map = map->next;
	}
	map_char[i] = NULL;
	return (map_char);
}
