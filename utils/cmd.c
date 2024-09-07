/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:33:25 by sabras            #+#    #+#             */
/*   Updated: 2024/09/06 08:23:27 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*init_cmd(t_data *data)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (throw_error("malloc failure", data), NULL);
	cmd->name = NULL;
	cmd->path = NULL;
	cmd->arg_lst = NULL;
	cmd->arg_count = 0;
	cmd->outfile = 0;
	cmd->infile = 0;
	cmd->next = NULL;
	data->entry->cmd_count++;
	return (cmd);
}

void	add_cmd(t_entry *entry, t_cmd *cmd)
{
	if (!entry->cmd_lst)
		entry->cmd_lst = cmd;
	else
	{
		while (entry->cmd_lst->next)
			entry->cmd_lst = entry->cmd_lst->next;
		entry->cmd_lst->next = cmd;
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
			throw_error("malloc failure", data);
	}
	else
	{
		cmd->name = ft_strdup(content);
		if (!cmd->name)
			throw_error("malloc failure", data);
		if (!ft_strstr(BUILTINS, cmd->name))
			cmd->path = get_cmd_path(data, content);
	}
}

void	clear_cmd_lst(t_cmd *cmd_lst)
{
	t_cmd	*tmp;

	while (cmd_lst)
	{
		tmp = cmd_lst;
		free(cmd_lst->name);
		free(cmd_lst->path);
		clear_arg_lst(cmd_lst->arg_lst);
		cmd_lst = cmd_lst->next;
		free(tmp);
	}
}
