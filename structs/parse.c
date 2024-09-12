/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 04:19:57 by sabras            #+#    #+#             */
/*   Updated: 2024/09/12 07:54:53 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parse	init_parse(t_data *data, char *input)
{
	t_parse	p;

	p.parsed = alloc_str(data, input);
	p.size = ft_strlen(input);
	p.quote = 0;
	p.i = 0;
	p.j = 0;
	return (p);
}
