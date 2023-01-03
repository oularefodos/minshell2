/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foulare <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 13:38:14 by foulare           #+#    #+#             */
/*   Updated: 2021/11/04 18:11:35 by foulare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_memcmp(const void *point1, const void *point2, size_t size)
{
	size_t			i;
	unsigned int	p;
	unsigned char	*s1;
	unsigned char	*s2;

	i = 0;
	p = 0;
	s1 = (unsigned char *)point1;
	s2 = (unsigned char *)point2;
	while (p == 0 && i < size)
	{
		if (s1[i] != s2[i])
			p = s1[i] - s2[i];
		i++;
	}
	return (p);
}
