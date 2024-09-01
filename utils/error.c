/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 11:33:32 by sabras            #+#    #+#             */
/*   Updated: 2024/08/31 10:55:36 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	throw_error(char *error, t_data *data)
{
	ft_putstr_fd(RED "error: ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n" RESET, 2);
	clear_data(data);
	exit(EXIT_FAILURE);
}
