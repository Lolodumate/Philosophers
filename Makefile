# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: laroges <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/18 16:16:20 by laroges           #+#    #+#              #
#    Updated: 2024/02/15 12:33:30 by laroges          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =	main.c \
	init.c \
	clean.c \
	philosophers.c \
	utils.c \
	tasks.c \
	time.c \
	ft_args.c \
	mem_alloc.c \
	ft_utils.c \
	meals.c \

CC = gcc

CFLAGS = -Wall -Werror -Wextra -g

THREADFLAG = -lpthread

OBJ = $(SRC:.c=.o)

NAME = ./philo

all: $(NAME)

%.o : %.c philosophers.h
	$(CC) $(CFLAGS) -c $< -o $(<:.c<=.o)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(THREADFLAG)

clean:
	rm -f $(OBJ) 

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY : all clean fclean re
