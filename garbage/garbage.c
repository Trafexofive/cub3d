/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamkadm <mlamkadm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 09:27:22 by mlamkadm          #+#    #+#             */
/*   Updated: 2024/02/09 22:38:55 by mlamkadm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/garbage.h"
#include "../lib/libft/libft.h"

void	*chad_alloc(size_t size, int quantity, t_alloc *address)
{
	void	*alloc_ptr;
	t_alloc	*iter;
	t_alloc	*new_alloc_node;

	iter = address;
	alloc_ptr = ft_calloc(size, quantity);
	if (!alloc_ptr)
		return (NULL);
	while (iter->next != NULL)
	{
		iter = iter->next;
	}
	new_alloc_node = ft_calloc(1, sizeof(t_alloc));
	new_alloc_node->alloc_node = new_alloc_node;
	iter->next = new_alloc_node;
	new_alloc_node->address = alloc_ptr;
	new_alloc_node->next = NULL;
	return (alloc_ptr);
}

void	chad_free(t_alloc *head)
{
	t_alloc	*tmp;

	while (head->next != NULL)
	{
		tmp = head;
		head = head->next;
		if (tmp->address)
		{
			free(tmp->address);
			free(tmp->alloc_node);
		}
	}
	free(head->address);
	free(head->alloc_node);
}
