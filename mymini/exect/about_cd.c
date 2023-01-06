/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   about_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakboub <mmakboub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 16:13:45 by mmakboub          #+#    #+#             */
/*   Updated: 2023/01/06 20:19:23 by mmakboub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	refresh_oldpwd(t_env **env, t_env *pwd)
{
	t_env	*tmp;
	char	*joined;

	tmp = *env;
	while (tmp && ft_strcmp(tmp->name, "OLDPWD"))
		tmp = tmp->next;
	if (tmp && tmp->value)
	{
		tmp->value = NULL;
		if (pwd)
			tmp->value = pwd->value;
		else
			tmp->value = ft_strdup("=");
	}
	else
	{
		joined = ft_strjoin("OLDPWD=", pwd->value);
		ft_lstadd_back(ft_lstnew(joined, 1), env);
	}
}

void	refresh_pwd(t_env **env)
{
	char	*pwd;
	t_env	*head;
	char	*joined;

	head = *env;
	pwd = getcwd(NULL, 0);
	while (head && ft_strcmp(head->name, "PWD"))
		head = head->next;
	if (head && head->value)
	{
		head->value = NULL;
		head->value = ft_strjoin("=", pwd);
	}
	else
	{
		joined = ft_strjoin("PWD=", pwd);
		ft_lstadd_back(ft_lstnew(joined, 1), env);
	}
}
