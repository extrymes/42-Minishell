/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 22:24:34 by sabras            #+#    #+#             */
/*   Updated: 2024/09/09 15:09:52 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cmd_path(t_data *data, char *name)
{
	char	*path;
	char	**locations;
	char	*joined;
	int		i;

	if (!is_alpha(name))
		return (NULL);
	path = ft_getenv("PATH", data->env);
	if (!path)
		return (NULL);
	locations = ft_split(path, ':');
	if (!locations)
		return (throw_error("malloc failure", data), NULL);
	i = -1;
	while (locations[++i])
	{
		joined = strjoin_free(ft_strjoin(locations[i], "/"), name, 0);
		if (!joined)
			return (free_split(locations),
				throw_error("malloc failure", data), NULL);
		if (access(joined, X_OK) == 0)
			return (free_split(locations), joined);
		free(joined);
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

int	check_command(t_data *data, char *content)
{
	struct stat	statbuf;
	char		*path;

	if (ft_strstr(BUILTINS, content))
		return (1);
	path = get_cmd_path(data, content);
	if (path)
		return (free(path), 1);
	if (!ft_strcmp(content, "."))
		return (print_cmd_error(content, NULL, "filename argument required"), 0);
	if (ft_strchr(content, '/'))
	{
		if (access(content, F_OK) != 0)
			return (print_cmd_error(content, NULL,
					"No such file or directory"), 0);
		if (access(content, X_OK) != 0)
			return (print_cmd_error(content, NULL, "Permission denied"), 0);
		if (stat(content, &statbuf) != 0)
			throw_error("stat failure", data);
		if (!S_ISREG(statbuf.st_mode))
			return (print_cmd_error(content, NULL, "Is a directory"), 0);
		return (1);
	}
	else
		print_cmd_error(content, NULL, "command not found");
	return (0);
}
