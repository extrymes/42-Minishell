/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 09:33:49 by sabras            #+#    #+#             */
/*   Updated: 2024/08/30 23:13:53 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_data	data;

	(void)ac;
	(void)av;
	if (!init_data(&data, env))
		return (1);
	while (1)
	{
		data.prompt = create_prompt(data);
		if (!data.prompt)
			return (1);
		data.entry.input = readline(data.prompt);
		add_history(data.entry.input);
		if (!parse_input(&data.entry, data.env))
			return (1);
		free(data.prompt);
		free(data.entry.input);
	}
	return (clear_data(data), 0);
}
