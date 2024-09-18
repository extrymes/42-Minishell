/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 19:56:48 by sabras            #+#    #+#             */
/*   Updated: 2024/09/18 09:23:42 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_signal_received;

static t_cmd	*get_cmd(t_data *data, t_token *token);
static int		handle_redir(t_data *data, t_cmd *cmd, t_token *token, int *id);
static int		handle_heredoc(t_data *data, t_token *token, int fd);

void	*parse_input(t_data *data, t_entry *entry)
{
	t_token	*token;
	t_cmd	*cmd;
	int		id;

	entry->input = handle_variables(data, entry->input, 0);
	tokenize_input(data, entry->input);
	if (!check_syntax(data, entry->token_lst))
		return (NULL);
	token = entry->token_lst;
	cmd = NULL;
	id = 0;
	while (token)
	{
		if (!cmd)
			cmd = get_cmd(data, token);
		if (token->type >= FILE_IN && handle_redir(data, cmd, token, &id))
			token = token->next;
		if (token->type == PIPE && ++id)
			cmd = NULL;
		if (id == -1)
			return (entry->cmd_count = 0, NULL);
		token = token->next;
	}
	return (NULL);
}

static t_cmd	*get_cmd(t_data *data, t_token *token)
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

static int	handle_redir(t_data *data, t_cmd *cmd, t_token *token, int *id)
{
	char	*filename;
	int		fd;

	if (token->type == HERE_DOC)
	{
		filename = strjoin_free("/tmp/heredoc", ft_itoa(*id), 1);
		if (!filename)
			throw_error(data, "malloc failure");
		fd = open(filename, O_TRUNC | O_CREAT | O_RDWR, 0644);
		if (fd < 0)
			return (free(filename), throw_error(data, "open failure"), 0);
		if (!handle_heredoc(data, token->next, fd))
			return (free(filename), *id = -1, 0);
	}
	else
		filename = alloc_str(data, token->next->content);
	add_file(data, cmd, filename, token->type);
	return (1);
}

static int	handle_heredoc(t_data *data, t_token *delimiter, int fd)
{
	char	*line;

	while (1)
	{
		line = readline(CYAN "> " RESET);
		if (!line)
			break ;
		line = handle_variables(data, line, delimiter->has_quote + 1);
		if (!ft_strcmp(line, delimiter->content))
			break ;
		if (g_signal_received)
			return (close(fd), free(line), 0);
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
	}
	if (line)
		free(line);
	else
		heredoc_warning(delimiter->content);
	return (close(fd), 1);
}
