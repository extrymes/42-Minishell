/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:36:25 by msimao            #+#    #+#             */
/*   Updated: 2024/09/13 19:52:25 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exec(t_cmd *cmd, t_data *data)
{
	int		i;
	char	**tab;

	i = 0;
	tab = malloc(sizeof(char *) * (cmd->arg_count + 2));
	if (tab == NULL)
		error_exec(data, NULL);
	tab[0] = ft_strdup(cmd->name);
	if (tab[0] == NULL)
		error_exec(data, NULL);
	while (cmd->arg_count != 0 && cmd->arg_lst)
	{
		tab[i + 1] = ft_strdup(cmd->arg_lst->data);
		if (tab[i + 1] == NULL)
			error_exec(data, NULL);
		cmd->arg_lst = cmd->arg_lst->next;
		i++;
	}
	tab[i + 1] = 0;
	execve(cmd->path, tab, data->env);
	perror("execve");
	exit(EXIT_FAILURE);
}

int	child(t_data *data, t_pipex *pipex, int i)
{
	t_cmd	*cmd;

	if (pipe(pipex->tube) < 0)
		return (perror(NULL), error_exec(data, NULL), 0);
	pipex->pid[i] = fork();
	if (pipex->pid[i] < 0)
		return (perror(NULL), error_exec(data, NULL), 0);
	if (pipex->pid[i] == 0)
	{
		dup2(pipex->tube[1], STDOUT_FILENO);
		cmd = get_cmd_by_id(data->entry->cmd_lst, i);
		free(pipex->pid);
		close(pipex->tube[0]);
		close(pipex->tube[1]);
		close(data->stdout_fd);
		close(data->stdin_fd);
		if (!set_file(cmd->file_lst, pipex, data) || cmd->err != NULL)
			error_exec(data, cmd->err);
		if (cmd->path == NULL)
			builtins(cmd, data, 1);
		ft_exec(cmd, data);
	}
	dup2(pipex->tube[0], STDIN_FILENO);
	return (close(pipex->tube[1]), close(pipex->tube[0]), 1);
}

int	parent(t_data *data, t_pipex *pipex, int i)
{
	t_cmd	*cmd;

	pipex->pid[i] = fork();
	if (pipex->pid[i] < 0)
		return (perror(NULL), error_exec(data, NULL), 0);
	if (pipex->pid[i] == 0)
	{
		free(pipex->pid);
		close(data->stdout_fd);
		close(data->stdin_fd);
		cmd = get_cmd_by_id(data->entry->cmd_lst, i);
		if (!set_file(cmd->file_lst, pipex, data) || cmd->err != NULL)
			error_exec(data, cmd->err);
		if (cmd->path == NULL)
			builtins(cmd, data, 1);
		ft_exec(cmd, data);
	}
	return (1);
}

void	multi_cmd(t_data *data, t_pipex *pipex)
{
	int		i;

	i = 0;
	while (i < data->entry->cmd_count - 1)
	{
		if (!child(data, pipex, i))
			return (free(pipex->pid), error_exec(data, "malloc failure"));
		i++;
	}
	if (!parent(data, pipex, i))
		return (free(pipex->pid), error_exec(data, "malloc failure"));
	stop_process(data, pipex);
}

void	exec_data(t_data *data)
{
	t_pipex	pipex;

	if (data->entry->cmd_count == 0)
		return ;
	pipex.pid = malloc(sizeof(pid_t) * data->entry->cmd_count);
	if (!pipex.pid)
		return (error_exec(data, "malloc failure"));
	handle_signals(1);
	if (data->entry->cmd_count == 1)
		one_cmd(data, &pipex);
	else
	{
		multi_cmd(data, &pipex);
		ft_close(pipex.tube[0]);
		ft_close(pipex.tube[1]);
	}
	reset_std(data);
	handle_signals(0);
	if (pipex.pid)
		free(pipex.pid);
	return ;
}
