/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:58:53 by msimao            #+#    #+#             */
/*   Updated: 2024/09/14 15:37:40 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	exit_error(t_cmd *cmd, t_data *data)
{
	cmd_error(cmd->name, cmd->arg_lst->data, \
	"numeric argument required");
	data->exit_code = 2;
	clear_data(data);
	exit(2);
}

void	ft_exit(t_cmd *cmd, t_data *data)
{
	int	i;

	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (cmd && cmd->arg_count > 1)
		return (data->exit_code = 127,
			cmd_error(cmd->name, NULL, "too many arguments"));
	if (cmd && cmd->arg_count == 1)
	{
		if (!ft_isdigit(cmd->arg_lst->data[0])
			&& cmd->arg_lst->data[0] != '+' && cmd->arg_lst->data[0] != '-')
			exit_error(cmd, data);
		i = 1;
		while (ft_isdigit(cmd->arg_lst->data[i]))
			i++;
		if (cmd->arg_lst->data[i] && !ft_isdigit(cmd->arg_lst->data[i]))
			exit_error(cmd, data);
		data->exit_code = ft_atoi(cmd->arg_lst->data);
	}
	clear_data(data);
	if (data->exit_code < 0)
		exit(256 + data->exit_code);
	exit(data->exit_code);
}
