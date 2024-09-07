/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 11:08:34 by msimao            #+#    #+#             */
/*   Updated: 2024/09/03 09:17:15 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_close(int fd)
{
	if (fd != 0)
		close(fd);
}

void	error_exec(t_data *data)
{
	clear_data(data);
	ft_putstr_fd("malloc failed", 2);
	exit(EXIT_FAILURE);
}
