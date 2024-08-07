/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamkadm <mlamkadm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 13:34:41 by mlamkadm          #+#    #+#             */
/*   Updated: 2023/09/15 00:52:47 by mlamkadm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

size_t	ft_strlen_(char *s);
char	*ft_strdup_(char *s);
char	*ft_strjoin_(char *s1, char *s2);
char	*ft_substr_(char *s, unsigned int start, size_t len);
char	*get_next_line(int fd);
int		ft_find_nl(char *s, int c);

#endif
