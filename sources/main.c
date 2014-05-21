/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeddi <aeddi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/20 19:16:49 by aeddi             #+#    #+#             */
/*   Updated: 2014/04/20 20:42:08 by aeddi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>
#include <unistd.h>

static t_alloc g_map = { FALSE, NULL, NULL, NULL, 0, 0 };

void	*malloc(size_t size)
{
	void	*ret;

	ret = NULL;
	if (size)
	{
		if (!g_map.init && !init_prealloc_area(&g_map))
			return (NULL);
		if (size <= TINY)
			ret = fill_prealloc_area(g_map.tiny, size);
		else if (size <= SMALL)
			ret = fill_prealloc_area(g_map.small, size);
		if (!ret)
			ret = alloc_undef_area(g_map.large, size);
	}
	return (ret);
}

void	*realloc(void *ptr, size_t size)
{
	void	*ret;

	ret = NULL;
	if (!size)
		free(ptr);
	else if (!ptr)
		return (malloc(size));
	else
	{
		if (size <= SMALL)
			ret = realloc_prealloc_area(ptr, size);
		else if (!ret)
			ret = realloc_large_area(ptr, size);
	}
	return (NULL);
}

void	free(void *ptr)
{
	t_bool	freed;

	freed = FALSE;
	if (ptr)
	{
		if (!g_map.init)
			ft_putstr_fd("No g_mapped memory\n", 2);
		if (ptr > (void *)g_map.tiny
			&& ptr < (void *)((char *)g_map.tiny + g_map.tn_area_size))
			freed = free_prealloc_area(ptr, g_map.tiny);
		else if (ptr > (void *)g_map.small
				&& ptr < (void *)((char *)g_map.small + g_map.sm_area_size))
			freed = free_prealloc_area(ptr, g_map.small);
		else
			freed = free_large_area(ptr, g_map.large);
	}
}

void	show_alloc_mem(void)
{
	short	first;
	size_t	total;
	t_llist	*tmp;

	first = 1;
	tmp = g_map.large;
	total = print_adress_area(g_map.tiny, "TINY : ", FALSE);
	total += print_adress_area(g_map.small, "SMALL : ", FALSE);
	while (tmp)
	{
		if (tmp->block)
		{
			if (first && !(first = 0))
			{
				ft_putstr_fd("LARGE : ", 1);
				print_ptr_to_hex((size_t)tmp->block, TRUE, FALSE);
				ft_putchar_fd('\n', 1);
			}
			total += print_large_area(tmp, FALSE);
		}
		tmp = tmp->next;
	}
	ft_putstr_fd("Total : ", 1);
	ft_putnbr_fd(total, 1);
	ft_putstr_fd(" octets\n", 1);
}

void	show_alloc_mem_ex(void)
{
	short	first;
	size_t	total;
	t_llist	*tmp;

	first = 1;
	tmp = g_map.large;
	total = print_adress_area(g_map.tiny, "TINY : ", TRUE);
	total += print_adress_area(g_map.small, "SMALL : ", TRUE);
	while (tmp)
	{
		if (tmp->block)
		{
			if (first && !(first = 0))
			{
				ft_putstr_fd("LARGE : ", 1);
				print_ptr_to_hex((size_t)tmp->block, TRUE, FALSE);
				ft_putchar_fd('\n', 1);
			}
			total += print_large_area(tmp, TRUE);
		}
		tmp = tmp->next;
	}
	ft_putstr_fd("Total : ", 1);
	ft_putnbr_fd(total, 1);
	ft_putstr_fd(" octets\n", 1);
}
