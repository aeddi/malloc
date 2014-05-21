/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeddi <aeddi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/20 16:16:26 by aeddi             #+#    #+#             */
/*   Updated: 2014/04/20 20:32:56 by aeddi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>
#include <unistd.h>

static char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static void	ft_putstr(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	write(1, str, i);
}

int			main(void)
{
	char	*ptr1;
	char	*ptr2;
	char	*ptr3;
	char	*ptr4;

	ptr1 = malloc(123);
	ft_strcpy(ptr1, "This is a sample text just for the demo of hex dump !");
	ft_putstr("\n1 pointer for demo of hex dump :\n\n");
	show_alloc_mem_ex();
	ptr2 = malloc(223);
	ptr3 = malloc(2323);
	ptr4 = malloc(4323);
	ft_putstr("\n4 pointers before free :\n\n");
	show_alloc_mem();
	free(ptr1);
	free(ptr2);
	free(ptr3);
	free(ptr4);
	ft_putstr("\n4 pointers after free :\n\n");
	show_alloc_mem();
	return (0);
}
