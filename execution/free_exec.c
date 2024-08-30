/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 11:08:34 by msimao            #+#    #+#             */
/*   Updated: 2024/08/30 19:37:18 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_flag_lst(t_flag *flags)
{
	while (flags)
	{
		free(flags->str);
		flags = flags->next;
	}
	free(flags);
}

void	free_cmd_lst(t_cmd *cmd_lst)
{
	while (cmd_lst)
	{
		free(cmd_lst->name);
		free(cmd_lst->path);
		free_flag_lst(cmd_lst->flag_lst);
		cmd_lst = cmd_lst->next;
	}
	free(cmd_lst);
}

void	free_entry(t_entry *entry)
{
	free_cmd_lst(entry->cmd_lst);
	free(entry->input);
}

void	error_exec(t_cmd *cmd_lst, t_entry *entry)
{
	free_entry(entry);
	free_cmd_lst(cmd_lst);
	ft_putstr_fd("malloc failed", 2);
	exit(EXIT_FAILURE);
}




