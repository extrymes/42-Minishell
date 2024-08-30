/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 19:34:31 by sabras            #+#    #+#             */
/*   Updated: 2024/08/24 15:00:06 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_word(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			count++;
		while (*s != c && *s)
			s++;
	}
	return (count);
}

static int	ft_spliter(char **tab, char const *s, char c)
{
	int	i;
	int	j;
	int	start;

	i = -1;
	j = 0;
	while (++i < count_word(s, c))
	{
		while (s[j] == c)
			j++;
		start = j;
		while (s[j] != c && s[j])
			j++;
		tab[i] = ft_substr(s, start, j - start);
		if (!tab[i])
		{
			while (--i >= 0)
				free(tab[i]);
			return (free(tab), 0);
		}
	}
	tab[i] = 0;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;

	if (!s)
		return (NULL);
	tab = ft_calloc(count_word(s, c) + 1, sizeof(char *));
	if (!tab)
		return (NULL);
	if (!ft_spliter(tab, s, c))
		return (NULL);
	return (tab);
}
