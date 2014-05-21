# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aeddi <aeddi@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/12/14 16:00:35 by aeddi             #+#    #+#              #
#    Updated: 2014/04/20 20:07:42 by aeddi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif
TEST			?=	0
ifeq ($(TEST), 1)
	NAME		=	test
else
	NAME		=	libft_malloc_$(HOSTTYPE).so
endif
SYMLINK			=	libft_malloc.so
CC				=	gcc
CFLAGS			=	-Wall -Wextra -Werror -pedantic -I $(INCS_DIR)
LFLAGS			=	-shared
INCS_DIR		=	./includes
OBJS_DIR		=	./objects
SRCS_DIR		=	./sources
OBJS			=	$(patsubst %.c, $(OBJS_DIR)/%.o, $(SRCS))
ifeq ($(TEST), 1)
	SRCS		=	calloc.c		\
					free.c			\
					init_area.c		\
					main.c			\
					malloc.c		\
					print_data.c	\
					realloced.c		\
					show_alloc.c	\
					test.c
else
	SRCS		=	calloc.c		\
					free.c			\
					init_area.c		\
					main.c			\
					malloc.c		\
					print_data.c	\
					realloced.c		\
					show_alloc.c
endif

all				:	$(NAME)

$(NAME)			:	$(OBJS_DIR) $(OBJS)
ifeq ($(TEST), 1)
	$(CC) -o $(NAME) $(OBJS)
else
	$(CC) $(LFLAGS) -o $(NAME) $(OBJS)
	@ln -s $(NAME) $(SYMLINK)
endif

$(OBJS_DIR)/%.o	:	$(addprefix $(SRCS_DIR)/, %.c)
	$(CC) $(CFLAGS) -o $@ -c $^

$(OBJS_DIR)		:
	@mkdir -p $(OBJS_DIR)

fclean			:	clean
	rm -f $(NAME) $(SYMLINK)

clean			:
	rm -rf $(OBJS_DIR)

re				:	fclean all

.PHONY: clean all re fclean
