/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:33:25 by sabras            #+#    #+#             */
/*   Updated: 2024/09/03 07:36:31 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*init_cmd(char *name, char *path, t_data *data)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (free(name), free(path), throw_error("malloc failure", data), NULL);
	cmd->name = name;
	cmd->path = path;
	cmd->flag_lst = NULL;
	cmd->flag_count = 0;
	cmd->next = NULL;
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

void	clear_cmd_lst(t_cmd *cmd_lst)
{
	t_cmd	*tmp;

	while (cmd_lst)
	{
		tmp = cmd_lst;
		free(cmd_lst->name);
		free(cmd_lst->path);
		clear_flag_lst(cmd_lst->flag_lst);
		cmd_lst = cmd_lst->next;
		free(tmp);
	}
}
