/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 11:11:47 by msimao            #+#    #+#             */
/*   Updated: 2024/09/10 12:23:48 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	set_infile(t_file *file)
{
	int		infile;
	t_file	*tmp;

	tmp = file;
	infile = open(tmp->name, O_RDONLY);
	tmp = tmp->next;
	while (tmp)
	{
		if (tmp->redir == FILE_IN)
			return (close(infile), 0);
		tmp = tmp->next;
	}
	return (infile);
}

int	set_outfile(t_file *file)
{
	int		outfile;
	t_file	*tmp;

	tmp = file;
	if (tmp->redir == FILE_OUT)
		outfile = open(tmp->name, O_TRUNC | O_CREAT | O_RDWR, 0644);
	else
		outfile = open(tmp->name, O_APPEND | O_CREAT | O_RDWR, 0644);
	tmp = tmp->next;
	while (tmp)
	{
		if (tmp->redir == FILE_OUT || tmp->redir == FILE_OUT_APP)
			return (close(outfile), 0);
		tmp = tmp->next;
	}
	return (outfile);
}

void	set_file(t_file *file, t_pipex *pipex)
{
	t_file	*tmp;

	tmp = file;
	pipex->infile = 0;
	pipex->outfile = 0;
	while (tmp)
	{
		if (tmp->redir == FILE_IN)
			pipex->infile = set_infile(tmp);
		else if (tmp->redir == FILE_OUT || tmp->redir == FILE_OUT_APP)
			pipex->outfile = set_outfile(tmp);
		tmp = tmp->next;
	}
	if (pipex->infile != 0)
		dup2(pipex->infile, STDIN_FILENO);
	if (pipex->outfile != 0)
		dup2(pipex->outfile, STDOUT_FILENO);
	ft_close(pipex->infile);
	ft_close(pipex->outfile);
}
