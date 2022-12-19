#include "../minishell.h"

int getsize(char **str) {
    int i;

    i = 0;
    while(*str[i])
        i++;
    return (i);
}

char *add(char **str, char *s) {
    int size;
    int i;
    char **ret;
    size = getsize(str) + 2;
    ret = malloc(sizeof(char *) + size);
    if (!ret)
        exit(1);
    i = 0;
    while (str[i]){
        ret[i] = ft_strdup(str);
        free(str[i++]);
    }
    ret[i++] = ft_strdup(s);
    ret[i] = NULL;
    free(s);
    free(str);
    return ret;
}

char **ft_concat(char **s1, char **s2) {
    int len;
    char **ret;
    int i;
    int y;
    len = getsize(s1) + getsize(s2) + 1;
    ret = malloc(sizeof(char *) * len);
    if (!ret)
        return NULL;
    i = 0;
    y = 0;
    while (s1[i]) {
        ret[i] = s1[i];
        i++;
    }
    while (s1[y]) {
        ret[i + y] = s1[y];
        y++;
    }
    ret[len] = NULL;
    return (ret);
}