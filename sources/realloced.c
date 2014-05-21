/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloced.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeddi <aeddi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/20 17:48:30 by aeddi             #+#    #+#             */
/*   Updated: 2014/04/20 19:47:45 by aeddi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

static void	*ft_memcpy(void *s1, const void *s2, size_t n)
{
	char	*s1_bis;
	char	*s2_bis;

	s1_bis = (char *)s1;
	s2_bis = (char *)s2;
	while (n > 0)
	{
		n--;
		s1_bis[n] = s2_bis[n];
	}
	return (s1);
}

void		*realloc_prealloc_area(void *ptr, size_t size)
{
	void	*ret;
	t_head	*verif;

	verif = (t_head *)((char *)ptr - HEADER);
	if (verif && verif->size)
	{
		ret = malloc(size);
		if (ret)
		{
			ret = ft_memcpy(ret, ptr, verif->size);
			free(ptr);
		}
	}
	return (NULL);
}

void		*realloc_large_area(void *ptr, size_t size)
{
	void	*ret;
	t_head	*verif;

	verif = (t_head *)((char *)ptr - HEADER);
	if (verif && verif->size)
	{
		ret = malloc(size);
		if (ret)
		{
			ret = ft_memcpy(ret, ptr, verif->size);
			free(ptr);
		}
	}
	return (NULL);
}
