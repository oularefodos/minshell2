#include "../minishell.h"
int grammar(t_element *s) {
    t_element *node;
    t_element *lst;
    int i;
    int x;
    int y;

    node = s;
    lst = last(node);
    if (lst->type == PIPE || lst->type == INF || lst->type == SUP || lst->type == ADD || lst->type == HERDOC ) {
        ft_putstr_fd("bash: syntax error near unexpected token `newline'\n", 1);
        return 1;
    }
    if (node->type == PIPE ) {
        ft_putstr_fd("bash: syntax error near unexpected token `|'\n", 1);
        return 1;
    }
    while(s) {
        if (s->type != CMD && s->type != SQUOT && s->type != DQUOT) {
            if (s->next->type == PIPE) {
                ft_putstr_fd("bash: syntax error near unexpected token `|'\n", 1);
                return 1;
            }
            if (s->next->type == HERDOC && s->type != PIPE) {
                ft_putstr_fd("bash: syntax error near unexpected token `<<'\n", 1);
                return 1;
            }
            if (s->next->type == ADD && s->type != PIPE) {
                ft_putstr_fd("bash: syntax error near unexpected token `>>'\n", 1);
                return 1;
            }
            if (s->next->type == SUP && s->type != PIPE) {
                ft_putstr_fd("bash: syntax error near unexpected token `>'\n", 1);
                return 1;
            }
            if (s->next->type == INF && s->type != PIPE) {
                ft_putstr_fd("bash: syntax error near unexpected token `<'\n", 1);
                return 1;
            }
        }
        if (s->type == SQUOT || s->type == DQUOT) {
            i = 0;
            x = 0;
            y = 0;
            while (s->cmd[0][i])
                i++;
            if (s->cmd[0][0] != s->cmd[0][--i]) {
                ft_putstr_fd("bash: syntax error", 1);
                if (s->type == DQUOT)
                    ft_putstr_fd(" `\"\n", 1);
                else
                    ft_putstr_fd(" `'\n", 1);
                return 1;
            }
        }
        s = s->next;
    }
    return 0;
}