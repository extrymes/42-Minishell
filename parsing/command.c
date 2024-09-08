/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 22:24:34 by sabras            #+#    #+#             */
/*   Updated: 2024/09/08 22:25:11 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cmd_path(t_data *data, char *name)
{
	char	*path;
	char	**locations;
	char	*joined;
	int		i;

	path = ft_getenv("PATH", data->env);
	if (!path)
		return (NULL);
	locations = ft_split(path, ':');
	if (!locations)
		return (throw_error("malloc failure", data), NULL);
	i = 0;
	while (locations[i])
	{
		joined = strjoin_free(ft_strjoin(locations[i], "/"), name, 0);
		if (!joined)
			return (free_split(locations),
				throw_error("malloc failure", data), NULL);
		if (access(joined, X_OK) == 0)
			return (free_split(locations), joined);
		free(joined);
		i++;
	}
	return (free_split(locations), NULL);
}

char	*get_cmd_name(t_data *data, char *path)
{
	char	*name;
	char	**tab;
	int		i;

	tab = ft_split(path, '/');
	if (!tab)
		return (throw_error("malloc failure", data), NULL);
	i = 0;
	while (tab[i + 1])
		free(tab[i++]);
	name = tab[i];
	return (free(tab), name);
}

int	is_command(t_data *data, char *content)
{
	char	*path;

	if (access(content, X_OK) == 0)
		return (1);
	if (ft_strstr(BUILTINS, content))
		return (1);
	path = get_cmd_path(data, content);
	if (path)
		return (free(path), 1);
	return (0);
}
