#include "../minishell.h"

char *deleteone(char *s, int index, int x)
{
    int i;
    int y;
    char *str;

    str = malloc(sizeof(char) * ft_strlen(s) - 1);
    if (!str)
        exit(1);
    i = 0;
    y = 0;
    while (s[i])
    {
        while(i == index || i == x)
            i++;
        if (!s[i])
            break;
        str[y++] = s[i++];
    }
    str[y] = 0;
    return (str);
}

int rest_delete(t_element *t, int i, int *y)
{
    char *temp;
    int c;
    int p;

    c = 0;
    if (t->args[i][*y] == '\'')
        c = '\'';
    if (t->args[i][*y] == '"')
        c = '"';
    if (c)
    {
        p = (*y)++;
        while (t->args[i][*y] != c)
            (*y)++;
        temp = t->args[i];
        t->args[i] = deleteone(t->args[i], p, *y);
        *y -= 1;
        free(temp);
        if (t->args[i][*y] == 0)
            return (1);
    }
        return (0);

}

void delete_quote(t_element *t)
{
    int i;
    int y;

    i = 0;
    y = 0;
    while(t->args[i])
    {
        y = 0;
        while(t->args[i][y])
        {

           if (t->args[i][y] == '\'' || t->args[i][y] == '"')
           {
                if (rest_delete(t, i, &y))
                    break;
           }
            else
                y++;
        }
        i++;
    }
    t->cmd = t->args[0];
}