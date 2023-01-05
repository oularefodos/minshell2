/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakboub <mmakboub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 01:21:19 by mmakboub          #+#    #+#             */
/*   Updated: 2023/01/05 02:33:52 by mmakboub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>
#include<signal.h>
#include "minishell.h"
  
// void    all_lower(char *cmd)
// {
// 	int	i;

// 	i = 0;
// 	while (cmd[i++])
// 		cmd[i] = ft_tolower(cmd[i]);
// }
// int main()
// {
//     char cmd[10] = "mariaHHJm";
//     all_lower(cmd);
//     return 0;
// }
char *put_my_shlvl(char *str)
{
    return (ft_substr(str, \
			ft_strlen(str) - ft_strlen(ft_strchr(str, '=') + 1), \
			ft_strlen(str)));
}
int main()
{
    char cmd[10] = "ma=riaHHJm";
    printf("%s\n",put_my_shlvl(cmd));
    return 0;
}

