/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 19:39:21 by sabras            #+#    #+#             */
/*   Updated: 2024/09/06 06:07:50 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_arg	*init_arg(t_data *data, char *content)
{
	t_arg	*arg;

	arg = malloc(sizeof(t_arg));
	if (!arg)
		return (throw_error("malloc failure", data), NULL);
	arg->data = ft_strdup(content);
	arg->next = NULL;
	return (arg);
}

void	add_arg(t_data *data, t_cmd *cmd, char *content)
{
	t_arg	*arg;
	t_arg	*tmp;

	arg = init_arg(data, content);
	if (!cmd->arg_lst)
		cmd->arg_lst = arg;
	else
	{
		tmp = cmd->arg_lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = arg;
	}
	cmd->arg_count++;
}

void	clear_arg_lst(t_arg *arg_lst)
{
	t_arg	*tmp;

	while (arg_lst)
	{
		tmp = arg_lst;
		free(arg_lst->data);
		arg_lst = arg_lst->next;
		free(tmp);
	}
}
