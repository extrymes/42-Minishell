/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:02:17 by sabras            #+#    #+#             */
/*   Updated: 2024/09/10 12:06:35 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_free(char *s1, char *s2, int to_free);

char	*strjoin_free(char *s1, char *s2, int to_free)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (ft_free(s1, s2, to_free), NULL);
	str = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!str)
		return (ft_free(s1, s2, to_free), NULL);
	i = 0;
	j = 0;
	while (s1[j])
		str[i++] = s1[j++];
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	return (ft_free(s1, s2, to_free), str);
}

static void	ft_free(char *s1, char *s2, int to_free)
{
	if (to_free == 0 && s1)
		free(s1);
	else if (to_free == 1 && s2)
		free(s2);
	else if (to_free == 2)
	{
		if (s1)
			free(s1);
		if (s2)
			free(s2);
	}
}

int	is_alpha(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalpha(str[i]))
			return (0);
		i++;
	}
	return (1);
}
