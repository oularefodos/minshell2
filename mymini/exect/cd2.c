/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakboub <mmakboub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 23:23:01 by mmakboub          #+#    #+#             */
/*   Updated: 2023/01/07 23:32:15 by mmakboub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"
void    go_tohome(t_env **env, t_element *cmd)
{
    t_env   *home;
    
    home = finder_getter(&env, "HOME");
    if(!home)
        return (printf("HOME is not seted\n"), (void)0);
    if(chdir(&home->value[1] == 1))
       printf("minishell: cd: %s\n", strerror(errno));
    // else
    //     refresh_oldpwd()
    //     refresh_pwd()
        
}
void	cd22(t_element *command, t_env **env)
{
    // t_env pwd = finder_getter(&env, "PWD");
    
    if(command->nbr_args == 1)
        go_to_home(env, command)
}