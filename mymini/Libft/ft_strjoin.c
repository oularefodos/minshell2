/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakboub <mmakboub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 20:26:29 by foulare           #+#    #+#             */
/*   Updated: 2022/12/30 20:07:10 by mmakboub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_getlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len;
	char	*tab;
	int		i;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	len = ft_getlen(s1) + ft_getlen(s2) + 1;
	tab = (char *)malloc(sizeof(char) * (len));
	if (!tab)
		return (NULL);
	while (s1[i])
	{
		tab[i] = s1[i];
		i++;
	}
	len = 0;
	while (s2[len])
	{
		tab[i] = s2[len];
		i++;
		len++;
	}
	tab[i] = '\0';
	return (tab);
}
