/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foulare <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 13:07:32 by foulare           #+#    #+#             */
/*   Updated: 2021/11/06 18:36:36 by foulare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*prec;

	if (!lst)
		return (0);
	while (lst)
	{
		prec = lst;
		lst = lst -> next;
	}
	return (prec);
}
