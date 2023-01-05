/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakboub <mmakboub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 00:41:35 by mmakboub          #+#    #+#             */
/*   Updated: 2023/01/05 03:24:51 by mmakboub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(int argc, char* argv[]) {
    int pid = fork();
    if (pid == -1) {
        return 1;
    }
    
    if (pid == 0) {
        int err = execlp("ping", "ping", "-ctr", "3", "google.com", NULL);
        if (err == -1) {
            printf("Could not find program to execute or other error ocurred\n");
            return 2;
        }
    } else {
        
    }
    return 0;
}
