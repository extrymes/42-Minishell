/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 13:36:11 by sabras            #+#    #+#             */
/*   Updated: 2024/09/10 13:08:15 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_entry	*init_entry(t_data *data)
{
	t_entry	*entry;

	entry = malloc(sizeof(t_entry));
	if (!entry)
		throw_error(data, "malloc failure");
	entry->token_lst = NULL;
	entry->cmd_lst = NULL;
	entry->cmd_count = 0;
	entry->prompt = create_prompt(data);
	entry->input = NULL;
	return (entry);
}

void	clear_entry(t_entry *entry)
{
	if (entry->prompt)
	{
		free(entry->prompt);
		entry->prompt = NULL;
	}
	if (entry->input)
	{
		free(entry->input);
		entry->input = NULL;
	}
	clear_token_lst(entry->token_lst);
	clear_cmd_lst(entry->cmd_lst);
	free(entry);
}
