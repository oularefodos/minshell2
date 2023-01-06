/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakboub <mmakboub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 21:24:58 by mmakboub          #+#    #+#             */
/*   Updated: 2023/01/05 21:55:13 by mmakboub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew_list(void *content)
{
	t_list	*newelement;

	newelement = (t_list *)malloc(sizeof(t_list));
	if (newelement == 0)
		return (0);
	newelement -> content = content;
	newelement -> next = 0;
	return (newelement);
}
