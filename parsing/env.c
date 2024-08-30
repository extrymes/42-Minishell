/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 10:54:02 by sabras            #+#    #+#             */
/*   Updated: 2024/08/30 21:54:15 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	read_env(t_data *data, char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	data->env = malloc((i + 1) * sizeof(char *));
	if (!data->env)
		return (print_error("malloc failure"), 0);
	i = 0;
	while (env[i])
	{
		data->env[i] = ft_strdup(env[i]);
		if (!data->env[i])
		{
			while (--i >= 0)
				free(data->env[i]);
			return (free(data->env), print_error("malloc failure"), 0);
		}
		i++;
	}
	data->env[i] = NULL;
	return (1);
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