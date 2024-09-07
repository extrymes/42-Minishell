/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 11:51:58 by sabras            #+#    #+#             */
/*   Updated: 2024/09/06 17:15:12 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	is_valid_key(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

int	is_valid_home(char c)
{
	if (!c || c == ' ' || c == '/')
		return (1);
	return (0);
}
