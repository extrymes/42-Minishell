/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 11:20:32 by sabras            #+#    #+#             */
/*   Updated: 2024/09/04 20:25:42 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*insert_value(t_parse *parse, char **env, int *i, int *j);
static char	*get_variable(char *content);

char	*replace_variables(t_parse *parse, char **env)
{
	char	quote;
	int		i;
	int		j;

	if (!ft_strchr(parse->content, '$'))
		return (parse->content);
	i = -1;
	j = 0;
	while (parse->content[++i])
	{
		if (parse->content[i] == '$' && is_valid_key(parse->content[i + 1])
			&& quote != '\'')
			parse->parsed = insert_value(parse, env, &i, &j);
		else
			parse->parsed[j++] = parse->content[i];
		if (!parse->parsed)
			return (free(parse->content), NULL);
		quote = toggle_quote(parse->content[i], quote);
	}
	parse->parsed[j] = '\0';
	return (free(parse->content), parse->parsed);
}

static char	*insert_value(t_parse *parse, char **env, int *i, int *j)
{
	char	*variable;
	char	*value;
	int		diff;

	variable = get_variable(parse->content + *i + 1);
	if (!variable)
		return (NULL);
	value = ft_getenv(variable, env);
	diff = (ft_strlen(variable) + 1) - ft_strlen(value);
	if (diff < 0)
	{
		parse->size += -diff;
		parse->parsed = ft_realloc(parse->parsed, parse->size);
	}
	if (value)
		ft_strcpy(parse->parsed + *j, value);
	*i += ft_strlen(variable);
	*j += ft_strlen(value);
	return (parse->parsed);
}

static char	*get_variable(char *content)
{
	char	*variable;
	int		i;
	int		j;

	i = 0;
	while (content[i] && is_valid_key(content[i]))
		i++;
	variable = malloc((i + 1) * sizeof(char));
	if (!variable)
		return (NULL);
	j = -1;
	while (++j < i)
		variable[j] = content[j];
	variable[j] = '\0';
	return (variable);
}

char	*remove_quotes(char *content)
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
