/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimao <msimao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 11:08:34 by msimao            #+#    #+#             */
/*   Updated: 2024/09/16 15:06:38 by msimao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_close(int fd)
{
	if (fd != 0)
		close(fd);
}

void	clear_fd(int fd1, int fd2)
{
	ft_close(fd1);
	ft_close(fd2);
}

void	error_exec(t_data *data, char *str)
{
	if (str != NULL)
		ft_putstr_fd(str, 2);
	clear_data(data);
	exit(EXIT_FAILURE);
}
