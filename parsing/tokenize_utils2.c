/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 20:11:00 by sabras            #+#    #+#             */
/*   Updated: 2024/09/06 19:05:19 by sabras           ###   ########.fr       */
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

int	count_spaces(char *str)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	return (i);
}

int	count_opt(char *str, char opt)
{
	int	i;

	i = 0;
	while (str[i] == opt)
		i++;
	return (i);
}
