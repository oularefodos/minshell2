#include "../minishell.h"

void norm_two(t_element **el);
int getsize(char **str) {
    int i;

    i = 0;
    while(str[i])
        i++;
    return (i);
}

char *concat(char *s1, char *s2)
{
    int size;
    int i;
    int y;
    char *ret;

    size = ft_strlen(s1) + ft_strlen(s2) + 1;
    ret = malloc(sizeof(char) * size);
    if (!ret)
        exit(1);
    i = -1;
    while(s1[++i])
        ret[i] = s1[i];
    y = -1;
    while (s2[++y])
        ret[i + y] = s2[y];
    ret[i + y] = 0;
    return (ret);
}

char **double_dup(char **s)
{
    char **ret;
    int i;

    i = 0;
    if (s == NULL)
        return (NULL);
    ret = malloc(sizeof(char *) * (getsize(s) + 1));
    if (ret == NULL)
        exit (1);
    while(s[i]) {
        ret[i] = ft_strdup(s[i]);
        i++;
    }
    ret[i] = NULL;
    return (ret);
}

char **ft_concat(char **s1, char **s2) {
    int len;
    char **ret;
    int i;
    int y;
    
    len = getsize(s1) + getsize(s2) + 1;
    ret = malloc(sizeof(char *) * len);
    if (!ret)
        exit(1);
    i = 0;
    y = 0;
    while (s1[i]) {
        ret[i] = ft_strdup(s1[i]);
        i++;
    }
    while (s2[y]) {
        ret[i + y] = ft_strdup(s2[y]);
        y++;
    }
    ret[i + y] = NULL;
    return (ret);
}

t_element *duplicate(t_element *n)
{
    t_element *ret;

    ret = malloc(sizeof(t_element));
    if (!ret)
        exit(1);
    ret->type = n->type;
    ret->args = double_dup(n->args);
    ret->next = NULL;
    return (ret);
}

void add_node_back(t_element **node, t_element *el)
{
    t_element *n;
    t_element *l;

    n = duplicate(el);
    if (*node == NULL){
       *node = n;
    }
    else {
        l = last(*node);
        l->next = n;
        n->prev = l;
    }
}
void norm_one_rest(t_element *node, t_element *n)
{
    char **temp;
    char *t;
    int i;

    i = getsize(node->args) - 1;
    if (n->space == 0)
    {
        t = node->args[i];
        node->args[i] = concat(node->args[i], n->args[0]);
        free(t);
    }
    else
    {
        temp = node->args;
        node->args = ft_concat(node->args, n->args);
        // free temp
    }
}

t_element *norm_one(t_element *el) {
    t_element *temp;
    t_element *ret;
    t_element *prev;

    temp = el;
    ret = NULL;
    while (el)
    {
        prev = el->prev;
        if (prev == NULL)
            add_node_back(&ret, el);
        else if ((el->type == CMD || el->type == SQUOT || el->type == DQUOT)
            && (prev->type == CMD || prev->type == SQUOT || prev->type == DQUOT))
                norm_one_rest(last(ret), el);
        else
            add_node_back(&ret, el);
        el = el->next;
    }
    ret->prev = NULL;
    norm_two(&ret);
    return ret;
}

void add_front(t_element **node, char **cmd, t_element **el) {
    t_element *prev;
    t_element *n;

    n = malloc(sizeof(t_element));
    if (!n)
        exit(1);
    n->args = double_dup(cmd);
    n->type = CMD;
    prev = (*node)->prev;
    (*node)->prev = n;
    n->next = *node;
    n->prev = prev;
    if (prev)
        prev->next = n;
    else
        *el = n;
}

void norm_two(t_element **el) {
    t_element *temp;
    char **t;

    temp = *el;
    while(temp) {
        if ((temp->type == INF || temp->type == ADD || temp->type == SUP || temp->type == HERDOC) 
            && getsize(temp->next->args) > 1)
        {
            
            if (temp->prev == NULL || temp->prev->type == PIPE) {
                add_front(&temp, &temp->next->args[1], el);
            }
            else
            {
                t = temp->prev->args;
                temp->prev->args = ft_concat(temp->prev->args, &temp->next->args[1]);
            }
        }
        if (temp->args) {
            temp->nbr_args = getsize(temp->args);
            temp->cmd = ft_strdup(temp->args[0]);
        }
        temp = temp->next;
    }    
}

