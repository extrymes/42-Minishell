/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 15:09:29 by sabras            #+#    #+#             */
/*   Updated: 2024/09/14 10:57:14 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_flag(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '-')
		return (0);
	i++;
	while (str[i])
	{
		if (str[i++] != 'n')
			return (0);
	}
	return (1);
}

void	ft_echo(t_data *data, t_cmd *cmd)
{
	int		is_n;
	t_arg	*tmp;

	is_n = 0;
	tmp = cmd->arg_lst;
	if (cmd->arg_count == 0)
		return (ft_putchar_fd('\n', STDOUT_FILENO));
	while (tmp && is_flag(tmp->data))
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
	data->exit_code = 0;
}
