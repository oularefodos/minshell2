/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foulare <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 19:55:37 by foulare           #+#    #+#             */
/*   Updated: 2021/11/15 20:02:49 by foulare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdlib.h>

char	*ft_nostart(void)
{
	char	*s;

	s = (char *)malloc(sizeof(char) * 1);
	s[0] = 0;
	return (s);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;
	int		i;

	i = 0;
	if (!s)
		return (0);
	if (start > ft_strlen(s))
		return (ft_nostart());
	if (len > ft_strlen(s) - start)
		dest = (char *)malloc(sizeof(char) * (ft_strlen(s) - start + 1));
	else
		dest = (char *)malloc(len + 1);
	if (!dest)
		return (NULL);
	while (s[start] && len > 0 && (start < ft_strlen(s)))
	{
		dest[i] = s[start];
		start++;
		i++;
		len--;
	}
	dest[i] = '\0';
	return (dest);
}
