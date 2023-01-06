/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakboub <mmakboub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 16:40:03 by mmakboub          #+#    #+#             */
/*   Updated: 2023/01/05 21:20:45 by mmakboub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*ft_lstnew(char *allstr, int flag)
{
	t_env	*newelement;

	newelement = (t_env *)malloc(sizeof(t_env));
	if (newelement == 0)
		return (0);
	if (flag == 1)
		newelement->name = receive_name(allstr);
	else
		newelement->name = receive_name_export(allstr);
	newelement->value = receive_value(allstr);
	newelement->next = NULL;
	return (newelement);
}

void	ft_lstadd_back(t_env *new, t_env **alst)
{
	t_env	*node;

	node = *alst;
	if (alst && *alst)
	{
		while (node && node->next)
		{
			node = node->next;
		}
		node->next = new;
	}
	else
		*alst = new;
}

char	*ft_concatenate(const char *s1, const char *s2, const char *s3)
{
	char	*new_str;
	size_t	j;
	size_t	i;

	if (!s1 || !s2 || !s3)
		return (NULL);
	new_str = (char *)malloc((ft_strlen(s1) + \
			ft_strlen(s2) + ft_strlen(s3) + 1) \
			* sizeof(char));
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		new_str[j++] = s1[i++];
	i = 0;
	while (s2[i])
		new_str[j++] = s2[i++];
	i = 0;
	while (s3[i])
		new_str[j++] = s3[i++];
	new_str[j] = '\0';
	return (new_str);
}

int	ft_isdigit(int x)
{
	if (x >= '0' && x <= '9')
		return (1);
	return (0);
}
