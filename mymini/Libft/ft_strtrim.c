/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foulare <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 12:53:17 by foulare           #+#    #+#             */
/*   Updated: 2021/11/10 18:39:45 by foulare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include "libft.h"

static int	ft_isset(char const *set, char c)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_equal(void)
{
	char	*tab;

	tab = (char *)malloc(sizeof(char) * 1);
	tab[0] = '\0';
	return (tab);
}

int	ft_getfirstindex(char const *str, char const *set)
{
	int	i;

	i = 0;
	while (ft_isset(set, str[i]))
		i++;
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		i;
	int			y;
	char		*tab;
	size_t		len;

	y = 0;
	if (!set)
		return ((char *)s1);
	if (!s1)
		return (0);
	len = ft_strlen(s1);
	i = ft_getfirstindex(s1, set);
	if (i == len)
		return (ft_equal());
	len--;
	while (ft_isset(set, s1[len]))
		len--;
	tab = (char *)malloc(sizeof(char) * (len - i + 2));
	if (!tab)
		return (NULL);
	while (i <= len)
		tab[y++] = s1[i++];
	tab[y] = '\0';
	return (tab);
}
