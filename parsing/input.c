/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 19:56:48 by sabras            #+#    #+#             */
/*   Updated: 2024/09/12 14:03:08 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*find_cmd(t_data *data, t_token *token);
static int		find_file(t_data *data, t_cmd *cmd, t_token *token, int i);
static void		*handle_heredoc(t_data *data, t_cmd *cmd, t_token *token, int i);

void	parse_input(t_data *data, t_entry *entry)
{
	t_token	*token;
	t_cmd	*cmd;
	int		i;

	entry->input = handle_variables(data, entry->input);
	tokenize_input(data, entry->input);
	if (!check_syntax(data, entry->token_lst))
		return ;
	token = entry->token_lst;
	cmd = NULL;
	i = 0;
	while (token)
	{
		if (!cmd)
			cmd = find_cmd(data, token);
		if (token->type >= FILE_IN && find_file(data, cmd, token, i))
			token = token->next;
		if (token->type == PIPE && ++i)
			cmd = NULL;
		token = token->next;
	}
}

static t_cmd	*find_cmd(t_data *data, t_token *token)
{
	t_cmd	*cmd;
	char	*err;

	cmd = init_cmd(data);
	while (token && token->type >= FILE_IN)
		token = token->next->next;
	if (!token || token->type == PIPE)
		return (cmd);
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
	return (cmd);
}

static int	find_file(t_data *data, t_cmd *cmd, t_token *token, int i)
{
	if (token->type == HERE_DOC)
		handle_heredoc(data, cmd, token, i);
	else
		add_file(data, cmd, token->next->content, token->type);
	return (1);
}

static void	*handle_heredoc(t_data *data, t_cmd *cmd, t_token *token, int i)
{
	char	*filename;
	char	*delimiter;
	char	*line;
	int		fd;

	filename = strjoin_free("/tmp/heredoc", ft_itoa(i), 1);
	if (!filename)
		throw_error(data, "malloc failure");
	delimiter = token->next->content;
	fd = open(filename, O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (fd < 0)
		throw_error(data, "open failure");
	while (1)
	{
		line = readline(CYAN "> " RESET);
		if (!line || !ft_strcmp(line, delimiter))
			break ;
		line = handle_variables(data, line);
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
	}
	signal(SIGINT, sigint_handler_nonl);
	add_file(data, cmd, filename, token->type);
	return (free(filename), close(fd), NULL);
}
