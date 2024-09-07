/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 11:27:31 by sabras            #+#    #+#             */
/*   Updated: 2024/09/07 01:57:38 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_realloc(char *s, size_t size)
{
	char	*str;
	size_t	i;

	if (size < ft_strlen(s))
		return (NULL);
	str = malloc((size + 1) * sizeof(char));
	if (!str)
		return (NULL);
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

void	*ft_realloc2(void *ptr, size_t original_size, size_t new_size)
{
	size_t	size_to_copy;
	void	*new_ptr;

	if (!ptr)
		return (malloc(new_size));
	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	size_to_copy = original_size;
	if (new_size < original_size)
		size_to_copy = new_size;
	ft_memcpy(new_ptr, ptr, size_to_copy);
	free(ptr);
	return (new_ptr);
}

char	*alloc_str(t_data *data, char *str)
{
	char	*allocated;

	if (str)
		allocated = ft_strdup(str);
	else
		allocated = ft_strdup("");
	if (!allocated)
		throw_error("malloc failure", data);
	return (allocated);
}

void	free_split(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}
