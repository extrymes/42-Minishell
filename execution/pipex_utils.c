/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:37:15 by msimao            #+#    #+#             */
/*   Updated: 2024/09/11 14:59:37 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	reset_std(t_data *data)
{
	dup2(data->stdout_fd, STDOUT_FILENO);
	dup2(data->stdin_fd, STDIN_FILENO);
}

void	stop_process(t_data *data, t_pipex *pipex)
{
	int	i;
	int	exit_status;

	i = 0;
	while (i < data->entry->cmd_count)
	{
		if (waitpid(pipex->pid[i++], &exit_status, 0) > 0 \
			&& WIFEXITED(exit_status))
			data->exit_code = WEXITSTATUS(exit_status);
	}
}

void	one_cmd(t_data *data, t_pipex *pipex)
{
	if (!set_file(data->entry->cmd_lst->file_lst, pipex)
		|| data->entry->cmd_lst->err != NULL)
		return (ft_putstr_fd(data->entry->cmd_lst->err, 2));
	if (data->entry->cmd_lst->path == NULL)
	{
		if (data->entry->cmd_lst->name
			&& ft_strncmp(data->entry->cmd_lst->name, "exit", 4) == 0)
		{
			free(pipex->pid);
			pipex->pid = NULL;
		}
		return (builtins(data->entry->cmd_lst, data, 0));
	}
	pipex->pid[0] = fork();
	if (pipex->pid[0] < 0)
		return (ft_putstr_fd("pipe error", 2));
	if (pipex->pid[0] == 0)
	{
		free(pipex->pid);
		ft_close(data->stdin_fd);
		ft_close(data->stdout_fd);
		ft_exec(data->entry->cmd_lst, data);
	}
	stop_process(data, pipex);
}

t_cmd	*get_cmd_by_id(t_cmd *cmd_lst, int id)
{
	int	i;

	i = 0;
	while (cmd_lst && i < id)
	{
		cmd_lst = cmd_lst->next;
		i++;
	}
	return (cmd_lst);
}
