/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeddi <aeddi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/18 16:31:52 by aeddi             #+#    #+#             */
/*   Updated: 2014/04/20 20:43:48 by aeddi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <malloc.h>

void	ft_putstr_fd(char *str, int fd)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	write(fd, str, i);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(long long int nbr, int fd)
{
	if (nbr < 0)
	{
		nbr *= -1;
		ft_putchar_fd('-', fd);
	}
	if (nbr >= 10)
	{
		ft_putnbr_fd(nbr / 10, fd);
		ft_putnbr_fd(nbr % 10, fd);
	}
	else
		ft_putchar_fd(nbr + '0', fd);
}

void	print_byte_to_hex(unsigned char byte)
{
	char	str[2];
	short	count;
	short	char_hex;

	count = -1;
	while (++count != 2)
	{
		char_hex = byte % 16;
		byte /= 16;
		if (char_hex < 10)
			str[count] = char_hex + '0';
		else
			str[count] = (char_hex % 10) + 'A';
	}
	ft_putchar_fd(str[1], 1);
	ft_putchar_fd(str[0], 1);
}

void	print_ptr_to_hex(size_t ptr, t_bool prefix, t_bool full)
{
	char	str[16];
	short	count;
	short	char_hex;

	count = -1;
	while (++count != 16)
	{
		char_hex = ptr % 16;
		ptr /= 16;
		if (char_hex < 10)
			str[count] = char_hex + '0';
		else
			str[count] = (char_hex % 10) + 'A';
	}
	count -= 5;
	if (prefix)
		ft_putstr_fd("0x", 1);
	if (!full)
		while (str[count] == '0')
			count--;
	while (count >= 0)
	{
		ft_putchar_fd(str[count], 1);
		count--;
	}
}
