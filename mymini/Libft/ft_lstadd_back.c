/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakboub <mmakboub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 22:01:32 by mmakboub          #+#    #+#             */
/*   Updated: 2023/01/03 16:34:29 by mmakboub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back_list(t_list **alst, t_list *new)
{
	t_list	*node;

	node = *alst;
	if (alst && *alst)
	{
		while (node -> next)
		{
			node = node -> next;
		}
			node -> next = new;
	}
	else
		*alst = new;
}
