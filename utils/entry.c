/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 13:36:11 by sabras            #+#    #+#             */
/*   Updated: 2024/08/31 10:53:14 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_entry	init_entry(void)
{
	t_entry	entry;

	entry.cmd_lst = NULL;
	entry.cmd_count = 0;
	entry.outfile = 0;
	entry.infile = 0;
	return (entry);
}

void	clear_entry(t_entry *entry)
{
	if (entry->input)
		free(entry->input);
	clear_cmd_lst(entry->cmd_lst);
}
