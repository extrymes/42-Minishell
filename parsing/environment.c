/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 10:54:02 by sabras            #+#    #+#             */
/*   Updated: 2024/09/10 13:12:09 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_env(t_data *data, char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	data->env = malloc((i + 1) * sizeof(char *));
	if (!data->env)
		throw_error(data, "malloc failure");
	i = 0;
	while (env[i])
	{
		data->env[i] = ft_strdup(env[i]);
		if (!data->env[i])
			throw_error(data, "malloc failure");
		i++;
	}
	data->env[i] = NULL;
}

char	*ft_getenv(char *key, char **env)
{
	int	key_len;
	int	i;

	key_len = ft_strlen(key);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(key, env[i], key_len)
			&& env[i][key_len] == '=')
			return (&env[i][key_len + 1]);
		i++;
	}
	return (NULL);
}
