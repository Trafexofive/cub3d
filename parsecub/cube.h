/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 08:52:41 by mel-houd          #+#    #+#             */
/*   Updated: 2024/04/23 20:57:39 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

#include "./libft/libft.h"

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <stdbool.h>
# include <fcntl.h>
# include <mlx.h>

# define X 600
# define Y 600
# define TITLE "cub3D"

typedef	struct	s_tex_fd
{
	int		NO_fd;
	int		SO_fd;
	int		WE_fd;
	int		EA_fd;
	int		*f_num;
	int		*c_num;
	char	**map;
}				t_tex_fd;

typedef struct s_init_map
{
	char	*NO_tex;
	char	*SO_tex;
	char	*WE_tex;
	char	*EA_tex;
	char	*f_color;
	char	*c_color;
}				t_init_map;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef	struct s_mlx
{
	void	*mlx_srv;
	void	*mlx_win;
}				t_mlx;

//----------parsing headers :
void		print_struct(t_tex_fd *tex);
bool		valid_file(int ac, char *file);
t_list		*fill_map(char *file);
t_init_map	*assign_line(t_list *data, t_init_map *map);
bool		analyse_line(char *tmp);
void		print_err(char *err_msg);
bool		check_tex(t_init_map *map);
char		*replace(char **p_holder, char *set);
void		validate_tex(t_list *head, t_init_map *init_data);
int			*convert_int(char *numb);
bool		help_check(char *part, int mode);
void		check_borders(t_list *map);
t_tex_fd	*open_fd(t_init_map *map_tex);
void		check_open(t_tex_fd *tex);
void		check_map_elements(t_list *map);
int			check_player(t_list *map);
bool		check_spaces_inside(t_list *map);
char		**transfer_map(t_list *map);
t_init_map	*null_init(t_init_map *init_data);
t_tex_fd	*parse(int ac, char **av);

//------------raycasting headers :
t_mlx	*init_mlx(void);
int		key_hook(int keycode, t_mlx *mlx_ptr);
int		close_window(t_mlx *mlx_ptr);
void	init_hooks(t_mlx *mlx_struct);
void	draw_map(char **map, t_mlx *mlx_ptr);

#endif