/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeddi <aeddi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/18 14:35:32 by aeddi             #+#    #+#             */
/*   Updated: 2014/04/20 19:46:19 by aeddi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <unistd.h>
# define TINY	256
# define SMALL	4096
# define HEADER	sizeof(t_head)

typedef enum		e_bool
{
	FALSE,
	TRUE
}					t_bool;

typedef struct		s_head
{
	short			free;
	struct s_head	*next;
	size_t			size;
}					t_head;

typedef struct		s_llist
{
	struct s_llist	*next;
	t_head			*block;
	size_t			size;
}					t_llist;

typedef struct		s_alloc
{
	t_bool			init;
	t_head			*tiny;
	t_head			*small;
	t_llist			*large;
	size_t			tn_area_size;
	size_t			sm_area_size;
}					t_alloc;

/*
** Main functions
*/
void				*malloc(size_t size);
void				*calloc(size_t nmemb, size_t size);
void				*realloc(void *ptr, size_t size);
void				free(void *ptr);

/*
** Aux. functions for malloc
*/
t_bool				init_prealloc_area(t_alloc *map);
void				*fill_prealloc_area(t_head *area, size_t size);
void				*alloc_undef_area(t_llist *head, size_t size);

/*
** Aux. functions for free
*/
t_bool				free_prealloc_area(void *ptr, t_head *first);
t_bool				free_large_area(void *ptr, t_llist *first);

/*
** Aux. functions for realloc
*/
void				*realloc_prealloc_area(void *ptr, size_t size);
void				*realloc_large_area(void *ptr, size_t size);

/*
** Show alloc functions
*/
void				show_alloc_mem(void);
void				show_alloc_mem_ex(void);
void				print_hex_dump(void *start, void *end);
size_t				print_large_area(t_llist *block, t_bool verbose);
size_t				print_adress_area(t_head *area, char *name, t_bool verbose);

/*
** Print data functions
*/
void				ft_putstr_fd(char *str, int fd);
void				ft_putchar_fd(char c, int fd);
void				ft_putnbr_fd(long long int nbr, int fd);
void				print_ptr_to_hex(size_t ptr, t_bool prefix, t_bool full);
void				print_byte_to_hex(unsigned char byte);

#endif
