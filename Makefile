# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbarrier <fbarrier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/02 06:23:52 by fbarrier          #+#    #+#              #
#    Updated: 2022/02/09 14:57:15 by fbarrier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SOURCES =	main.c \
			philosophers_utils.c \
			philosophers_utils2.c \
			init.c \
			forks.c \
			display.c \
			error.c

OBJS = $(SOURCES:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I. -fsanitize=thread
LIBNAME = philosophers.a
NAME = philo
HEADER = philosophers.h

# make -C -Idir Include ?

.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all: $(NAME)

$(NAME): $(OBJS)
		${CC} ${CFLAGS} -o $(NAME) $(OBJS) -pthread -g

clean:
	rm -f $(OBJS)
	
fclean: clean
	rm -f $(NAME) 

re: fclean all

.PHONY: all clean fclean re
