/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 09:58:23 by sabras            #+#    #+#             */
/*   Updated: 2024/08/30 22:16:08 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_data(t_data *data, char **env)
{
	if (!read_env(data, env))
		return (0);
	data->user = ft_getenv("USER", data->env);
	data->home = ft_getenv("HOME", data->env);
	data->pwd = ft_getenv("PWD", data->env);
	data->prompt = NULL;
	data->entry = init_entry();
	return (1);
}

void	clear_data(t_data data)
{
	int	i;

	i = 0;
	while (data.env[i])
		free(data.env[i++]);
	free(data.env);
	if (data.prompt)
		free(data.prompt);
	clear_entry(data.entry);
	clear_history();
}
