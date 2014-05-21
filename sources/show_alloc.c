/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeddi <aeddi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/18 16:31:52 by aeddi             #+#    #+#             */
/*   Updated: 2014/04/20 20:40:59 by aeddi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>
#include <unistd.h>

void		print_hex_dump(void *start, void *end)
{
	short	count;

	ft_putstr_fd("Hex dump :\n", 1);
	while (start != end)
	{
		count = 0;
		print_ptr_to_hex((size_t)start, FALSE, TRUE);
		ft_putchar_fd(' ', 1);
		while (count++ != 16)
		{
			print_byte_to_hex(*(unsigned char *)start);
			start = (char *)start + 1;
			if (start == end)
				break ;
			if (count != 16 && count % 2 == 0)
				ft_putchar_fd(' ', 1);
		}
		ft_putchar_fd('\n', 1);
	}
}

size_t		print_adress_area(t_head *area, char *name, t_bool verbose)
{
	size_t	total;

	total = 0;
	ft_putstr_fd(name, 1);
	print_ptr_to_hex((size_t)area, TRUE, FALSE);
	ft_putchar_fd('\n', 1);
	while (area->next)
	{
		if (!area->free)
		{
			print_ptr_to_hex((size_t)((char *)area + HEADER), TRUE, FALSE);
			ft_putstr_fd(" - ", 1);
			print_ptr_to_hex((size_t)((char *)area + HEADER + area->size),
										TRUE, FALSE);
			ft_putstr_fd(" : ", 1);
			ft_putnbr_fd(area->size, 1);
			ft_putstr_fd(" octets\n", 1);
			if (verbose)
				print_hex_dump((char *)area + HEADER,
								(char *)area + HEADER + area->size);
			total += area->size;
		}
		area = area->next;
	}
	return (total);
}

size_t		print_large_area(t_llist *block, t_bool verbose)
{
	t_head	*header;

	header = block->block;
	print_ptr_to_hex((size_t)((char *)header + HEADER), TRUE, FALSE);
	ft_putstr_fd(" - ", 1);
	print_ptr_to_hex((size_t)((char *)header + HEADER + header->size),
								TRUE, FALSE);
	ft_putstr_fd(" : ", 1);
	ft_putnbr_fd(header->size, 1);
	ft_putstr_fd(" octets\n", 1);
	if (verbose)
	{
		ft_putstr_fd("Hex dump :\n", 1);
		print_hex_dump((char *)header + HEADER,
						(char *)header + HEADER + header->size);
	}
	return (header->size);
}
