/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakboub <mmakboub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 01:21:19 by mmakboub          #+#    #+#             */
/*   Updated: 2023/01/03 04:10:38 by mmakboub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>
#include<signal.h>
#include "minishell.h"
  
// Handler for SIGINT, caused by
// Ctrl-C at keyboard
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
  
int main()
{
    char *line;
        //rl_catch_signals = 0;
        signal(SIGINT, handler);
    while (1) 
    {
        line = readline("minishell> ");
        if (!line)
            exit(0);
        if(*line)
        {
            add_history(line);
            
        }           
    }
    return 0;
}