/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:37:15 by msimao            #+#    #+#             */
/*   Updated: 2024/09/06 13:33:41 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	reset_std(t_pipex *pipex)
{
	dup2(pipex->saved_stdout, STDOUT_FILENO);
	dup2(pipex->saved_stdin, STDIN_FILENO);
	close(pipex->saved_stdout);
	close(pipex->saved_stdin);
}

void	set_file(t_pipex *pipex)
{
	pipex->saved_stdout = dup(STDOUT_FILENO);
	pipex->saved_stdin = dup(STDIN_FILENO);
}

void	one_cmd(t_data *data, t_pipex *pipex)
{
	pid_t	pid;

	(void)pipex;
	if (data->entry->cmd_lst->path == NULL)
		return (builtins(data->entry->cmd_lst, data, 0));
	pid = fork();
	if (pid < 0)
		return (ft_putstr_fd("pipe error", 2));
	if (pid == 0)
	{
		// if (pipex->outfile != 0)
		// {
		// 	dup2(pipex->outfile, STDOUT_FILENO);
		// 	close(pipex->outfile);
		// }
		// ft_close(pipex->infile);
		ft_exec(data->entry->cmd_lst, data);
	}
	// ft_close(pipex->outfile);
	// ft_close(pipex->infile);
	waitpid(pid, NULL, 0);
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
