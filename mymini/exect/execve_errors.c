/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakboub <mmakboub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 16:19:48 by mmakboub          #+#    #+#             */
/*   Updated: 2023/01/07 17:31:04 by mmakboub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	path_error(char *cmd)
{
	printf("minishell: %s: command not found\n", cmd);
	g_global.exit_status = 127;
	exit(127);
	return ;
}

void	execve_cmd_error(char *path, t_element *command)
{
	if (!path)
		path_error(command->cmd);
	if (!command->args || !command->args[0])
		exit(0);
}

void	execve_failure(char *cmd)
{
	(void)cmd;
	int fd;

	fd = dup(1);
	dup2(1, 2);
	if (access(cmd, W_OK) && !access(cmd, F_OK))
	{
		printf("minishell: %s: is a directory\n", cmd);
		exit(126);
	}
	printf("minishell: %s: %s\n", cmd, strerror(errno));
	dup2(fd, 1);
	close(fd);
	g_global.exit_status = 127;
	return ;
}