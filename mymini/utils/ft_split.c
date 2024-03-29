/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakboub <mmakboub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 18:34:00 by mmakboub          #+#    #+#             */
/*   Updated: 2023/01/06 23:56:38 by mmakboub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	ft_total(char const *s, char c)
{
	size_t	n_wrd;

	n_wrd = 0;
	while (*s)
	{
		if (*s != c)
		{
			n_wrd++;
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	return (n_wrd);
}

static char	**ft_free(char **str, int c)
{
	while (c--)
	{
		free(str[c--]);
	}
	free(str);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	len;
	char	**str;

	i = 0;
	if (!s)
		return (NULL);
	str = (char **)ft_malloc(sizeof(char *) * (ft_total(s, c) + 1), 1);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		len = 0;
		while (s[len] && s[len] != c)
			len++;
		if (len != 0)
			str[i++] = ft_substr(s, 0, len, 1);
		if (len != 0 && !str[i - 1])
			return (ft_free(str, i - 1));
		s += len;
	}
	str[i] = NULL;
	return (str);
}
