/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakboub <mmakboub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 18:54:30 by mmakboub          #+#    #+#             */
/*   Updated: 2022/12/31 18:00:31 by mmakboub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void handle_pipe(t_element *node, t_env **env)
{
    int fd[2];
    int i = 0;
    int argc = ft_lstsize_elem(node);
    // printf("lol\n");
    int in_tmp = dup(0);   
    while (node != NULL)
    {
        if(node->next)
        {
            if (pipe(fd) == -1)
                exit(1);
        }
        pid_t pid = fork();
        if (pid == 0)
        {

            // rediction
            /*

                void open_file_add(char *file_name)
                {
                    int fd;

                    fd = open(file_name, O_RONLY);
                    if (fd < 0)
                        return ;
                    
                    dup2(fd, 1);
                }

                cat < file >> file2

                cat
                file < (read in)
                file2 >> (APPEND)
            
                if (command->type = ADD)
                {
                    open_file_add(file_name);
                }
            */
            if (node->next) {
                if (dup2(fd[1],1) == -1)
                {
                    perror("lol1");
                }
                close(fd[1]);
                close(fd[0]);
            }
            if(check_builtings(node))
		    	is_builting(node, env);
		    else
            {
                
		    	execve_cmd(node, env, node->args);
            }
            exit(0);
        }
        if (node->next)
        {
            if (dup2(fd[0],0) == -1)
            {
                perror("lol2");
            }
            close(fd[1]);
            close(fd[0]);
        }
        i++;
        node = node->next;
        if (node && node->type == PIPE)
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

