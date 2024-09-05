/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 11:05:01 by sabras            #+#    #+#             */
/*   Updated: 2024/09/05 06:01:25 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_token(t_data *data, t_token **token_lst, char *content);
static char	*get_content(char *input);
static char	*parse_content(char *content, char **env);

t_token	*tokeniser(t_data *data, char *input)
{
	t_token	*token_lst;
	char	*content;
	int		i;

	token_lst = NULL;
	i = count_spaces(input);
	while (input[i])
	{
		content = get_content(input + i);
		if (!content)
			return (clear_token_lst(token_lst),
				throw_error("malloc failure", data), NULL);
		i += ft_strlen(content);
		i += count_spaces(input + i);
		content = parse_content(content, data->env);
		if (!content)
			return (clear_token_lst(token_lst),
				throw_error("malloc failure", data), NULL);
		add_token(data, &token_lst, content);
	}
	return (token_lst);
}

static void	add_token(t_data *data, t_token **token_lst, char *content)
{
	t_token	*node;
	t_token	*tmp;

	node = malloc(sizeof(t_token));
	if (!node)
		return (clear_token_lst(*token_lst),
			throw_error("malloc failure", data));
	node->content = content;
	node->next = NULL;
	if (!*token_lst)
		*token_lst = node;
	else
	{
		tmp = *token_lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
}

static char	*get_content(char *input)
{
	char	*content;
	char	quote;
	int		i;
	int		j;

	quote = 0;
	i = 0;
	while (input[i] && ((!ft_isspace(input[i]) && !is_opt(input[i])) || quote))
		quote = toggle_quote(input[i++], quote);
	if (i == 0 && is_opt(input[i]))
		i = 1;
	content = malloc((i + 1) * sizeof(char));
	if (!content)
		return (NULL);
	j = -1;
	while (++j < i)
		content[j] = input[j];
	content[j] = '\0';
	return (content);
}

static char	*parse_content(char *content, char **env)
{
	t_parse	parse;

	parse.content = content;
	parse.size = ft_strlen(content);
	parse.parsed = malloc((parse.size + 1) * sizeof(char));
	if (!parse.parsed)
		return (NULL);
	parse.parsed = replace_variables(&parse, env);
	if (!parse.parsed)
		return (NULL);
	parse.parsed = remove_quotes(parse.parsed);
	if (!parse.parsed)
		return (NULL);
	return (parse.parsed);
}

void	clear_token_lst(t_token *token_lst)
{
	t_token	*tmp;

	while (token_lst)
	{
		tmp = token_lst;
		free(token_lst->content);
		token_lst = token_lst->next;
		free(tmp);
	}
}
