/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 09:33:49 by sabras            #+#    #+#             */
/*   Updated: 2024/09/10 13:35:20 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_data	data;

	(void)ac;
	(void)av;
	data = init_data(env);
	while (1)
	{
		data.entry = init_entry(&data);
		data.entry->input = readline(data.entry->prompt);
		if (ft_strlen(data.entry->input) > 0)
		{
			add_history(data.entry->input);
			parse_input(&data, data.entry);
			pipex(&data);
		}
		clear_entry(data.entry);
	}
	return (clear_data(&data), 0);
}
