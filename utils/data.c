/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 09:58:23 by sabras            #+#    #+#             */
/*   Updated: 2024/09/02 14:40:41 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	init_data(char **env)
{
	t_data	data;

	read_env(&data, env);
	data.user = ft_getenv("USER", data.env);
	data.home = ft_getenv("HOME", data.env);
	data.pwd = ft_getenv("PWD", data.env);
	data.prompt = NULL;
	data.entry = init_entry();
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
	if (data->prompt)
		free(data->prompt);
	clear_entry(&data->entry);
	rl_clear_history();
}
