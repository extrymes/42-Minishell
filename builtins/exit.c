/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:58:53 by msimao            #+#    #+#             */
/*   Updated: 2024/09/11 13:28:48 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exit(t_cmd *cmd, t_data *data)
{
	int	i;

	i = -1;
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (cmd->arg_count > 1)
	{
		data->exit_code = 127;
		return (cmd_error(cmd->name, NULL, "too many arguments"));
	}
	if (cmd->arg_count == 1)
	{
		while (cmd->arg_lst->data[++i])
		{
			if (!ft_isdigit(cmd->arg_lst->data[i]))
			{
				cmd_error(cmd->name, cmd->arg_lst->data, \
				"numeric argument required");
				data->exit_code = 2;
				exit(2);
			}
		}
		data->exit_code = ft_atoi(cmd->arg_lst->data);
	}
	clear_data(data);
	exit(data->exit_code);
}
