/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 22:01:22 by sabras            #+#    #+#             */
/*   Updated: 2024/08/31 11:20:42 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_flag	*init_flag(char *str, t_data *data)
{
	t_flag	*flag;

	flag = malloc(sizeof(t_flag));
	if (!flag)
		return (throw_error("malloc failure", data), NULL);
	flag->str = str;
	flag->next = NULL;
	return (flag);
}

void	clear_flag_lst(t_flag *flag_lst)
{
	while (flag_lst)
	{
		free(flag_lst->str);
		flag_lst = flag_lst->next;
	}
	free(flag_lst);
}
