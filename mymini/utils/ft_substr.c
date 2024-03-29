/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakboub <mmakboub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 20:47:14 by mmakboub          #+#    #+#             */
/*   Updated: 2023/01/07 06:49:25 by mmakboub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len, int type)

{
	size_t	firstc;
	char	*newstr;

	firstc = 0;
	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
	{
		newstr = ft_malloc(1, type);
		if (!newstr)
			return (NULL);
		newstr[0] = '\0';
		return (newstr);
	}
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	newstr = (char *)ft_malloc(sizeof(char) * (len + 1), type);
	while (firstc < len && start < ft_strlen(s))
	{
		newstr[firstc++] = s[start++];
	}
	newstr[firstc] = '\0';
	return (newstr);
}
