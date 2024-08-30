/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:37:15 by msimao            #+#    #+#             */
/*   Updated: 2024/08/30 19:29:21 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_close(int fd)
{
	if (fd != 0)
		close(fd);
}

void	set_file(t_entry *entry, t_pipex *pipex)
{
	if (entry->outfile != 0)
		pipex->outfile = entry->outfile;
	else
		pipex->outfile = 0;
	if (entry->infile != 0)
	{
		pipex->infile = entry->infile;
		dup2(pipex->infile, STDIN_FILENO);
	}
	else
		pipex->infile = 0;

}

void	one_cmd(t_entry *entry, t_pipex *pipex, char **envp)
{
	pid_t	pid;
	char	**cmd;

	pid = fork();
	if (pid < 0)
	{
		ft_putstr_fd("pipe error", 2);
		return ;
	}
	if (pid == 0)
	{
		if (pipex->outfile != 0)
		{
			dup2(pipex->outfile, STDOUT_FILENO);
			close(pipex->outfile);
		}
		ft_close(pipex->infile);
		if (1)
			builtins(entry->cmd_lst, entry, envp); // strncmp path builtins
		ft_exec(entry->cmd_lst, envp, entry);
	}
	ft_close(pipex->outfile);
	ft_close(pipex->infile);
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
