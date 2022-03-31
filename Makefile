# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/27 11:00:22 by pirichar          #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2022/03/30 09:45:25 by pirichar         ###   ########.fr        #
=======
#    Updated: 2022/03/28 15:15:24 by pirichar         ###   ########.fr        #
>>>>>>> ff38854cb930db2703bb2e6164caee07ef18a0c8
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRC			= src
INC			= include
OBJ			= obj
CFILES		= main.c environement.c ft_put_str_error.c ft_split.c pipex.c str_functions.c
HFILES		= colors.h pipex.h
OFILES		= $(CFILES:.c=.o)
SRCS		= $(addprefix $(SRC)/, $(CFILES))
OBJS		= $(addprefix $(OBJ)/, $(OFILES))
HEADERS		= $(addprefix $(INC)/, $(HFILES))

CC			= gcc
<<<<<<< HEAD
CFLAGS		= -Wall -Werror -Wextra -g -O3
=======
CFLAGS		= -Wall -Werror -Wextra -g -O1
>>>>>>> ff38854cb930db2703bb2e6164caee07ef18a0c8
RM			= rm -rf

$(OBJ)/%.o:	$(SRC)/%.c
			@$(CC) $(CFLAGS) -c $< -o  $@


$(NAME):	$(OBJ) $(OBJS)
			@$(CC) $(OBJS) -o $(NAME)
			@echo "COMPILING DONE"

$(OBJ):
			@mkdir -p $(OBJ)

all:		$(NAME)

clean:
			@$(RM) $(OBJS) $(OBJ)

fclean:		clean
			@$(RM) $(NAME)

re:			fclean all

norme:
			@norminette $(SRCS) $(HEADERS)

	
