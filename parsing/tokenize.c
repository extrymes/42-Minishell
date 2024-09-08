/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 11:05:01 by sabras            #+#    #+#             */
/*   Updated: 2024/09/08 21:49:27 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_content(t_data *data, char *input);
static char	*handle_quotes(t_data *data, char *content);
static int	count_spaces(char *str);
static int	count_opt(char *str, char opt);

void	tokenize_input(t_data *data, char *input)
{
	char	*content;
	int		i;

	i = count_spaces(input);
	while (input[i])
	{
		content = get_content(data, input + i);
		i += ft_strlen(content);
		i += count_spaces(input + i);
		content = handle_quotes(data, content);
		add_token(data, data->entry, content);
	}
}

static char	*get_content(t_data *data, char *input)
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
		return (throw_error("malloc failure", data), NULL);
	j = -1;
	while (++j < i)
		content[j] = input[j];
	content[j] = '\0';
	return (content);
}

static char	*handle_quotes(t_data *data, char *content)
{
	char	*parsed;
	char	quote;
	int		i;
	int		j;

	if (!ft_strchr(content, '\'') && !ft_strchr(content, '\"'))
		return (content);
	parsed = malloc((ft_strlen(content) + 1) * sizeof(char));
	if (!parsed)
		return (free(content), throw_error("malloc failure", data), NULL);
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

static int	count_spaces(char *str)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	return (i);
}

static int	count_opt(char *str, char opt)
{
	int	i;

	i = 0;
	while (str[i] == opt && i < 2)
		i++;
	return (i);
}

