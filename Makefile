# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/27 11:00:22 by pirichar          #+#    #+#              #
#    Updated: 2022/03/31 12:55:42 by pirichar         ###   ########.fr        #
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
# OBJS		= $(addprefix $(OBJ)/, $(OFILES))
HEADERS		= $(addprefix $(INC)/, $(HFILES))

GNL			= gnl
GFILES		= get_next_line_utils.c get_next_line.c
OGNL		= $(GFILES:.c=.o)
GETNEXT		= $(addprefix $(GNL)/, $(GFILES))
OBJG		= $(addprefix $(OBJ)/, $(OGNL))

OBJS		= $(addprefix $(OBJ)/, $(OFILES) $(OGNL))
VPATH		= $(SRC) $(GNL)

CC			= gcc
CFLAGS		= -Wall -Werror -Wextra -g
RM			= rm -rf

# $(OBJ)/%.o:	$(SRC)/%.c 
$(OBJ)/%.o:	%.c 
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
			@norminette $(SRCS) $(HEADERS) $(GETNEXT)
