/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:46:50 by sabras            #+#    #+#             */
/*   Updated: 2024/09/08 03:45:42 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_token(t_data *data, t_entry *entry, char *content)
{
	t_token	*token;
	t_token	*tmp;

	token = malloc(sizeof(t_token));
	if (!token)
		return (throw_error("malloc failure", data));
	token->content = content;
	token->next = NULL;
	if (!entry->token_lst)
		entry->token_lst = token;
	else
	{
		tmp = entry->token_lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = token;
	}
}

void	clear_token_lst(t_token *token_lst)
{
	t_token	*tmp;

	while (token_lst)
	{
		tmp = token_lst;
		free(token_lst->content);
		token_lst = token_lst->next;
		free(tmp);
	}
}
