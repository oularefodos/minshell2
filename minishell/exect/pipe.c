/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakboub <mmakboub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 18:54:30 by mmakboub          #+#    #+#             */
/*   Updated: 2023/01/02 17:50:31 by mmakboub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void handle_pipe(t_element *node, t_env **env)
{
    int fd[2];
    int i = 0;
    int argc = ft_lstsize_elem(node);
    char **envv;
    int in_tmp = dup(0);

    envv = convertto_doublep(*env);   
    while (node != NULL)
    {
        if(i < argc - 1)
        {
            if (pipe(fd) == -1)
                exit(1);
        }
        pid_t pid = fork();
        if (pid == 0)
        {
            if (i < argc - 1) {
                if (dup2(fd[1],1) == -1)
                {
                    perror("lol1");
                }
                close(fd[1]);
                close(fd[0]);
            }
            expender(node, envv);
            if (node->args[0]){
                if(check_builtings(node))
                    is_builting(node, env);
                else
                    execve_cmd(node, env, node->args);
            }
            exit(0);
        }
        if (i < argc - 1)
        {
            if (dup2(fd[0],0) == -1)
            {
                perror("lol2");
            }
            close(fd[1]);
            close(fd[0]);
        }
        i++;
        while (node && node->type != PIPE)
            node = node->next;
        if (node)
            node = node->next;
    }
    dup2(in_tmp, 0);
    close(in_tmp);
    close(fd[0]);
    close(fd[1]);
    i = 0;
    while (i < argc)
    {
        wait(NULL);
        i++;
    }
}

