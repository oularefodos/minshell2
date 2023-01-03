/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foulare <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 21:32:38 by foulare           #+#    #+#             */
/*   Updated: 2021/11/06 18:39:14 by foulare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t size)
{
	char		*s;
	char		*d;
	size_t		i;

	i = 0;
	d = (char *)dest;
	s = (char *)src;
	if (d > s)
		while (size--)
			d[size] = s[size];
	else
		ft_memcpy(d, s, size);
	return (dest);
}
