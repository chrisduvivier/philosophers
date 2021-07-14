# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cduvivie <cduvivie@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/26 01:08:07 by cduvivie          #+#    #+#              #
#    Updated: 2021/07/12 16:22:38 by cduvivie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= philo

CC 			:=	gcc
CFLAGS	 	:=	-Wall -Wextra -Werror -g
RM 			:=	/bin/rm -f

INCLUDE 	:= 	-Iinclude/

SRCS		:=	./srcs/main.c \
				./srcs/utilities_1.c \
				./srcs/input_parser.c \
				./srcs/struct_init.c \
				./srcs/philo_status.c \
				./srcs/check_status.c \
				./srcs/time_helper.c \
				./srcs/debug.c \

OBJ			:=	$(SRCS:%.c=%.o)

all			:	$(NAME)

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDE)

$(NAME)		:	$(OBJ)
	@ $(CC) $(CFLAGS) $(INCLUDE) $(SRCS) -o $(NAME) -pthread

clean		:
	@ $(RM) $(OBJ)

fclean		:	clean
	@ $(RM) $(NAME)

re			: fclean all

.PHONY		: all clean fclean
