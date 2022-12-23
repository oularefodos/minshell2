#include "minishell.h"

void display(t_element *c)
{
    char *Eltype[] = {"PIPE", "INF", "SUP", "ADD", "HER", "CMD", "SQUOT", "DQUOT"};
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
            while(s->cmd[i]) {
                printf("%s | ", s->cmd[i]);
                i++;
            }
            puts("");
        }
        s = s->next;
    }
}

int main() {
    char *line;
    t_element *elemnt;
    while (1) {
        line = readline("minishell> ");
        add_history(line);
        elemnt  = parser(line);
        if (elemnt) {
            display(elemnt);
        }
    }
}