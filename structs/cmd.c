/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:33:25 by sabras            #+#    #+#             */
/*   Updated: 2024/09/10 13:08:04 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*init_cmd(t_data *data)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		throw_error(data, "malloc failure");
	cmd->name = NULL;
	cmd->path = NULL;
	cmd->arg_lst = NULL;
	cmd->arg_count = 0;
	cmd->file_lst = NULL;
	cmd->next = NULL;
	add_cmd(data->entry, cmd);
	return (cmd);
}

void	add_cmd(t_entry *entry, t_cmd *cmd)
{
	t_cmd	*tmp;

	if (!entry->cmd_lst)
		entry->cmd_lst = cmd;
	else
	{
		tmp = entry->cmd_lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = cmd;
	}
	entry->cmd_count++;
}

void	set_cmd_data(t_data *data, t_cmd *cmd, char *content)
{
	if (ft_strchr(content, '/'))
	{
		cmd->name = get_cmd_name(data, content);
		cmd->path = ft_strdup(content);
		if (!cmd->path)
			throw_error(data, "malloc failure");
	}
	else
	{
		cmd->name = ft_strdup(content);
		if (!cmd->name)
			throw_error(data, "malloc failure");
		if (!ft_strstr(BUILTINS, cmd->name))
			cmd->path = get_cmd_path(data, content);
		else
			cmd->path = NULL;
	}
}

void	clear_cmd_lst(t_cmd *cmd_lst)
{
	t_cmd	*cmd;

	while (cmd_lst)
	{
		cmd = cmd_lst;
		if (cmd->name)
			free(cmd->name);
		if (cmd->path)
			free(cmd->path);
		clear_arg_lst(cmd->arg_lst);
		clear_file_lst(cmd->file_lst);
		cmd_lst = cmd_lst->next;
		free(cmd);
	}
}
