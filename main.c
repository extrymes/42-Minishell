/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 09:33:49 by sabras            #+#    #+#             */
/*   Updated: 2024/09/17 12:32:27 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal_received = 0;

int	main(int ac, char **av, char **env)
{
	t_data	data;

	(void)ac;
	(void)av;
	data = init_data(env);
	handle_signals(0);
	rl_event_hook = rl_event_handler;
	while (1)
	{
		data.entry = init_entry(&data);
		data.entry->input = readline(data.entry->prompt);
		if (!data.entry->input)
			ft_exit(NULL, &data);
		if (ft_strlen(data.entry->input) > 0 && !g_signal_received)
		{
			add_history(data.entry->input);
			parse_input(&data, data.entry);
			exec_data(&data);
		}
		if (g_signal_received)
			data.exit_code = 128 + g_signal_received;
		reset_signal_status();
		clear_entry(data.entry);
	}
	return (clear_data(&data), 0);
}
