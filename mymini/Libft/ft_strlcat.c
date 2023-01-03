/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foulare <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 12:22:53 by foulare           #+#    #+#             */
/*   Updated: 2021/11/10 17:44:53 by foulare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dest, char *src, unsigned int size)
{
	size_t	len;

	len = ft_strlen(dest);
	if (size <= len)
		return (size + ft_strlen(src));
	size -= len + 1;
	while (*src && size > 0 )
	{
		dest[len++] = *(src++);
		size--;
	}
	dest[len] = '\0';
	return (len + ft_strlen(src));
}
