# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cduvivie <cduvivie@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/26 01:08:07 by cduvivie          #+#    #+#              #
#    Updated: 2021/06/26 01:14:32 by cduvivie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= philo

CC 			:=	gcc
CFLAGS	 	:=	-Wall -Wextra -Werror -g
RM 			:=	/bin/rm -f

INCLUDE 	:= 	-Iinclude/

SRCS		:=	main.c \

OBJ			:=	$(SRCS:%.c=%.o)

all			:	$(NAME)

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDE)

$(NAME)		:	$(OBJ)
	@ $(CC) $(CFLAGS) $(INCLUDE) $(SRCS) -o $(NAME) -pthread

clean		:
	@ $(RM) $(OBJ)
	@ $(MAKE) -C clean

fclean		:	clean
	@ $(RM) $(NAME)
	@ $(MAKE) -C fclean

re			: fclean all

.PHONY		: all clean fclean
