/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 17:44:26 by mel-houd          #+#    #+#             */
/*   Updated: 2024/08/01 20:26:17 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	polish_list(t_list **list)
{
	t_list	*last_node;
	t_list	*clean_node;
	int		i;
	int		k;
	char	*buf;

	buf = (char *)gb_malloc((BUFFER_SIZE + 1) * sizeof(char), 0);
	clean_node = (t_list *)gb_malloc(sizeof(t_list), 0);
	if (!buf || !clean_node)
		return ;
	last_node = find_last_node(*list);
	i = 0;
	k = 0;
	while (last_node->str_buf[i] && last_node->str_buf[i] != '\n')
		i++;
	while (last_node->str_buf[i] && last_node->str_buf[++i])
		buf[k++] = last_node->str_buf[i];
	buf[k] = '\0';
	clean_node->str_buf = buf;
	clean_node->next = NULL;
	dealloc(list, clean_node, buf);
}

char	*get_line_str(t_list *list)
{
	int		str_len;
	char	*next_str;

	if (!list)
		return (NULL);
	str_len = len_to_newline(list);
	next_str = (char *)gb_malloc(str_len + 1, 0);
	if (!next_str)
		return (NULL);
	copy_str(list, next_str);
	return (next_str);
}

void	append(t_list **list, char *buf)
{
	t_list	*new_node;
	t_list	*last_node;

	if (!list)
		return ;
	last_node = find_last_node(*list);
	new_node = (t_list *)gb_malloc(sizeof(t_list), 0);
	if (!new_node)
		return ;
	if (!last_node)
		*list = new_node;
	else
		last_node->next = new_node;
	new_node->str_buf = buf;
	new_node->next = NULL;
}

void	create_list(t_list **list, int fd)
{
	int		char_read;	
	char	*buf;

	while (!found_newline(*list))
	{
		buf = (char *)gb_malloc((BUFFER_SIZE + 1) * sizeof(char), 0);
		if (!buf)
			return ;
		char_read = read(fd, buf, BUFFER_SIZE);
		if (char_read == 0)
		{
			free(buf);
			buf = NULL;
			return ;
		}
		buf[char_read] = '\0';
		append(list, buf);
	}
}

char	*get_next_line(int fd)
{
	static t_list	*list = NULL;
	char			*next_line;
	t_list			*tmp;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		while (list)
		{
			tmp = list->next;
			free(list->str_buf);
			free(list);
			list = tmp;
		}
		list = NULL;
		return (NULL);
	}
	create_list(&list, fd);
	if (!list)
		return (NULL);
	next_line = get_line_str(list);
	polish_list(&list);
	return (next_line);
}
