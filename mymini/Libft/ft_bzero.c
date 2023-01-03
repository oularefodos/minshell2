/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foulare <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 10:38:19 by foulare           #+#    #+#             */
/*   Updated: 2021/11/02 10:43:05 by foulare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *pointer, size_t count)
{
	unsigned char	*str;
	unsigned int	i;

	i = 0;
	str = (unsigned char *)pointer;
	while (i < count)
	{
		str[i] = 0;
		i++;
	}
}
