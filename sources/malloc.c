/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeddi <aeddi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/18 16:35:56 by aeddi             #+#    #+#             */
/*   Updated: 2014/04/20 19:54:30 by aeddi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>
#include <unistd.h>
#include <sys/mman.h>

static void	*lock_prealloc_block(t_head *block, size_t size)
{
	t_head	*rest;

	rest = (t_head *)((char *)block + HEADER + size);
	rest->size = block->size - (HEADER + size);
	rest->next = block->next;
	rest->free = TRUE;
	block->next = rest;
	block->size = size;
	block->free = FALSE;
	return ((char *)block + HEADER);
}

static void	*defrag_prealloc_area(t_head *first, t_head *next, size_t size)
{
	t_head	*rest;

	rest = (t_head *)((char *)first + HEADER + size);
	rest->size = (char *)next - ((char *)rest + HEADER);
	rest->next = next;
	rest->free = TRUE;
	first->next = rest;
	first->size = size;
	first->free = FALSE;
	return ((char *)first + HEADER);
}

void		*fill_prealloc_area(t_head *area, size_t size)
{
	t_head	*frag_h;
	size_t	frag_s;

	frag_s = 0;
	frag_h = NULL;
	while (area)
	{
		if (area->free)
		{
			if (!frag_h)
				frag_h = area;
			frag_s += area->size + HEADER;
			if (frag_s >= size + (HEADER * 2) && frag_h != area)
				return (defrag_prealloc_area(frag_h, area->next, size));
			else if (area->size >= size + HEADER)
				return (lock_prealloc_block(area, size));
		}
		else
		{
			frag_s = 0;
			frag_h = NULL;
		}
		area = area->next;
	}
	return (NULL);
}

void		*alloc_undef_area(t_llist *head, size_t size)
{
	int		page_size;
	int		rest;
	size_t	area_size;
	t_head	*block;
	t_llist	*tmp;

	page_size = getpagesize();
	area_size = size + HEADER;
	if ((rest = area_size % page_size) != 0)
		area_size = area_size - rest + page_size;
	block = (t_head *)mmap(0, area_size, PROT_READ | PROT_WRITE,
								MAP_ANON | MAP_PRIVATE, -1, 0);
	if (block == (void *)-1)
		return (NULL);
	tmp = head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = (t_llist *)((char *)tmp + sizeof(t_llist));
	tmp->next->next = NULL;
	tmp->next->block = block;
	tmp->next->size = area_size;
	block->size = size;
	block->next = (t_head *)((char *)block + area_size);
	block->free = FALSE;
	return ((char *)block + HEADER);
}
