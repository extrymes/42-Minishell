/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 22:24:34 by sabras            #+#    #+#             */
/*   Updated: 2024/09/12 09:10:26 by sabras           ###   ########.fr       */
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
		throw_error(data, "malloc failure");
	i = -1;
	while (locations[++i])
	{
		joined = strjoin_free(ft_strjoin(locations[i], "/"), name, 0);
		if (!joined)
			return (free_split(locations),
				throw_error(data, "malloc failure"), NULL);
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
		throw_error(data, "malloc failure");
	i = 0;
	while (tab[i + 1])
		free(tab[i++]);
	name = tab[i];
	return (free(tab), name);
}

int	check_command(t_data *data, char *content, char **err)
{
	struct stat	statbuf;
	char		*path;

	if (ft_strstr(BUILTINS, content))
		return (1);
	path = get_cmd_path(data, content);
	if (path)
		return (free(path), 1);
	if (!ft_strcmp(content, "."))
		return (*err = get_error(data, content, ERR_NARG, 2), 0);
	if (ft_strchr(content, '/'))
	{
		if (access(content, F_OK) != 0)
			return (*err = get_error(data, content, ERR_NFILE, 127), 0);
		if (access(content, X_OK) != 0)
			return (*err = get_error(data, content, ERR_NPERM, 126), 0);
		if (stat(content, &statbuf) != 0)
			throw_error(data, "stat failure");
		if (!S_ISREG(statbuf.st_mode))
			return (*err = get_error(data, content, ERR_ISDIR, 126), 0);
		return (1);
	}
	else
		*err = get_error(data, content, ERR_NCMD, 127);
	return (0);
}
