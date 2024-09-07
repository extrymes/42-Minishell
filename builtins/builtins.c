/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:23:54 by msimao            #+#    #+#             */
/*   Updated: 2024/09/06 15:57:56 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int		is_built(t_cmd *cmd)
// {
// 	if (ft_strncmp(cmd->name, "exit", 4) == 0)
// 		return (1);
// 	return (0);
// }

// int		check_exit(t_data *data)
// {
// 	t_cmd *tmp;
// 	int	i;

// 	i = 0;
// 	tmp = data->entry->cmd_lst;
// 	while (tmp)
// 	{
// 		if (is_built(tmp) == 1)
// 		{
// 			if (data->entry->cmd_count == 1)
// 				builtins(tmp, data, 0);
// 			else if (data->entry->cmd_count != 1 && i < 1)
// 				return (1);
// 			else
// 				return (0);
// 		}
// 		i++;
// 		tmp = tmp->next;
// 	}
// 	return (1);
// }

void	builtins(t_cmd *cmd, t_data *data, int in_fork)
{
	if (ft_strncmp(cmd->name, "echo", 4) == 0)
		ft_echo(cmd); //faiss
	else if (ft_strncmp(cmd->name, "pwd", 3) == 0)
		ft_pwd(data); //fais
	else if (ft_strncmp(cmd->name, "env", 3) == 0)
		ft_env(data); //fais
	else if (ft_strncmp(cmd->name, "cd", 2) == 0)
		ft_cd(cmd, data);//fais
	else if (ft_strncmp(cmd->name, "exit", 4) == 0)
		ft_exit(data);//fais
	else if (ft_strncmp(cmd->name, "export", 6) == 0)
		ft_export(cmd, data); //fais
	else if (ft_strncmp(cmd->name, "unset", 5) == 0)
		ft_unset(cmd, data); //fais
	else
		return ;
	if (in_fork == 1)
	{
		clear_data(data);
		exit(EXIT_SUCCESS);
	}
}
