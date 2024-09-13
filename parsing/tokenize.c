/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 11:05:01 by sabras            #+#    #+#             */
/*   Updated: 2024/09/13 21:04:55 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_content(t_data *data, char *input);
static char	*handle_quotes(t_data *data, char *content, int *quote);
static int	count_spaces(char *str);
static int	count_opt(char *str, char opt);

void	tokenize_input(t_data *data, char *input)
{
	char	*content;
	int		type;
	int		has_quote;
	int		i;

	i = count_spaces(input);
	while (input[i])
	{
		has_quote = 1;
		content = get_content(data, input + i);
		i += ft_strlen(content);
		i += count_spaces(input + i);
		type = get_token_type(content);
		content = handle_quotes(data, content, &has_quote);
		init_token(data, content, type, has_quote);
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
		throw_error(data, "malloc failure");
	j = -1;
	while (++j < i)
		content[j] = input[j];
	content[j] = '\0';
	return (content);
}

static char	*handle_quotes(t_data *data, char *content, int *has_quote)
{
	char	*parsed;
	char	quote;
	int		i;
	int		j;

	if (!ft_strchr(content, '\'') && !ft_strchr(content, '\"'))
		return (*has_quote = 0, content);
	parsed = malloc((ft_strlen(content) + 1) * sizeof(char));
	if (!parsed)
		return (free(content), throw_error(data, "malloc failure"), NULL);
	quote = 0;
	i = 0;
	j = 0;
	while (content[i])
	{
		if (!is_quote(content[i]) || (quote && quote != content[i]))
			parsed[j++] = content[i];
		quote = toggle_quote(content[i++], quote);
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
