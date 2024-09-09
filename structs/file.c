/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 10:25:06 by sabras            #+#    #+#             */
/*   Updated: 2024/09/09 10:54:59 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_file	*init_file(t_data *data, char *content, int redir)
{
	t_file	*file;

	file = malloc(sizeof(t_file));
	if (!file)
		return (throw_error("malloc failure", data), NULL);
	file->name = alloc_str(data, content);
	file->redir = redir;
	file->next = NULL;
	return (file);
}

void	add_file(t_data *data, t_cmd *cmd, char *content, int redir)
{
	t_file	*file;
	t_file	*tmp;

	file = init_file(data, content, redir);
	if (!cmd->file_lst)
		cmd->file_lst = file;
	else
	{
		tmp = cmd->file_lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = file;
	}
}

void	clear_file_lst(t_file *file_lst)
{
	t_file	*file;

	while (file_lst)
	{
		file = file_lst;
		free(file->name);
		file_lst = file_lst->next;
		free(file);
	}
}
