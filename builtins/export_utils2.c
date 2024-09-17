/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimao <msimao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 08:38:40 by msimao            #+#    #+#             */
/*   Updated: 2024/09/16 08:39:36 by msimao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
