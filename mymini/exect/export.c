/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakboub <mmakboub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 11:05:55 by mmakboub          #+#    #+#             */
/*   Updated: 2022/12/18 20:39:00 by mmakboub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int check_caract(char *str, char c)
{
    int i = 1;
    if(!str)
        return(0);
    while(str[i])
    {
        if(str[i] == c)
            return(1);
        i++;
    }
    return(0);
}
int check_plus(char *str, char c, char x)
{
    if (!str)
        return(0);
    int i = 0;
    while(str[i] && str[i + 1])
    {
        if(str[i] == c && str[i + 1] == x)
            return(1);
        i++;
    }
    return(0);
}
void	printf_env(t_env **env)
{
	t_env *current = *env;
	while (current != 0)
	{
        if(current->value)
        {
		    printf("declare -x %s", current->name);
            printf("=%s\n",current->value);
        }
        else
             printf("declare -x %s\n", current->name);
		current = current->next;
	}
}

char *receive_name_export(char *allstr)
{
    return(ft_substr(allstr, 0, strlen(allstr) - strlen(strchr(allstr, '+'))));
}

char *receive_value_export(char *allstr)
{
     return(ft_substr(allstr, strlen(allstr) - strlen(strchr(allstr, '=')) + 1, strlen(allstr)));
}
t_env	*env_finder(t_env	*env, char *name)
{
	while(env && strcmp(env->name, name))
		env = env->next;
	if(env)
		return(env);
	return(NULL);
}

int check_is_valid(char *str)
{
    int i;
    i= 0;
    str = receive_name(str);
	if (str[ft_strlen(str) - 1] == '+')
        str = ft_substr(str, 0, ft_strlen(str) - 1);
    if(ft_strlen(str) == 0)
    {
        printf("minishell: export: `%s': not a valid identifier\n", str);
        return 0;
    }
    if (str[0] == '-')
	{
		printf("minishell: export: -%c: invalid option \n", str[1]);
		printf("export: usage: export [name[=value]...] or export \n");
        return 0;
	}
    while(str[i])
    {
        if ((!ft_isalpha(str[i])))
        {
            printf("minishell: export: `%s': not a valid identifier\n", str);
            return 0;
        }
        i++;
    }
    return 1;
}

void export(t_env **env, t_element *command)
{
    int i = 1;
    t_env *tmp;
    t_env	*newelement;
    if(command->nbr_args == 1 || (command->nbr_args == 2 && (!ft_strcmp(command->args[1], "#") || !ft_strcmp(command->args[1], ";" ))))
    {
        printf_env(env);
        return ;
    }
    while(command->args[i])
    {
        if (!check_is_valid(command->args[i]))
           return;
        if(check_caract(command->args[i], '=') == 1)
        {
            if(check_plus(command->args[i], '+', '='))
            {
                if(env_finder(*env,receive_name_export(command->args[i])))
                {
                    tmp = env_finder(*(env),receive_name_export(command->args[i]));
                    if (tmp->value)
                        tmp->value = ft_strjoin(tmp->value, receive_value_export(command->args[i]));
                    else
                        tmp->value = receive_value_export(command->args[i]); 
                }
                else
                    ft_lstadd_back(ft_lstnew(command->args[i], 2), env);
            }
            else
            {
                if(env_finder(*env,receive_name(command->args[i])))
                    env_finder(*env,receive_name(command->args[i]))->value = receive_value(command->args[i]);
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
            ft_lstadd_back(newelement, env);
        }
        i++;
    }
}


//still trsiting first condition case it should not add the argument to exportand and handled errors;