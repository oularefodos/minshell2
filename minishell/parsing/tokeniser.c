#include "../minishell.h"

t_element *last(t_element *s) {
    t_element *c;
    c = s;
    while(c->next)
        c = c->next;
    return c;
}

int issep(char c, char *sep) {
    int i;

    i = 0;
    while (sep[i])
    {
        if (c == sep[i])
            return 1;
        i++;
    }
    return 0;
} 


t_element *new_element(int type, char *str, t_element *prev) {
    t_element *new;
    new = malloc(sizeof(t_element));
    if (!new)
    {
        free(str);
        return (NULL);
    }
    new->type = type;
    new->cmd = ft_split(str, ' ');
    new->next = NULL;
    new->prev = prev;
    free(str);
    return (new);   
}

void add_back(t_element **node, char *str, int type, int len) {
    char *s;
    t_element *lst;
    if ((type == CMD || type == SQUOT || type == DQUOT) && str)
        s = ft_substr(str - len, 0, len);
    else
        s = NULL;
    if (*node == NULL)
        *node = new_element(type, s, NULL);
    else {
        lst = last(*node);
        lst->next = new_element(type, s, lst);
    }
}

t_element *tokeniser(char *line) {
    t_element *elmnt;
    int len;
    elmnt = NULL;

    while(*line) {
        len = 0;
        while(*line == ' ')
            line++;
        if (*line == '\0')
            break;
        if (!issep(*line, "<>|'\"")) {
            while(!issep(*line, "<>|'\"") && *line) {
                len++;
                line++;
            }
            add_back(&elmnt, line, CMD, len);
            len = 0;
        }
        else if (*line =='<')  {
            while(*line && *line == '<' && len < 2) {
                len++;
                line++;
            }
            if (len == 1)
                add_back(&elmnt, NULL, INF, len);
            else if (len == 2)
                add_back(&elmnt, NULL, HERDOC, len);
            len = 0;
        }
        else if (*line =='>')  {
            while(*line && *line == '>' && len < 2) {
                len++;
                line++;
            }
            if (len == 1)
                add_back(&elmnt, NULL, SUP, len);
            else if (len == 2)
                add_back(&elmnt, NULL, ADD, len);
            len = 0;
            }
        else if (*line =='|') {
            add_back(&elmnt, NULL, PIPE, len);
            line++;
        }
    }
    return elmnt;
}