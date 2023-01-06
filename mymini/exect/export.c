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


int	check_caract(char *str, char c)
{
	int i = 1;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}
int	check_plus(char *str, char c, char x)
{
	if (!str)
		return (0);
	int i = 0;
	while (str[i] && str[i + 1])
	{
		if (str[i] == c && str[i + 1] == x)
			return (1);
		i++;
	}
	return (0);
}
int	ft_envsize(t_env *lst)
{
	int len;

	len = 0;
	while (lst)
	{
		lst = lst->next;
		len++;
	}
	return (len);
}

t_env	*sort_env(t_env *env)
{
	char *tmp_name;
	char *tmp_value;
	t_env *temp_head;
	int i;

	temp_head = env;
	i = ft_envsize(temp_head);
	while (i > 0)
	{
		temp_head = env;
		while (temp_head != NULL && temp_head->next != NULL)
		{
			if (temp_head->name[0] > temp_head->next->name[0])
			{
				tmp_name = temp_head->name;
				tmp_value = temp_head->value;
				temp_head->name = temp_head->next->name;
				temp_head->value = temp_head->next->value;
				temp_head->next->name = tmp_name;
				temp_head->next->value = tmp_value;
			}
			temp_head = temp_head->next;
		}
		i--;
	}
	return (env);
}

void	printf_env(t_env **env)
{
	t_env *current;

	write(1, "passed/n", 8);
	current = *env;
	sort_env(current);
	while (current != 0)
	{
		if (current->value)
		{
			printf("declare -x %s", current->name);
			printf("%s\n", current->value);
		}
		else
			printf("declare -x %s\n", current->name);
		current = current->next;
	}
}

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

t_env	*env_finder(t_env *env, char *name)
{
	while (env && strcmp(env->name, name))
		env = env->next;
	if (env)
		return (env);
	return (NULL);
}

int	check_is_valid(char *str)
{
	int i;
	i = 1;
	str = receive_name(str);
	if (str[ft_strlen(str) - 1] == '+')
		str = ft_substr(str, 0, ft_strlen(str) - 1);
	if (ft_strlen(str) == 0)
	{
		printf("minishell: export: `%s': not a valid identifier\n", str);
		return (0);
	}
	else if (str[0] == '-')
	{
		printf("minishell: export: -%c: invalid option \n", str[1]);
		printf("export: usage: export [name[=value]...] or export \n");
		return (0);
	}
	else if (str[0] != '_' && !ft_isalpha(str[0]))
    {
        printf("minishell: export: `%s': not a valid identifier\n", str);
		return (0);
    }
	while (str[i] && str[i] != '=')
	{
		if ((!ft_isalpha(str[i]) && !ft_isdigit(str[i]) && str[i] != '_'))
		{
			printf("minishell: export: `%s': not a valid identifier\n", str);
			return (0);
		}
		i++;
	}
	return (1);
}
void	export(t_env **env, t_element *command)
{
	int i = 1;
	t_env *tmp;
	t_env *newelement;

	if (command->nbr_args == 1 || (command->nbr_args == 2
			&& (!ft_strcmp(command->args[1], "#")
				|| !ft_strcmp(command->args[1], ";"))))
	{
		printf_env(env);
		return ;
	}

	while (command->args[i])
	{
		 if (!check_is_valid(command->args[i]))
			return ;
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
							receive_name(command->args[i]))->value = receive_value(command->args[i]);
				else
					ft_lstadd_back(ft_lstnew(command->args[i], 1), env);
			}
		}
		else
		{
			newelement = (t_env *)malloc(sizeof(t_env));
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