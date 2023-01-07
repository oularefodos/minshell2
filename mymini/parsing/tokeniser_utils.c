/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakboub <mmakboub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 21:22:43 by mmakboub          #+#    #+#             */
/*   Updated: 2023/01/07 01:25:39 by mmakboub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	str_tokeniser(char **str, t_element **elmnt, int *len)
{
	char	*line;

	line = *str;
	while (!issep(*line, "<>|'\"") && *line)
	{
		(*len)++;
		line++;
	}
	add_back(elmnt, line, CMD, *len);
	*len = 0;
	*str = line;
}

void	squote_tokeniser(char **str, t_element **elmnt, int *len)
{
	char	*line;
	int		c;
	int		s;
	int		type;

	line = *str;
	c = *line;
	if (c == '\'')
		type = SQUOT;
	else
		type = DQUOT;
	if (*(line - 1) == 32)
		s = 1;
	else
		s = 0;
	line++;
	(*len)++;
	while (*line != c && *(line++))
		(*len)++;
	line++;
	(*len)++;
	add_back(elmnt, line, type, *len);
	last(*elmnt)->space = s;
	*len = 0;
	*str = line;
}

void	redir_tokeniser(char **str, t_element **elmnt, int *len)
{
	char	*line;
	int		c;

	line = *str;
	c = *line;
	*len = 1;
	line++;
	if (*line == c)
	{
		*len = 2;
		line++;
	}
	if (c == '<')
	{
		if (*len == 1)
			add_back(elmnt, NULL, INF, *len);
		else if (*len == 2)
			add_back(elmnt, NULL, HERDOC, *len);
	}
	else
	{
		if (*len == 1)
			add_back(elmnt, NULL, SUP, *len);
		else if (*len == 2)
			add_back(elmnt, NULL, ADD, *len);
	}
	*len = 0;
	*str = line;
}
