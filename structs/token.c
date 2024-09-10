/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:46:50 by sabras            #+#    #+#             */
/*   Updated: 2024/09/10 23:41:19 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_token(t_data *data, t_entry *entry, char *content, int type)
{
	t_token	*token;
	t_token	*tmp;

	token = malloc(sizeof(t_token));
	if (!token)
		throw_error(data, "malloc failure");
	token->content = content;
	token->type = type;
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
