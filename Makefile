# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hugo-mar <hugo-mar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/29 14:39:20 by hugo-mar          #+#    #+#              #
#    Updated: 2024/09/23 14:31:38 by hugo-mar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
ARCHIVE = pipex.a
CC = cc
CFLAGS = -Wall -Werror -Wextra
MAKE_LIB = ar -rcs

SRCS = childlabor.c pipecreate.c pipex.c tasks1.c twistft.c \
		libft.c pathsrch.c pipesetup.c tasks2.c twistsplit.c

BONUS_SRCS = childlabor.c pipecreate.c pipex_bonus.c tasks1.c twistft.c \
		libft.c pathsrch.c pipesetup.c tasks2.c twistsplit.c

OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(ARCHIVE)
	$(CC) $(ARCHIVE) -o $(NAME)

$(ARCHIVE) : $(OBJS)
	$(MAKE_LIB) $(ARCHIVE) $(OBJS)

bonus : fclean $(BONUS_OBJS)
	$(MAKE_LIB) $(ARCHIVE) $(BONUS_OBJS)
	$(CC) $(ARCHIVE) -o $(NAME)

%.o : %.c 
	$(CC) $(CFLAGS) -c $< -o $@ 

clean :
	rm -f $(OBJS) $(BONUS_OBJS) $(ARCHIVE)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re bonus
