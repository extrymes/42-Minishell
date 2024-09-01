/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 11:27:31 by sabras            #+#    #+#             */
/*   Updated: 2024/08/31 11:05:23 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_realloc(char *s, size_t size, t_data *data)
{
	char	*str;
	size_t	i;

	if (size < ft_strlen(s))
		return (throw_error("size smaller than string length", data), NULL);
	str = malloc((size + 1) * sizeof(char));
	if (!str)
		return (throw_error("malloc failure", data), NULL);
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
