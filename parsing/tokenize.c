/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 11:05:01 by sabras            #+#    #+#             */
/*   Updated: 2024/09/06 17:52:14 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_content(char *input);
static char	*parse_content(t_parse *parse, char *content, char **env);
static char	*replace_variables(t_parse *parse, char **env);
static char	*remove_quotes(char *content);

t_token	*tokenize_input(t_data *data, char *input)
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
		i = count_opt(input, input[i]);
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

static char	*replace_variables(t_parse *parse, char **env)
{
	char	*content;
	char	quote;
	int		i;
	int		j;

	content = parse->content;
	if (!ft_strchr(content, '$') && !ft_strchr(content, '~'))
		return (parse->parsed);
	quote = 0;
	i = -1;
	j = 0;
	while (content[++i])
	{
		if (content[i] == '$' && is_valid_key(content[i + 1]) && quote != '\'')
			parse->parsed = insert_value(parse, env, &i, &j);
		else if (content[i] == '~' && is_valid_home(content[i + 1]) && !quote)
			parse->parsed = insert_home(parse, env, &j);
		else
			parse->parsed[j++] = content[i];
		if (!parse->parsed)
			return (NULL);
		quote = toggle_quote(content[i], quote);
	}
	parse->parsed[j] = '\0';
	return (parse->parsed);
}

static char	*remove_quotes(char *content)
{
	char	*parsed;
	char	quote;
	int		i;
	int		j;

	if (!ft_strchr(content, '\'') && !ft_strchr(content, '\"'))
		return (content);
	parsed = malloc((ft_strlen(content) + 1) * sizeof(char));
	if (!parsed)
		return (free(content), NULL);
	quote = 0;
	i = 0;
	j = 0;
	while (content[i])
	{
		if (!is_quote(content[i]) || (quote && quote != content[i]))
			parsed[j++] = content[i];
		quote = toggle_quote(content[i], quote);
		i++;
	}
	parsed[j] = '\0';
	return (free(content), parsed);
}
