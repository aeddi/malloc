/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_area.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeddi <aeddi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/18 14:35:32 by aeddi             #+#    #+#             */
/*   Updated: 2014/04/20 19:31:41 by aeddi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>
#include <unistd.h>
#include <sys/mman.h>

static t_bool	init_large_list(t_alloc *map)
{
	int		page_size;

	page_size = getpagesize();
	map->large = (t_llist *)mmap(0, 4 * page_size, PROT_READ | PROT_WRITE,
									MAP_ANON | MAP_PRIVATE, -1, 0);
	if (map->large == (void *)-1)
		return (FALSE);
	map->large->next = NULL;
	map->large->block = NULL;
	return (TRUE);
}

t_bool			init_prealloc_area(t_alloc *map)
{
	int		page_size;
	int		rest;

	map->tn_area_size = (TINY + HEADER) * 100;
	map->sm_area_size = (SMALL + HEADER) * 100;
	page_size = getpagesize();
	if ((rest = map->tn_area_size % page_size) != 0)
		map->tn_area_size = map->tn_area_size - rest + page_size;
	if ((rest = map->sm_area_size % page_size) != 0)
		map->sm_area_size = map->sm_area_size - rest + page_size;
	map->tiny = (t_head *)mmap(0, map->tn_area_size, PROT_READ | PROT_WRITE,
								MAP_ANON | MAP_PRIVATE, -1, 0);
	map->small = (t_head *)mmap(0, map->sm_area_size, PROT_READ | PROT_WRITE,
								MAP_ANON | MAP_PRIVATE, -1, 0);
	if (map->tiny == (void *)-1 || map->small == (void *)-1)
		return (FALSE);
	map->tiny->size = map->tn_area_size - HEADER;
	map->tiny->next = NULL;
	map->tiny->free = TRUE;
	map->small->size = map->sm_area_size - HEADER;
	map->small->next = NULL;
	map->small->free = TRUE;
	if ((map->init = init_large_list(map)))
		return (TRUE);
	return (FALSE);
}
