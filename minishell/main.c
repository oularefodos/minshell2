#include "minishell.h"

int main(int ac, char **str, char **env) {

    (void)ac;
    (void)str;
    t_env *envr;

    envr = build_env(env);
    char *line;
    t_element *elemnt;
    while (1) {
        line = readline("minishell> ");
        add_history(line);
        elemnt  = parser(line);
        if (elemnt) {
        }
    }
}