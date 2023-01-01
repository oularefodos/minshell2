#include "minishell.h"

void display(t_element *c)
{
    char *Eltype[] = {"PIPE", "INF", "SUP", "ADD", "HER", "CMD", "SQUOT", "DQUOT", "FILE"};
    int i = 0;
    t_element *s;
    s = c;
    if (s->type < 0){
        printf("error\n\n");
        exit(1);
    }
    while (s) {
        printf("TYPE : %s\n", Eltype[s->type]);
        if (s->type == CMD || s->type == SQUOT || s->type == DQUOT) {
            i = 0;
            while(s->args[i]) {
                printf("%s ", s->args[i]);
                i++;
            }
        }
        puts("\n------------------------------");
        s = s->next;
    }
}
// > file < f >
int main(int ac, char **str, char **env) {

    (void)ac;
    (void)str;
    t_env *envr;
    char *line;
    t_element *element;
    int fd_1 = dup(1);
    envr = build_env(env);
    while (1) {
        line = readline("minishell> ");
        if (!line)
            exit(0);
        if(*line) {
        add_history(line);
        element  = parser(line);
        if (element) 
        {
            if(!envr)
            {
                printf("sadly ! there is no env\n");
                return(1);
            }
            check_cmd(element, &envr);
        }
        }
        dup2(fd_1, 1);
    }
    return(0);
}