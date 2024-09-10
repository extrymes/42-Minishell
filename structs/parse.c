/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 04:19:57 by sabras            #+#    #+#             */
/*   Updated: 2024/09/11 00:03:07 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parse	init_parse(t_data *data, char *input)
{
	t_parse	p;

	p.input = input;
	p.parsed = alloc_str(data, input);
	p.quote = 0;
	p.size = ft_strlen(input);
	p.i = 0;
	p.j = 0;
	return (p);
}
