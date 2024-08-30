/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 00:09:52 by sabras            #+#    #+#             */
/*   Updated: 2024/05/22 11:48:16 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_in_set(const char c, const char *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	int		i;

	if (!s1)
		return (NULL);
	start = 0;
	end = 0;
	i = 0;
	while (s1[i] && ft_in_set(s1[i], set))
	{
		start++;
		i++;
	}
	if (start == ft_strlen(s1))
		return (ft_substr(s1, start, 0));
	i = ft_strlen(s1) - 1;
	while (i >= 0 && ft_in_set(s1[i], set))
	{
		end++;
		i--;
	}
	return (ft_substr(s1, start, ft_strlen(s1) - start - end));
}
