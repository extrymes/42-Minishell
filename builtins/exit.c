/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:58:53 by msimao            #+#    #+#             */
/*   Updated: 2024/09/06 08:46:05 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exit(t_data *data)
{
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	clear_data(data);
	exit(EXIT_SUCCESS);
}
