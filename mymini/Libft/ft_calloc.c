/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foulare <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 16:49:37 by foulare           #+#    #+#             */
/*   Updated: 2021/11/09 15:34:12 by foulare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t nelem, size_t elsize)
{
	char			*str;
	unsigned int	i;

	i = 0;
	if (nelem == 0 || elsize == 0)
	{
		nelem = 1;
		elsize = 1;
	}
	str = (char *)malloc(nelem * elsize);
	if (str)
	{
		while (i < nelem * elsize)
		{
			str[i] = 0;
			i++;
		}
	}
	return (str);
}
