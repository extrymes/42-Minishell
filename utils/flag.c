/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 22:01:22 by sabras            #+#    #+#             */
/*   Updated: 2024/08/30 22:02:58 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_flag	init_flag(void)
{
	t_flag	flag;

	flag.str = NULL;
	flag.next = NULL;
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
