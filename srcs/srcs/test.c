/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 13:54:18 by jalevesq          #+#    #+#             */
/*   Updated: 2023/03/23 15:07:28 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int main() {
    int pipe_fd[2];
    int fd_array[10]; // array of file descriptors

    for (int i = 0; i < 10; i++) {
        if (pipe(pipe_fd) == -1) {
            perror("pipe");
            return 1;
        }
        fd_array[i] = pipe_fd[0]; // store read end of pipe in array
        fd_array[++i] = pipe_fd[1]; // store write end of pipe in array
    }

    // now you can use the file descriptors in fd_array to read from and write to the pipes
    // ...

    return 0;
}

       // ls | cat | wc
// pipe 1: 0 1
// pipe 2: 0 1
// pipe 3: 0 1
