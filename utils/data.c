/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 09:58:23 by sabras            #+#    #+#             */
/*   Updated: 2024/09/07 01:57:26 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	init_data(char **env)
{
	t_data	data;

	read_env(&data, env);
	data.user = alloc_str(&data, ft_getenv("USER", data.env));
	data.pwd = getcwd(NULL, 0);
	if (!data.pwd)
		data.pwd = alloc_str(&data, "");
	data.entry = NULL;
	return (data);
}

void	clear_data(t_data *data)
{
	int	i;

	i = 0;
	if (data->env)
	{
		while (data->env[i])
			free(data->env[i++]);
		free(data->env);
	}
	if (data->user)
		free(data->user);
	if (data->pwd)
		free(data->pwd);
	clear_entry(data->entry);
	clear_history();
}
