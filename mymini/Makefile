# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmakboub <mmakboub@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/03 04:13:27 by mmakboub          #+#    #+#              #
#    Updated: 2023/01/03 19:27:39 by mmakboub         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell
FONCTIONS = ./exect/cd.c\
			./exect/echo2.c\
			./exect/env.c\
			./exect/exit.c\
			./exect/export.c\
			./exect/is_builting.c\
			./exect/pipe.c\
            ./exect/pwd.c\
            ./exect/unset.c\
            ./exect/utils.c\
            ./exect/build_envirement.c\
            ./exect/env_initialisation.c\
			./exect/execve.c ./libft/ft_memset.c\
			./libft/ft_strjoin.c ./libft/ft_strtrim.c\
			./libft/ft_isprint.c\
			./libft/ft_putchar_fd.c ./libft/ft_strlcat.c\
			./libft/ft_substr.c ./libft/ft_atoi.c\
			./libft/ft_itoa.c ./libft/ft_putendl_fd.c\
			./libft/ft_strlcpy.c \
			./libft/ft_bzero.c ./libft/ft_putnbr_fd.c\
			./libft/ft_strlen.c ./libft/ft_toupper.c ./libft/ft_calloc.c\
			./libft/ft_memchr.c ./libft/ft_putstr_fd.c\
			./libft/ft_strmapi.c ./libft/ft_isalnum.c\
			./libft/ft_memcmp.c ./libft/ft_strncmp.c\
			./libft/ft_isalpha.c ./libft/ft_split.c\
			./libft/ft_memcpy.c ./libft/ft_strchr.c\
			./libft/ft_strnstr.c ./libft/ft_tolower.c\
			./libft/ft_memmove.c ./libft/ft_strdup.c\
			./libft/ft_strrchr.c ./libft/ft_strcmp.c\
			./parsing/delete_qote.c\
			./parsing/expender.c\
			./parsing/grammar.c\
			./parsing/parser.c\
			./parsing/tokeniser.c\
			./parsing/utils.c\
			./main.c

	
CC = cc
CFLAGS = -Wall -Werror -Wextra
RM = rm -f
INCLUDE = minishell.h
LFLAGS = -L/Users/mmakboub/.brew/opt/readline/lib
IFLAGS = -I/Users/mmakboub/.brew/opt/readline/include

OBJS = $(FONCTIONS:.c=.o)

all : $(NAME)

$(NAME) :	$(OBJS)	$(INCLUDE)
	$(CC) $(CFLAGS)  $(OBJS) -o $(NAME) -lreadline -lncurses $(LFLAGS)

%.o : %.c $(INCLUDE)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@
	
clean:
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME) 

re: fclean all