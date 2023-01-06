/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: mmakboub <mmakboub@student.42.fr>          +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2022/11/21 11:05:55 by mmakboub          #+#    #+#             */
/*   Updated: 2022/12/18 20:39:00 by mmakboub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


char	*receive_name_export(char *allstr)
{
	return (ft_substr(allstr, 0, strlen(allstr) - strlen(strchr(allstr,
					'+'))));
}

char	*receive_value_export(char *allstr)
{
	return (ft_substr(allstr, strlen(allstr) - strlen(strchr(allstr, '=')) + 1,
			strlen(allstr)));
}
void	check_empty_export(char *str)
{
	if (ft_strlen(str) == 0)
	{
		printf("minishell: export: `%s': not a valid identifier\n", str);
		return ;
	}
}

void	export(t_env **env, t_element *command)
{
	int i = 1;
	t_env *tmp;
	t_env *newelement;

	if (command->nbr_args == 1 || (command->nbr_args == 2
			&& (command->args[1][0] == '#' || !ft_strcmp(command->args[1],
					";"))))
	{
		printf_env(env);
		return ;
	}
	while (command->args[i])
	{
		if (!check_is_valid(command->args[i]))
			return ;
		if (env_finder(*env, receive_name(command->args[i])))
		{
			env_finder(*env,
						receive_name(command->args[i]))
				->value = receive_value(command->args[i]);
			i++;
			continue ;
		}
		if (check_caract(command->args[i], '=') == 1)
		{
			if (check_plus(command->args[i], '+', '='))
			{
				if (env_finder(*env, receive_name_export(command->args[i])))
				{
					tmp = env_finder(*(env),
										receive_name_export(command->args[i]));
					if (tmp->value)
						tmp->value = ft_strjoin(tmp->value,
												receive_value_export(command->args[i]));
					else
						tmp->value = receive_value_export(command->args[i]);
				}
				else
					ft_lstadd_back(ft_lstnew(command->args[i], 2), env);
			}
			else
			{
				if (env_finder(*env, receive_name(command->args[i])))
					env_finder(*env,
								receive_name(command->args[i]))
						->value = receive_value(command->args[i]);
				else
					ft_lstadd_back(ft_lstnew(command->args[i], 1), env);
			}
		}
		else
		{
			newelement = (t_env *)ft_malloc(sizeof(t_env), 1);
			if (newelement == 0)
				return ;
			newelement->name = ft_strdup(command->args[i]);
			newelement->value = NULL;
			newelement->next = NULL;
			printf("%s\n", newelement->name);
			ft_lstadd_back(newelement, env);
		}
		i++;
	}
}

//still trsiting first condition case it should not add the argument to exportand and handled errors;