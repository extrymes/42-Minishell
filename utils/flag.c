/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 22:01:22 by sabras            #+#    #+#             */
/*   Updated: 2024/09/03 07:37:52 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_flag	*init_flag(char *word, t_data *data)
{
	t_flag	*flag;

	flag = malloc(sizeof(t_flag));
	if (!flag)
		return (free(word), throw_error("malloc failure", data), NULL);
	flag->word = word;
	flag->next = NULL;
	return (flag);
}

void	clear_flag_lst(t_flag *flag_lst)
{
	t_flag	*tmp;

	while (flag_lst)
	{
		tmp = flag_lst;
		free(flag_lst->word);
		flag_lst = flag_lst->next;
		free(tmp);
	}
}
