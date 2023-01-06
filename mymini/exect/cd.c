/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: mmakboub <mmakboub@student.42.fr>          +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2022/11/21 20:14:40 by mmakboub          #+#    #+#             */
/*   Updated: 2022/12/31 00:31:36 by mmakboub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	back_to_home(t_env **env, t_env *pwd)
{
	t_env	*home;

	home = finder_getter(*env, "HOME");
	if (!home)
	{
		printf("Minishell: cd: HOME not set\n");
		return ;
	}
	if (chdir(&home->value[1]) == -1)
		printf("minishell: cd: %s\n", strerror(errno));
	else
	{
		refresh_oldpwd(env, pwd);
		refresh_pwd(env);
	}
}

void	updatepwd(t_env **env, char *arg)
{
	t_env	*nenv;
	t_env	*oenv;
	char	*temp;

	nenv = finder_getter(*env, "PWD");
	oenv = finder_getter(*env, "OLDPWD");
	temp = oenv->value;
	oenv->value = ft_strdup(nenv->value);
	free(temp);
	temp = nenv->value;
	nenv->value = ft_concatenate(temp, "/", arg);
	free(temp);
	temp = NULL;
}

void	cd(t_element *command, t_env **env)
{
	t_env	*pwd;
	t_env	*oldpwd;
	// char *tmp;
	pwd = finder_getter(*env, "PWD");
	oldpwd = finder_getter(*env, "OLDPWD");
	if(!getcwd(NULL, 0))
	{
		printf("minishell: cd: error retrieving current directory: "
			"getcwd: cannot access parent directories\n");
		chdir("~");
		printf("ok");
		return ;
	}
	if ((!ft_strcmp(command->args[0], "cd") && command->nbr_args == 1)
		|| (!ft_strcmp(command->cmd, "cd") && (!strcmp(command->args[1], "--")
				|| !strcmp(command->args[1], "~")
				|| (command->args[1][0] == '#'))))
		back_to_home(env, pwd);
	else if (command->nbr_args > 1)
	{
		if (chdir(command->args[1]) == -1)
			printf("minishell: cd: %s\n", strerror(errno));
		else
		{
			if (!pwd || !oldpwd)
			{
				refresh_oldpwd(env, pwd);
				return ;
			}
			refresh_oldpwd(env, pwd);
			refresh_pwd(env);
		}
	}
}
