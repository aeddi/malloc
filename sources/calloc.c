/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeddi <aeddi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/20 17:04:11 by aeddi             #+#    #+#             */
/*   Updated: 2014/04/20 19:18:19 by aeddi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

void	*calloc(size_t nmemb, size_t size)
{
	void	*ret;
	char	*clean;
	size_t	total;

	total = nmemb * size;
	ret = malloc(total);
	if (ret)
	{
		clean = (char *)ret;
		while (total)
		{
			clean[total - 1] = '\0';
			total--;
		}
	}
	return (ret);
}
