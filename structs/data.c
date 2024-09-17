/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 09:58:23 by sabras            #+#    #+#             */
/*   Updated: 2024/09/17 11:45:27 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	init_data(char **env)
{
	t_data	data;

	data.user = NULL;
	data.home = NULL;
	data.pwd = NULL;
	data.env = NULL;
	data.entry = NULL;
	read_env(&data, env);
	data.user = alloc_str(&data, ft_getenv("USER", data.env));
	data.home = alloc_str(&data, ft_getenv("HOME", data.env));
	data.pwd = getcwd(NULL, 0);
	if (!data.pwd)
		data.pwd = alloc_str(&data, "");
	data.stdin_fd = dup(STDIN_FILENO);
	if (data.stdin_fd < 0)
		throw_error(&data, "dup failure");
	data.stdout_fd = dup(STDOUT_FILENO);
	if (data.stdout_fd < 0)
		throw_error(&data, "dup failure");
	data.exit_code = 0;
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
	if (data->home)
		free(data->home);
	if (data->pwd)
		free(data->pwd);
	close(data->stdin_fd);
	close(data->stdout_fd);
	clear_entry(data->entry);
	rl_clear_history();
}
