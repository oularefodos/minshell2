/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_initialisation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakboub <mmakboub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 23:42:52 by mmakboub          #+#    #+#             */
/*   Updated: 2023/01/05 15:24:06 by mmakboub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *put_my_shlvl(char *str)
{
    return (ft_substr(str, \
			ft_strlen(str) - ft_strlen(ft_strchr(str, '=') + 1), \
			ft_strlen(str)));
}

void env_initialisation(t_env **env)
{
	t_env	*head;
	char		*shlvl;

	head = *env;
	while (head)
	{
		if (ft_strcmp(head->name, "SHLVL") == 0)
		{
			shlvl = ft_itoa((ft_atoi(put_my_shlvl(head->value)) + 1));
			if (!shlvl)
				return (printf("minishell: memory was not allocated!\n"), \
				(void)0);
			free(head->value);
			head->value = ft_strjoin("=",shlvl);
			return ;
		}
		head = head->next;
	}
	// new_shlvl = printf("SHLVL=1");
	// ft_lstadd_back((ft_lstnew(&new_shlvl, 1)), &head);
}

int	ft_lstsize_env(t_env *lst)
{
	int	len;

	len = 0;
	while (lst)
	{
		lst = lst -> next;
		len++;
	}
	return (len);
}
char **convertto_doublep(t_env *env)
{
	int len;
	int i;
	char **dp;
	i = 0;
	len = ft_lstsize_env(env);
	dp = (char **)malloc(sizeof(char *) * (len +1));
	while (env)
	{
		dp[i] = ft_strjoin(env->name, env->value);
		i++;
		env = env->next;
	}
	dp[i] = NULL;
	return(dp);
}

char *convertto_char(t_env *env)
{
	char *p;
	p = ft_strjoin(env->name, env->value);
	if (p == NULL)
		return (NULL);
	return(p);
}