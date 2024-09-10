/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 11:33:32 by sabras            #+#    #+#             */
/*   Updated: 2024/09/10 13:01:28 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	syntax_error(char *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token '", 2);
	ft_putstr_fd(token, 2);
	ft_putstr_fd("'\n", 2);
}

void	cmd_error(char *cmd, char *arg, char *err)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	if (arg)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(err, 2);
	ft_putstr_fd("\n", 2);
}

void	throw_error(t_data *data, char *err)
{
	ft_putstr_fd(RED "error: ", 2);
	ft_putstr_fd(err, 2);
	ft_putstr_fd("\n" RESET, 2);
	clear_data(data);
	exit(EXIT_FAILURE);
}
