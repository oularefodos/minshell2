#include "../minishell.h"

void herdoc(t_element *s)
{
    char *line;
    
    if (pipe(s->pip) == -1)
        exit(1);
    line = readline("> ");
    while (line && ft_strcmp(line, s->next->args[0]))
    {
        write(s->pip[1], line, ft_strlen(line));
        write(s->pip[1], "\n", 1);
        free(line);
        line = readline("> ");
    }
    close(s->pip[1]);
}

int check_rest_error(int type, int next)
{
    if (next == ADD && type != PIPE) 
    {
        ft_putstr_fd("minishell: syntax error near unexpected token `>>'\n", 1);
        return 1;
    }
    if (next == SUP && type != PIPE) 
    {
        ft_putstr_fd("minishell: syntax error near unexpected token `>'\n", 1);
        return 1;
    }
    if (next == INF && type != PIPE) 
    {
        ft_putstr_fd("minishell: syntax error near unexpected token `<'\n", 1);
        return 1;
    }
    return (0);
}