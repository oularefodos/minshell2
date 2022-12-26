#ifndef MINISHELL_H
#define MINISHELL_H

#define PIPE 0
#define INF 1
#define SUP 2
#define ADD 3
#define HERDOC 4
#define CMD 5
#define SQUOT 6
#define DQUOT 7
 
#include "Libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

typedef struct element {
    int type;
    int space;
    char **cmd;
    int her[2];
    struct element *next;
    struct element *prev;
}   t_element;

t_element *tokeniser(char *line);
t_element *parser(char *line);
t_element *last(t_element *s);
int grammar(t_element *s);
char *add(char **str, char *s);
t_element *norm_one(t_element *el);
void expender(t_element *s, char **env);
void delete_quote(t_element *s);
#endif