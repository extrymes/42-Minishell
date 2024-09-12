/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:42:42 by msimao            #+#    #+#             */
/*   Updated: 2024/09/11 16:29:37 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_var_exists(char **env, char *str)
{
	int	i;
	int	j;

	j = 0;
	while (str[j] && str[j] != '=')
		j++;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(str, env[i], j) == 0) // probleme =
			return (i);
		i++;
	}
	return (0);
}

char	**copy_tab(t_data *data)
{
	char	**envp;
	int		i;

	i = 0;
	while (data->env[i])
		i++;
	envp = malloc(sizeof(char *) * (i + 1));
	if (!envp)
		return (NULL);
	i = 0;
	while (data->env[i])
	{
		envp[i] = ft_strdup(data->env[i]);
		if (!envp[i])
			return (free_split(envp), NULL);
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

int	check_arg(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[i]))
		return (0);
	while(str[i] && str[i] != '=')
	{
		if (!check_key(str[i]))
			return (0);
		i++;
	}
	return (1);
}
