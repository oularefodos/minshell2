/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakboub <mmakboub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 18:57:46 by mmakboub          #+#    #+#             */
/*   Updated: 2023/01/07 01:10:55 by mmakboub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*execute_cmd(t_element *command, t_env **env)
{
	char	*line;
	char	*path;
	char	**splited_path;

	if (!env)
		return (NULL);
	if (!command->args || !command->args[0])
		return (ft_strdup("", 1));
	if (check_caract(command->cmd, '/'))
		return (ft_strdup(command->cmd, 1));
	line = convertto_char(finder_getter(*env, "PATH"));
	if (!line)
		return (NULL);
	splited_path = ft_split(line, ':');
	if (!splited_path)
		return (NULL);
	path = join_get_acces(splited_path, command->cmd);
	if (!path)
		return (NULL);
	return (path);
}

int	check_accecs_exec(char *joined_path)
{
	int	acc1;
	int	acc2;

	acc1 = access(joined_path, F_OK);
	acc2 = access(joined_path, X_OK);
	if (acc1 == 0 && acc2 == 0)
		return (1);
	return (0);
}

char	*join_get_acces(char **splited_path, char *cmd)
{
	int		i;
	char	*tmp;

	i = 0;
	while (splited_path[i])
	{
		tmp = ft_strdup(splited_path[i], 1);
		splited_path[i] = ft_concatenate(tmp, "/", cmd);
		if (check_accecs_exec(splited_path[i]))
			return (ft_strdup(splited_path[i], 1));
		i++;
	}
	return (NULL);
}

void	execve_cmd(t_element *command, t_env **env, char **argv)
{
	char	*path;
	int		wstatus;
	int		pid;

	if (!env || !command)
		return ;
	pid = fork();
		puts("ok1");
	path = execute_cmd(command, env);
	if (pid == 0)
	{
		sig_default();
		handle_redirection(command);
		execve_cmd_error(path, command);
		if (execve(path, argv, convertto_doublep(*env)) == -1)
			execve_failure(command->cmd);
		exit(0);
	}
	ignsig();
	waitpid(pid, &wstatus, 0);
	if (WIFEXITED(wstatus))
		g_global.exit_status = WEXITSTATUS(wstatus);
	else
		g_global.exit_status = wstatus;
}
