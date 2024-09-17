/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 11:11:47 by msimao            #+#    #+#             */
/*   Updated: 2024/09/17 13:52:42 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	set_infile(t_file *file, t_pipex *pipex)
{
	t_file	*tmp;

	pipex->infile = 0;
	tmp = file;
	if (access(tmp->name, F_OK) != 0)
		return (cmd_error(tmp->name, NULL, "No such file or directory"), 1);
	pipex->infile = open(tmp->name, O_RDONLY);
	if (pipex->infile < 0)
		return (cmd_error(tmp->name, NULL, "Permission denied"), 1);
	if (pipex->infile != 0)
	{
		if (dup2(pipex->infile, STDIN_FILENO) < 0)
			return (perror("dup2"), 1);
	}
	ft_close(pipex->infile);
	return (0);
}

static int	set_outfile(t_file *file)
{
	int		outfile;
	t_file	*tmp;

	tmp = file;
	outfile = 0;
	if (tmp->redir == FILE_OUT)
		outfile = open(tmp->name, O_TRUNC | O_CREAT | O_RDWR, 0644);
	else
		outfile = open(tmp->name, O_APPEND | O_CREAT | O_RDWR, 0644);
	if (outfile < 0)
		return (cmd_error(tmp->name, NULL, "Permission denied"), 1);
	if (outfile != 0)
	{
		if (dup2(outfile, STDOUT_FILENO) < 0)
			return (perror("dup2"), 1);
		ft_close(outfile);
	}
	return (0);
}

static void	destroy_heredoc(t_file *file)
{
	t_file	*tmp;

	tmp = file;
	while (tmp)
	{
		if (tmp->redir == HERE_DOC)
			unlink(tmp->name);
		tmp = tmp->next;
	}
}

int	set_file(t_file *file, t_pipex *pipex, t_data *data)
{
	t_file	*tmp;
	int		infile;
	int		outfile;

	tmp = file;
	infile = 0;
	outfile = 0;
	while (tmp)
	{
		if (tmp->redir == FILE_IN || tmp->redir == HERE_DOC)
			infile = set_infile(tmp, pipex);
		else if (tmp->redir == FILE_OUT || tmp->redir == FILE_OUT_APP)
			outfile = set_outfile(tmp);
		if (infile > 0 || outfile > 0)
			return (data->exit_code = 1, 0);
		tmp = tmp->next;
	}
	destroy_heredoc(file);
	return (1);
}
