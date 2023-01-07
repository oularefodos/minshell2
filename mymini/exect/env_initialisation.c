/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_initialisation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakboub <mmakboub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 23:42:52 by mmakboub          #+#    #+#             */
/*   Updated: 2023/01/06 23:01:09 by mmakboub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*put_my_shlvl(char *str)
{
	return (ft_substr(str, \
			ft_strlen(str) - ft_strlen(ft_strchr(str, '=') + 1), \
				ft_strlen(str), 0));
}

void	env_initialisation(t_env **env)
{
	t_env	*head;
	char	*shlvl;
	char	*new_shlvl;

	head = *env;
	while (head)
	{
		if (ft_strcmp(head->name, "SHLVL") == 0)
		{
			shlvl = ft_itoa((ft_atoi(put_my_shlvl(head->value)) + 1), 0);
			if (!shlvl)
				return (printf("minishell: memory was not allocated!\n"), \
						(void)0);
			head->value = ft_strjoin("=", shlvl, 0);
			return ;
		}
		head = head->next;
	}
	new_shlvl = ("SHLVL=1");
	ft_lstadd_back((ft_lstnew(new_shlvl, 1)), env);
}
