/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metachars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 11:51:58 by sabras            #+#    #+#             */
/*   Updated: 2024/09/09 11:42:10 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	toggle_quote(char c, char quote)
{
	if (is_quote(c))
	{
		if (!quote)
			return (c);
		if (c == quote)
			return (0);
	}
	return (quote);
}

int	is_opt(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

int	is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

int	check_key(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

int	check_tilde(char c)
{
	if (!c || c == ' ' || c == '/')
		return (1);
	return (0);
}
