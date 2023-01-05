#include "../minishell.h"

t_element *parser(char *line) {
    t_element *ret;
    ret = tokeniser(line);
    if (!ret)
        return (NULL);
    if (grammar(ret))
        return NULL;
    // free temp
    ret = norm_one(ret);
    return ret;
}