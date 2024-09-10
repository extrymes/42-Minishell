/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 11:08:34 by msimao            #+#    #+#             */
/*   Updated: 2024/09/09 12:16:24 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_close(int fd)
{
	if (fd != 0)
		close(fd);
}

// void	clear_fd(t_file *file)
// {
// 	t_file	*tmp;

// 	tmp = file;
// 	while (tmp)
// 	{
// 		ft_close(tmp->name);
// 		tmp = tmp->next;
// 	}
// }

void	error_exec(t_data *data, char *str)
{
	if (str != NULL)
		ft_putstr_fd(str, 2);
	clear_data(data);
	exit(EXIT_FAILURE);
}
