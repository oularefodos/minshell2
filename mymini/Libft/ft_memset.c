/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foulare <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 12:15:02 by foulare           #+#    #+#             */
/*   Updated: 2021/11/02 12:18:01 by foulare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memset(void *pointer, int value, size_t count)
{
	unsigned char	*str;
	unsigned int	i;

	i = 0;
	str = (unsigned char *)pointer;
	while (i < count)
	{
		str[i] = (unsigned char)value;
		i++;
	}
	return (pointer);
}
