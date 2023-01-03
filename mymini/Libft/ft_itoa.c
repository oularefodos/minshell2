/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foulare <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 14:49:58 by foulare           #+#    #+#             */
/*   Updated: 2021/11/04 18:31:20 by foulare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include "libft.h"

int	ft_getlen(int n)
{
	long int	nb;
	int			i;

	nb = n;
	i = 1;
	if (nb < 0)
	{
		i++;
		nb = nb * -1;
	}
	while (nb >= 10)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char		*str;
	long int	nb;
	int			len;	

	len = ft_getlen(n);
	nb = n;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	if (nb < 0)
	{
		nb = nb * -1;
		str[0] = '-';
	}
	str[len] = 0;
	len--;
	while (nb >= 10)
	{
		str[len] = (nb % 10) + 48;
		nb = nb / 10;
		len--;
	}
	str[len] = nb + 48;
	return (str);
}
