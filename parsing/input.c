/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 19:56:48 by sabras            #+#    #+#             */
/*   Updated: 2024/09/11 16:08:04 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	find_cmd(t_data *data, t_cmd *cmd, t_token *token);
static int	find_file(t_data *data, t_cmd *cmd, t_token *token);

void	parse_input(t_data *data, t_entry *entry)
{
	t_token	*token;
	t_cmd	*cmd;

	entry->input = handle_variables(data, entry->input);
	tokenize_input(data, entry->input);
	if (!check_syntax(entry->token_lst))
		return ;
	token = entry->token_lst;
	cmd = init_cmd(data);
	while (token)
	{
		if (!cmd->name)
			find_cmd(data, cmd, token);
		if (token->type == PIPE)
			cmd = init_cmd(data);
		if (find_file(data, cmd, token))
			token = token->next;
		token = token->next;
	}
}

static void	find_cmd(t_data *data, t_cmd *cmd, t_token *token)
{
	char	*err;

	while (token && token->type >= FILE_IN)
		token = token->next->next;
	if (!token)
		return ;
	if (!check_command(data, token->content, &err))
		cmd->err = err;
	set_cmd_data(data, cmd, token->content);
	token = token->next;
	while (token && token->type != PIPE)
	{
		if (token->type == WORD)
			add_arg(data, cmd, token->content);
		else
			token = token->next;
		token = token->next;
	}
	return ;
}

static int	find_file(t_data *data, t_cmd *cmd, t_token *token)
{
	if (token->type < FILE_IN)
		return (0);
	add_file(data, cmd, token->next->content, token->type);
	return (1);
}
