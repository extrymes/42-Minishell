/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:23:54 by msimao            #+#    #+#             */
/*   Updated: 2024/09/11 13:37:42 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	builtins(t_cmd *cmd, t_data *data, int in_fork)
{
	if (cmd->name == NULL)
		return ;
	else if (ft_strncmp(cmd->name, "echo", 4) == 0)
		ft_echo(data, cmd);
	else if (ft_strncmp(cmd->name, "pwd", 3) == 0)
		ft_pwd(data);
	else if (ft_strncmp(cmd->name, "env", 3) == 0)
		ft_env(data);
	else if (ft_strncmp(cmd->name, "cd", 2) == 0)
		ft_cd(cmd, data);
	else if (ft_strncmp(cmd->name, "exit", 4) == 0)
		ft_exit(cmd, data);
	else if (ft_strncmp(cmd->name, "export", 6) == 0)
		ft_export(cmd, data);
	else if (ft_strncmp(cmd->name, "unset", 5) == 0)
		ft_unset(cmd, data);
	if (in_fork == 1)
	{
		clear_data(data);
		exit(EXIT_SUCCESS);
	}
}
