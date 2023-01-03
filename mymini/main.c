/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakboub <mmakboub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 21:16:47 by mmakboub          #+#    #+#             */
/*   Updated: 2023/01/03 16:21:19 by mmakboub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_putchar(int  c)
{
  write(1, &c, 1);
  return (1);     
}

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
int main(int ac, char **str, char **env) 
{

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
        {
            char		*sr_cap;

            sr_cap = tgetstr("sr", NULL);
            tputs(sr_cap, 0, ft_putchar);
	        printf("\nminishell$> exit\n");
    system("leaks a.out");

            exit(0);
        }
        if(*line) {
        add_history(line);
        element  = parser(line);
        // printf("%d\n", element->next->args == NULL);
        // display(element);
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