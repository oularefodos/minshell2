/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakboub <mmakboub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 15:55:23 by mmakboub          #+#    #+#             */
/*   Updated: 2022/12/31 01:07:25 by mmakboub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void	pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path == NULL)
		printf("getcwd couldn't find the pwd");
	else
		printf("%s\n", path);
	free(path);
}
