/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakboub <mmakboub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 18:57:46 by mmakboub          #+#    #+#             */
/*   Updated: 2023/01/01 23:48:01 by mmakboub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"


char *execute_cmd(t_element *command, t_env **env)
{
	if(!env)
		return(NULL);
	char *line;
	char *path;
	char **splited_path;
	if(check_accecs_exec(command->cmd))//todo : ADD another fonction that check only accessibility while the path is executable and replace it in this line (nammed :check_access)
		return (strdup(command->cmd));
	line = convertto_char(finder_getter(*env,"PATH"));
	if(!line)
		return(NULL);
	splited_path = ft_split(line, ':');
	if(!splited_path)
		return(NULL);
	path = join_get_acces(splited_path, command->cmd);
    if (!path)
		return(NULL);
	return(path);
}
int check_accecs_exec(char *joined_path)
{
	int acc1;
	int acc2;
	acc1 = access(joined_path, F_OK);
	acc2 = access(joined_path, X_OK);
	if(acc1 == 0 && acc2 == 0)
		return(1);
	return(0);
}

char *join_get_acces(char **splited_path, char *cmd)
{
	int i;
	i = 0;
	char *tmp;
	while(splited_path[i])
	{
		tmp = ft_strdup(splited_path[i]);
		free(splited_path[i]);
		splited_path[i] = ft_concatenate(tmp, "/", cmd);
		free(tmp);
		if(check_accecs_exec(splited_path[i]))
			return(ft_strdup(splited_path[i]));
		i++;
	}
	return(NULL);
}

void handle_redirection(t_element *red)
{
    t_element *tmp;
    t_element *next_node;
	int fd;

    tmp = red;
    while (tmp)
    {   
    //    if (tmp->type == PIPE)
    //        break;
       if (tmp->type == SUP)
       {
           next_node = tmp->next;
           fd = open(next_node->cmd, O_CREAT | O_WRONLY, 0777);
		   if (fd < 0)
		   {
				printf("sup fd error %d %s\n", fd, next_node->cmd);
				exit (1);
		   }
           dup2(fd, 1);
		   close(fd);
       }

       if (tmp->type == INF)
       {
           next_node = tmp->next;
           fd = open(next_node->cmd, O_CREAT | O_RDONLY, 0777);
		   if (fd < 0)
		   {
				printf("inf fd error %d %s\n", fd, next_node->cmd);
				exit (1);
		   }
           dup2(fd, 0);
		   close(fd);
       }

       if (tmp->type == ADD)
       {
           next_node = tmp->next;
           int fd = open(next_node->cmd, O_CREAT | O_WRONLY | O_APPEND);
		   if (fd < 0)
		   {
				printf("inf fd error %d %s\n", fd, next_node->cmd);
				exit (1);
		   }
           dup2(fd, 1);
		   close(fd);
       }
       tmp = tmp->next;
    }
}


void execve_cmd(t_element *command, t_env **env, char **argv)
{
    char *path;
	
	if(!env)
		return ;
    path = execute_cmd(command, env);
    if(fork() == 0)
	{
		handle_redirection(command);
		if(!path)
		{
			printf("minishell :%s: command not found\n", command->cmd);
			exit(127);
		}
		if(execve(path, argv, convertto_doublep(*env)) == -1)
        	printf("minishell: %s: %s\n", path, strerror(errno));
		exit(0);
	}
	wait(NULL);
    free(path);
}

int	ft_lstsize_elem(t_element *lst)
{
	int	len;

	len = 1;
	while (lst)
	{
		if (lst->type == PIPE)
			len++;
		lst = lst -> next;
	}
	return (len);
}

void check_cmd(t_element *command, t_env **envv)
{
	if (command->type == INF)
		puts("-------------------");
	// printf("size == %d\n", ft_lstsize_elem(command));
	else if (ft_lstsize_elem(command) > 1)
		handle_pipe(command, envv);
	else
	{
		if(check_builtings(command))
			is_builting(command, envv);
		else
			execve_cmd(command, envv, command->args);		
	}
}