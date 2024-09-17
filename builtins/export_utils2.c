/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 08:38:40 by msimao            #+#    #+#             */
/*   Updated: 2024/09/17 16:09:54 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_join(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			if (i > 0 && str[i - 1] == '+')
				return (1);
			return (0);
		}
		i++;
	}
	return (0);
}

char	**sort_env(t_data *data)
{
	int		i;
	int		j;
	char	*tmp;
	char	**envp;

	envp = copy_tab(data);
	if (!envp)
		return (NULL);
	i = 0;
	while (envp[i])
		i++;
	j = 0;
	while (j + 1 < i)
	{
		if (ft_strcmp(envp[j], envp[j + 1]) > 0)
		{
			tmp = envp[j];
			envp[j] = envp[j + 1];
			envp[j + 1] = tmp;
			j = 0;
		}
		else
			j++;
	}
	return (envp);
}
