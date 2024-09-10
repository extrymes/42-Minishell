/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 19:56:48 by sabras            #+#    #+#             */
/*   Updated: 2024/09/10 14:45:30 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*handle_variables(t_data *data, char *input);
static int	find_cmd_data(t_data *data, t_cmd *cmd, t_token *token, int *err);
static int	find_file(t_data *data, t_cmd *cmd, t_token *token, int *err);

int	parse_input(t_data *data, t_entry *entry)
{
	t_token	*token;
	t_cmd	*cmd;
	int		err;

	entry->input = handle_variables(data, entry->input);
	tokenize_input(data, entry->input);
	if (!check_syntax(entry->token_lst))
		return (0);
	token = entry->token_lst;
	cmd = init_cmd(data);
	err = 0;
	while (token)
	{
		if (!cmd->name)
			find_cmd_data(data, cmd, token, &err);
		if (token->content[0] == '|')
			cmd = init_cmd(data);
		if (find_file(data, cmd, token, &err))
			token = token->next;
		if (err)
			return (entry->cmd_count = 0, 0);
		token = token->next;
	}
	return (1);
}

static char	*handle_variables(t_data *data, char *input)
{
	t_parse	p;

	if (!ft_strchr(input, '$') && !ft_strchr(input, '~'))
		return (input);
	p = init_parse(data, input);
	while (input[++p.i])
	{
		if (input[p.i] == '$' && check_key(input[p.i + 1]) && p.quote != '\'')
			p.parsed = insert_value(data, &p);
		else if (input[p.i] == '~' && check_tilde(input[p.i + 1]) && !p.quote)
			p.parsed = insert_home(data, &p);
		else
			p.parsed[p.j++] = input[p.i];
		p.quote = toggle_quote(input[p.i], p.quote);
	}
	p.parsed[p.j] = '\0';
	return (p.parsed);
}

static int	find_cmd_data(t_data *data, t_cmd *cmd, t_token *token, int *err)
{
	if (token->type >= FILE_IN)
		token = token->next->next;
	if (!token)
		return (0);
	if (!check_command(data, token->content))
		return (*err = 1, 0);
	set_cmd_data(data, cmd, token->content);
	token = token->next;
	while (token && token->type != PIPE)
	{
		if (token->type >= FILE_IN)
			token = token->next;
		else
			add_arg(data, cmd, token->content);
		token = token->next;
	}
	return (1);
}

static int	find_file(t_data *data, t_cmd *cmd, t_token *token, int *err)
{
	char	*content;

	if (token->type < FILE_IN)
		return (0);
	content = token->next->content;
	if (token->type == FILE_IN && access(content, F_OK) != 0)
		return (*err = 1, cmd_error(content, NULL,
				"No such file or directory"), 0);
	add_file(data, cmd, content, token->type);
	return (1);
}
