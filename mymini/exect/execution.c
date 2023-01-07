/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakboub <mmakboub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 16:18:27 by mmakboub          #+#    #+#             */
/*   Updated: 2023/01/07 01:08:49 by mmakboub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_lstsize_elem(t_element *lst)
{
	int	len;

	len = 1;
	while (lst)
	{
		if (lst->type == PIPE)
			len++;
		lst = lst->next;
	}
	return (len);
}

void	check_cmd(t_element *command, t_env **envv)
{
	char	**env;

	env = convertto_doublep(*envv);
	if (finder_getter(*envv, "PATH") == NULL)
	{
		if (check_builtings(command))
			is_builting(command, envv);
		else
		{
			printf("minishell: %s: no such file or directory\n", command->cmd);
			g_global.exit_status = 127;
			return ;
		}
		return ;
	}
	if (ft_lstsize_elem(command) > 1)
		handle_pipe(command, envv);
	else
	{
		expender(command, env);
		puts("ok8");
		if (check_builtings(command))
			is_builting(command, envv);
		else
		{
			puts("ok2");
			execve_cmd(command, envv, command->args);
		}
	}
}
