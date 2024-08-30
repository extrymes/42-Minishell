/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 19:11:00 by sabras            #+#    #+#             */
/*   Updated: 2024/05/15 19:48:30 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_min_size(size_t a, size_t b)
{
	if (a < b)
		return (a);
	return (b);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	size_t			str_size;
	unsigned int	i;

	if (!s)
		return (NULL);
	str_size = 0;
	if (start < ft_strlen(s))
		str_size = ft_min_size(len, ft_strlen(s) - start);
	str = malloc((str_size + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (i < str_size)
		str[i++] = s[start++];
	str[i] = '\0';
	return (str);
}
