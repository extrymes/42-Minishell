/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 11:27:31 by sabras            #+#    #+#             */
/*   Updated: 2024/08/30 19:38:33 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_realloc(char *s, size_t size)
{
	char	*str;
	size_t	i;

	if (size < ft_strlen(s))
		return (print_error("size smaller than string length"), NULL);
	str = malloc((size + 1) * sizeof(char));
	if (!str)
		return (print_error("malloc failure"), NULL);
	i = 0;
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	while (i < size)
	{
		str[i] = '0';
		i++;
	}
	str[size] = '\0';
	free(s);
	return (str);
}
