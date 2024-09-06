/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:46:50 by sabras            #+#    #+#             */
/*   Updated: 2024/09/06 17:47:41 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_token(t_data *data, t_token **token_lst, char *content)
{
	t_token	*node;
	t_token	*tmp;

	node = malloc(sizeof(t_token));
	if (!node)
		return (clear_token_lst(*token_lst),
			throw_error("malloc failure", data));
	node->content = content;
	node->next = NULL;
	if (!*token_lst)
		*token_lst = node;
	else
	{
		tmp = *token_lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
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
