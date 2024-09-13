/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:46:50 by sabras            #+#    #+#             */
/*   Updated: 2024/09/13 21:01:52 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*init_token(t_data *data, char *content, int type, int has_quote)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		throw_error(data, "malloc failure");
	token->content = content;
	token->type = type;
	token->has_quote = has_quote;
	token->next = NULL;
	add_token(data->entry, token);
	return (token);
}

void	add_token(t_entry *entry, t_token *token)
{
	t_token	*tmp;

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

int	get_token_type(char *content)
{
	if (!ft_strcmp(content, "|") || !ft_strcmp(content, "||"))
		return (PIPE);
	if (!ft_strcmp(content, "<"))
		return (FILE_IN);
	if (!ft_strcmp(content, "<<"))
		return (HERE_DOC);
	if (!ft_strcmp(content, ">"))
		return (FILE_OUT);
	if (!ft_strcmp(content, ">>"))
		return (FILE_OUT_APP);
	return (WORD);
}

void	clear_token_lst(t_token *token_lst)
{
	t_token	*token;

	while (token_lst)
	{
		token = token_lst;
		free(token->content);
		token_lst = token_lst->next;
		free(token);
	}
}
