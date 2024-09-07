/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 15:09:29 by sabras            #+#    #+#             */
/*   Updated: 2024/09/07 01:15:19 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_echo(t_cmd *cmd)
{
	int		is_n;
	t_arg	*tmp;

	is_n = 0;
	tmp = cmd->arg_lst;
	if (cmd->arg_count == 0)
		return (ft_putchar_fd('\n', STDOUT_FILENO));
	if (tmp->data && tmp->data[0] == '-'
		&& tmp->data[1] == 'n')
	{
		is_n = 1;
		tmp = tmp->next;
	}
	while (tmp)
	{
		ft_putstr_fd(tmp->data, STDOUT_FILENO);
		tmp = tmp->next;
		if (tmp)
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (is_n != 1)
		ft_putchar_fd('\n', STDOUT_FILENO);
}
