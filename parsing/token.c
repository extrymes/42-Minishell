/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 11:05:01 by sabras            #+#    #+#             */
/*   Updated: 2024/09/05 08:37:09 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_token(t_data *data, t_token **token_lst, char *content);
static char	*get_content(char *input);
static char	*parse_content(t_parse *parse, char *content, char **env);

t_token	*tokeniser(t_data *data, char *input)
{
	t_token	*token_lst;
	t_parse	parse;
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
		content = parse_content(&parse, content, data->env);
		if (parse.warning != 0)
			continue ;
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

static char	*parse_content(t_parse *parse, char *content, char **env)
{
	parse->content = content;
	parse->parsed = ft_strdup(content);
	if (!parse->parsed)
		return (clear_parse(parse), NULL);
	parse->size = ft_strlen(content);
	parse->warning = 0;
	parse->parsed = replace_variables(parse, env);
	if (!parse->parsed)
		return (clear_parse(parse), NULL);
	parse->parsed = remove_quotes(parse->parsed);
	if (!parse->parsed)
		return (NULL);
	if (ft_strchr(content, '$') && ft_strlen(parse->parsed) == 0)
	{
		parse->warning = NullContent;
		return (clear_parse(parse), NULL);
	}
	return (free(content), parse->parsed);
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
		tmp = NULL;
	}
}
