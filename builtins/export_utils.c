/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:42:42 by msimao            #+#    #+#             */
/*   Updated: 2024/09/14 11:29:41 by sabras           ###   ########.fr       */
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
		if (ft_strncmp(str, env[i], j) == 0)
		{
			if (env[i][j] == '\0' || env[i][j] == '=')
				return (i);
		}
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
	while (str[i] && str[i] != '=')
	{
		if (!check_key(str[i]))
			return (0);
		i++;
	}
	if (i == 0)
		return (0);
	return (1);
}

char	*copy_to(char *env, char c, char start)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	if (start == '=')
	{
		while (env[j] != start)
			j++;
		j++;
	}
	while (env[j + i] && env[j + i] != c)
		i++;
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (env[j + i] && env[j + i] != c)
	{
		str[i] = env[j + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

void	print_x(char *str, int a)
{
	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	ft_putstr_fd(str, STDOUT_FILENO);
	if (a == 1)
		ft_putstr_fd("\"\n", STDOUT_FILENO);
	else
		ft_putstr_fd("\n", STDOUT_FILENO);
}
