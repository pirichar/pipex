# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/27 11:00:22 by pirichar          #+#    #+#              #
#    Updated: 2022/04/07 15:31:21 by pirichar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRC			= src
INC			= include
OBJ			= obj
BNS 		= bonus
CFILES		= main.c environement.c ft_put_str_error.c ft_split.c pipex.c str_functions.c
HFILES		= colors.h pipex.h
OFILES		= $(CFILES:.c=.o)
SRCS		= $(addprefix $(SRC)/, $(CFILES))
HEADERS		= $(addprefix $(INC)/, $(HFILES))

GNL			= gnl
GFILES		= get_next_line_utils.c get_next_line.c
OGNL		= $(GFILES:.c=.o)
GETNEXT		= $(addprefix $(GNL)/, $(GFILES))
OBJG		= $(addprefix $(OBJ)/, $(OGNL))

OBJS		= $(addprefix $(OBJ)/, $(OFILES) $(OGNL))
VPATH		= $(SRC) $(GNL) $(BNS)


BFILES		= environement_bonus.c ft_put_str_error_bonus.c ft_split_bonus.c here_doc_bonus.c main_bonus.c pipex_bonus.c str_functions_bonus.c
BONUSNORM	= $(addprefix $(BNS)/, $(BFILES))
OBNS		= $(BFILES:.c=.o)
OBJBNS	 	= $(addprefix $(OBJ)/, $(OBNS) $(OGNL))

CC			= gcc
CFLAGS		= -Wall -Werror -Wextra -g
RM			= rm -rf

$(OBJ)/%.o:	%.c 
			@$(CC) $(CFLAGS) -c $< -o  $@
			
$(NAME):	$(OBJ) $(OBJS) 
			@$(CC) $(OBJS) -o $(NAME)
			@echo "COMPILING DONE"

$(OBJ):	
			@mkdir -p $(OBJ)

all:		$(NAME)

bonus :		$(OBJ) $(OBJBNS)
			@$(CC) $(OBJBNS) -o $(NAME)
			@echo "COMPILING BONUS DONE"
clean:
			@$(RM) $(OBJS) $(OBJ)

fclean:		clean
			@$(RM) $(NAME)

re:			fclean all

norme:
			@norminette $(SRCS) $(HEADERS) $(GETNEXT) $(BONUSNORM)
