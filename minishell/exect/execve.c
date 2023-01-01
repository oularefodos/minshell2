/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakboub <mmakboub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 18:57:46 by mmakboub          #+#    #+#             */
/*   Updated: 2022/12/31 19:15:23 by mmakboub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"


char *execute_cmd(t_element *command, t_env **env)
{
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


/*
	1 : acces = >1 execve
	2 : path ==> /bin/ls => not fond

*/
void execve_cmd(t_element *command, t_env **env, char **argv)
{
    char *path;
	//char **env1;
	//env1 = convertto_doublep(*env);
    path = execute_cmd(command, env);
	if(!path)
	{
		printf("minishell :%s: command not found\n", command->cmd);
		return ;
	}
    if(fork() == 0)
	{
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

	len = 0;
	while (lst)
	{
		if (lst && lst->type != PIPE)
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