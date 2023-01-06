/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakboub <mmakboub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 21:22:33 by mmakboub          #+#    #+#             */
/*   Updated: 2023/01/06 19:24:55 by mmakboub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_element	*parser(char *line, char **env)
{
	t_element	*ret;

	ret = tokeniser(line);
	if (!ret)
		return (NULL);
	if (grammar(ret, env))
		return (NULL);
	ret = norm_one(ret);
	return (ret);
}
