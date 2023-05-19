# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juhyulee <juhyulee@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/09 18:18:19 by juhyulee          #+#    #+#              #
#    Updated: 2023/05/15 15:42:43 by juhyulee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =  \
		main.c\
		util0.c\
		util1.c\
		util2.c\
		philo_run.c\
		moniter.c

OBJS = $(SRCS:.c=.o)

HEADER = -I./philo.h
NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror #-g -fsanitize=address
RM = rm -f

all : 		$(NAME)

$(NAME) :	$(OBJS)
			@printf "🍎 compiled OBJS\n"
			@$(CC) $(CFLAGS) -o $(NAME) $(HEADER) $(OBJS)
			@printf "🥳 compiled $(NAME)\n"

%.o : %.c
			@$(CC) $(CFLAGS) $(HEADER) -c $< -o $@

clean :
			@$(RM) $(OBJS)
			@printf "🗑 cleaned\n"

fclean :	clean
			@$(RM) $(NAME)
			@printf "🧽 fcleaned\n"

re :		fclean all

.PHONY : all clean fclean re
