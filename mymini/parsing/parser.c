/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakboub <mmakboub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 21:22:33 by mmakboub          #+#    #+#             */
/*   Updated: 2023/01/05 21:59:49 by mmakboub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_element	*parser(char *line)
{
	t_element	*ret;

	ret = tokeniser(line);
	if (!ret)
		return (NULL);
	if (grammar(ret))
		return (NULL);
	// free temp
	ret = norm_one(ret);
	return (ret);
}
