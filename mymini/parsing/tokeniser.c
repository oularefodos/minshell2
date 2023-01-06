/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakboub <mmakboub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 21:22:51 by mmakboub          #+#    #+#             */
/*   Updated: 2023/01/05 21:47:49 by mmakboub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_element	*last(t_element *s)
{
	t_element	*c;

	c = s;
	while (c->next)
		c = c->next;
	return (c);
}

int	issep(char c, char *sep)
{
	int	i;

	i = 0;
	while (sep[i])
	{
		if (c == sep[i])
			return (1);
		i++;
	}
	return (0);
}

t_element	*new_element(int type, char *str, t_element *prev)
{
	t_element	*new;

	new = malloc(sizeof(t_element));
	if (!new)
	{
		free(str);
		return (NULL);
	}
	new->type = type;
	if (type == SQUOT || type == DQUOT)
	{
		new->args = malloc(sizeof(char *) * 2);
		if (!new)
			exit(1);
		new->args[0] = ft_strdup(str);
		new->args[1] = 0;
	}
	else
		new->args = ft_split(str, ' ');
	new->next = NULL;
	new->prev = prev;
	free(str);
	return (new);
}

void	add_back(t_element **node, char *str, int type, int len)
{
	char		*s;
	t_element	*lst;

	if ((type == CMD || type == SQUOT || type == DQUOT) && str)
		s = ft_substr(str - len, 0, len);
	else
		s = NULL;
	if (*node == NULL)
		*node = new_element(type, s, NULL);
	else
	{
		lst = last(*node);
		lst->next = new_element(type, s, lst);
	}
}

t_element	*tokeniser(char *line)
{
	t_element	*elmnt;
	int			len;

	elmnt = NULL;
	while (*line)
	{
		len = 0;
		while (*line == ' ')
			line++;
		if (*line == '\0')
			break ;
		if (!issep(*line, "<>|'\""))
			str_tokeniser(&line, &elmnt, &len);
		else if (*line == '\'' || *line == '"')
		{
			squote_tokeniser(&line, &elmnt, &len);
			if (*line == '\0')
				break ;
		}
		else if (*line == '<' || *line == '>')
			redir_tokeniser(&line, &elmnt, &len);
		else if (*(line++) == '|')
			add_back(&elmnt, NULL, PIPE, len);
	}
	return (elmnt);
}
