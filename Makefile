all:
	gcc -Wall -Wextra -Werror main.c -lreadline Libft/libft.a  exect/* parsing/* -fsanitize=address -g
