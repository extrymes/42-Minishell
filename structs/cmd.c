/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:33:25 by sabras            #+#    #+#             */
/*   Updated: 2024/09/09 10:55:04 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	find_name_path(t_data *data, t_cmd *cmd, char *content);

t_cmd	*init_cmd(t_data *data, char *content)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (throw_error("malloc failure", data), NULL);
	find_name_path(data, cmd, content);
	cmd->arg_lst = NULL;
	cmd->arg_count = 0;
	cmd->file_lst = NULL;
	cmd->next = NULL;
	return (cmd);
}

static void	find_name_path(t_data *data, t_cmd *cmd, char *content)
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
		else
			cmd->path = NULL;
	}
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

void	clear_cmd_lst(t_cmd *cmd_lst)
{
	t_cmd	*cmd;

	while (cmd_lst)
	{
		cmd = cmd_lst;
		free(cmd->name);
		if (cmd->path)
			free(cmd->path);
		clear_arg_lst(cmd->arg_lst);
		clear_file_lst(cmd->file_lst);
		cmd_lst = cmd_lst->next;
		free(cmd);
	}
}