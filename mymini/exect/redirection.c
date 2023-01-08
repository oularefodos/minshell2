/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakboub <mmakboub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 22:57:34 by mmakboub          #+#    #+#             */
/*   Updated: 2023/01/08 05:09:21 by mmakboub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	redirec_out(t_element *tmp, t_element *next_node, int fd)
{
	next_node = tmp->next;
	fd = open(next_node->cmd, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd < 0)
	{
		perror(next_node->cmd);
		exit(1);
	}
	dup2(fd, 1);
	close(fd);
}

static void	redirec_inp(t_element *tmp, t_element *next_node, int fd)
{
	next_node = tmp->next;
	fd = open(next_node->cmd, O_RDONLY, 0777);
	if (fd < 0)
	{
		perror(next_node->cmd);
		exit(1);
	}
	dup2(fd, 0);
	close(fd);
}

static void	redirec_herdoc(t_element *tmp)
{
	dup2(tmp->pip[0], 0);
	close(tmp->pip[0]);
}

static void	redirec_add(t_element *tmp, t_element *next_node, int fd)
{
	next_node = tmp->next;
	fd = open(next_node->cmd, O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (fd < 0)
	{
		perror(next_node->cmd);
		exit(1);
	}
	dup2(fd, 1);
	close(fd);
}

void	handle_redirection(t_element *red)
{
	t_element	*tmp;
	t_element	*next_node;
	int			fd;

	tmp = red;
	fd = 0;
	next_node = NULL;
	while (tmp)
	{
		if(tmp->type == PIPE)
			break;
		if (tmp->type == SUP)
			redirec_out(tmp, next_node, fd);
		if (tmp->type == INF)
			redirec_inp(tmp, next_node, fd);
		if (tmp->type == ADD)
			redirec_add(tmp, next_node, fd);
		if (tmp->type == HERDOC)
			redirec_herdoc(tmp);
		tmp = tmp->next;
	}
}
