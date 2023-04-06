/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 10:47:01 by jalevesq          #+#    #+#             */
/*   Updated: 2023/04/06 12:57:33 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_pwd(void)
{
	char pwd[1024];

	if (getcwd(pwd, sizeof(pwd)) == NULL) {
        perror("getcwd");
	}
	printf("%s\n", pwd);
}