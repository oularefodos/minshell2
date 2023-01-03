/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foulare <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 12:00:27 by foulare           #+#    #+#             */
/*   Updated: 2021/11/06 19:08:35 by foulare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *full, const char *subs, size_t len)
{
	unsigned int	i;
	unsigned int	y;

	i = 0;
	if (!*subs)
		return ((char *)full);
	while (full[i] && len != 0)
	{
		y = 0;
		while (subs[y] == full[i + y] && subs[y] && y < len)
			y++;
		if (subs[y] == '\0')
			return ((char *)&full[i]);
		i++;
		len--;
	}
	return (0);
}
