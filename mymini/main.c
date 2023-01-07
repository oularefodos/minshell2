/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakboub <mmakboub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 21:16:47 by mmakboub          #+#    #+#             */
/*   Updated: 2023/01/07 18:03:57 by mmakboub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print(t_element *m)
{
	t_element *t = m;

	while (t)
	{
		printf("%d\n", t->type);
		printf("%s\n", t->cmd);
		t = t->next;
	}
}

t_global	g_global;
int	ft_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}

int	readline_hook(void)
{
	return (0);
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
void	ignsig(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
void	sig_default(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	handling_sig(void)
{
	rl_catch_signals = 0;
	if (signal(SIGINT, handler) == SIG_ERR || signal(SIGQUIT,
			SIG_IGN) == SIG_ERR)
	{
		write(2, "sig error\n", 10);
		exit(1);
	}
}
int	main(int ac, char **str, char **env)
{
	(void)ac;
	(void)str;
	t_env *envr;
	char *line;
	t_element *element;
	int fd_1 = dup(1);
	g_global.end = NULL;
	g_global.temp = NULL;
	envr = build_env(env);
	env_initialisation(&envr);
	while (1)
	{
		handling_sig();
		line = readline("minishell> ");
		add_back_memory(line, 1);
		if (!line)
		{
			char *sr_cap;

			sr_cap = tgetstr("sr", NULL);
			tputs(sr_cap, 0, ft_putchar);
			printf("minishell> exit\n");
			// system("leaks minishell");
			free_memory(0);
			exit(g_global.exit_status);
		}
		if (*line)
		{
			add_history(line);
			element = parser(line, env);
			if (element)
			{
				if (!envr)
				{
					printf("sadly ! there is no env\n");
					continue;
				}
				check_cmd(element, &envr);
				free_memory(1);
			}
		}
		dup2(fd_1, 1);
	}
	return (0);
}