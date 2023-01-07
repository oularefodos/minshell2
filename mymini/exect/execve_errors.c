/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakboub <mmakboub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 16:19:48 by mmakboub          #+#    #+#             */
/*   Updated: 2023/01/07 04:14:28 by mmakboub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	path_error(char *cmd)
{
	printf("minisherll: %s: command not found\n", cmd);
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

	printf("minishell: %s: %s\n", cmd, strerror(errno));
	g_global.exit_status = 127;
	exit(127);
	return ;
}