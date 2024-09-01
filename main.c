/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 09:33:49 by sabras            #+#    #+#             */
/*   Updated: 2024/08/31 11:11:37 by sabras           ###   ########.fr       */
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
		data.prompt = create_prompt(&data);
		data.entry.input = readline(data.prompt);
		add_history(data.entry.input);
		parse_input(&data, &data.entry);
		free(data.prompt);
		free(data.entry.input);
	}
	return (clear_data(&data), 0);
}
