/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakboub <mmakboub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 21:16:47 by mmakboub          #+#    #+#             */
/*   Updated: 2023/01/05 16:29:26 by mmakboub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
t_global	g_global;
int ft_putchar(int  c)
{
  write(1, &c, 1);
  return (1);     
}
 void	handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
	    rl_replace_line("", 0);
	    rl_on_new_line();
	    rl_redisplay();
	}
}
 
void    handling_sig(void)
{
    rl_catch_signals = 0;
	if (signal(SIGINT, handler) == SIG_ERR \
	 || signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	{
		write(2, "sig error\n", 10);
		exit (1);
	}
}
int main(int ac, char **str, char **env) 
{

    (void)ac;
    (void)str;
    t_env *envr;
    char *line;
    t_element *element;
    int fd_1 = dup(1);
    envr = build_env(env);
    puts("hi");
    env_initialisation(&envr);
    handling_sig();
    while (1) {
        line = readline("minishell> ");
        if (!line)
        {
            char		*sr_cap;

            sr_cap = tgetstr("sr", NULL);
            tputs(sr_cap, 0, ft_putchar);
	        printf("minishell> exit\n");
            exit(0);
        }
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