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
		perror("Error");
	else if (printf("%s\n", path) != ft_strlen(path) + 1)
		perror("Error");
	free(path);
}
