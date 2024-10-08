/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimao <msimao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:52:41 by msimao            #+#    #+#             */
/*   Updated: 2024/09/16 09:55:58 by msimao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_key(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	ft_env(t_data *data, t_cmd *cmd)
{
	int	i;

	i = 0;
	(void)cmd;
	if (cmd->arg_count != 0)
		return (cmd_error(cmd->name, NULL, "too many arguments"));
	while (data->env[i])
	{
		if (is_key(data->env[i]))
		{
			ft_putstr_fd(data->env[i], STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
			i++;
		}
		else
			i++;
	}
	data->exit_code = 0;
}
