#include "../minishell.h"

char *insert(char *str, int index, char *s, int sz) {
    int size;
    int i;
    int y;
    char *temp;

    size = ft_strlen(str) - sz + ft_strlen(s);
    temp = str;
    str = malloc(sizeof(char) * (size + 1));
    if (str == NULL)
        exit(1);
    i = -1;
    while (++i < index)
        str[i] = temp[i];
    while (*s)
    {
        str[i++] = *s;
        s++;
    }
    y = index + sz;
    while(temp[y])
        str[i++] = temp[y++];
    str[i] = 0;
    // free(temp);
    // free(s);
    return(str);
}


char *takevarvalue(char *str, char **env){
    int i;
    char *s;
    char *ret;
    int sz;

    s = ft_strjoin(str + 1, "=");
    i = 0;
    sz = ft_strlen(s);
    ret = NULL;
    while(env[i])
    {
        if (!ft_strncmp(s, env[i], sz))
            ret = ft_strdup(&env[i][sz]);
        i++;
    }
    if (ret == NULL)
        ret = ft_strdup("");
    free(s);
    free(str);
    return (ret);
}

int checkvarexist(char *s)
{
    int i;
    int x;
    int y;

    i = 0;
    x = 0;
    y = 0;
    while (s[i])
    {
        if (!x && s[i] == '"')
            x++;
        if (s[i] == '\'' && !(x % 2))
        {
            i++;
            while (s[i] != '\'')
                i++;
        }
        if (s[i] == '$' && s[i + 1] != ' ' && s[i + 1])
            return (i);
        i++;
    }
    return (-1);
}

char **fixed_char(char **str)
{
    int size;
    char **newstr;
    int i;
    int y;

    size = getsize(str);
    i = 0;
    while(str[i])
        if (str[i++][0] == '\0')
            size--;
    i = 0;
    y = 0;
    newstr = malloc(sizeof(char *) * (size + 1));
    if(!newstr)
        exit(1);
    while (str[i])
    {
        if (str[i][0])
            newstr[y++] = ft_strdup(str[i]);
        i++;
    }
    newstr[y] = NULL;
    return (newstr);
}

int takesize(char *s)
{
    int i;
    int c;

    i = 0;
    if (*(s + 1) == '\'')
        c = '\'';
    if (*(s + 1) == '"')
        c = '"';
    else
        c = ' ';
    while (s[i] && s[i] != c)
    {
        i++;
        if ((s[i] == '$' || s[i] == '\'' || s[i] == '"') && c == ' ')
            break;
    }
    return (i);
}

void expender(t_element *s, char **env)
{
    t_element *t;
    int i;
    char *str;
    int y;
    int index;
    char *temp;

    t = s;
    if (t->type != CMD && t->type != DQUOT && t->type != SQUOT)
        return ;
    i = 0;
    while (t->args[i]) {
        index = checkvarexist(t->args[i]);
        while (index >= 0)
        {
            y = takesize(&t->args[i][index]);
            if (t->args[i][index + 1] !=  '\'' && t->args[i][index + 1] !=  '\"')
            {
                temp = ft_substr(t->args[i], index, y);
                str = takevarvalue(temp, env);
            }
            else
            {
                temp = ft_substr(t->args[i], index + 1, y - 1);
                str = temp;
            }
            t->args[i] = insert(t->args[i], index, str, y);
            index = checkvarexist(t->args[i]);
        }
        i++;
    }
    t->args = fixed_char(t->args);
    t->cmd = t->args[0];
    delete_quote(s);
}