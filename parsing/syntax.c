/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:06:05 by sabras            #+#    #+#             */
/*   Updated: 2024/09/10 16:07:36 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_syntax(t_token *token_lst)
{
	t_token	*token;
	int		curr;
	int		next;
	int		i;

	token = token_lst;
	i = 0;
	while (token)
	{
		curr = token->type;
		if (curr)
		{
			if ((i == 0 && curr == PIPE) || !ft_strcmp(token->content, "||"))
				return (syntax_error(token->content), 0);
			if (!token->next)
				return (syntax_error("newline"), 0);
			next = token->next->type;
			if (curr == next || (curr >= FILE_IN && next))
				return (syntax_error(token->next->content), 0);
		}
		token = token->next;
		i++;
	}
	return (1);
}
