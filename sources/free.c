/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeddi <aeddi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/18 16:31:52 by aeddi             #+#    #+#             */
/*   Updated: 2014/04/20 19:46:08 by aeddi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>
#include <unistd.h>
#include <sys/mman.h>

t_bool	free_prealloc_area(void *ptr, t_head *first)
{
	t_head	*block;
	t_bool	freed;

	block = first;
	freed = FALSE;
	while (block)
	{
		if ((char *)block + HEADER == ptr)
		{
			block->free = TRUE;
			freed = TRUE;
			break ;
		}
		block = block->next;
	}
	return (freed);
}

t_bool	free_large_area(void *ptr, t_llist *first)
{
	t_head	*block;
	t_llist	*index;
	t_bool	freed;

	freed = FALSE;
	index = first;
	while (index)
	{
		block = index->block;
		if (block == (t_head *)((char *)ptr - HEADER))
		{
			if (!(munmap(block, index->size)))
				freed = TRUE;
			index->block = NULL;
			break ;
		}
		index = index->next;
	}
	return (freed);
}
