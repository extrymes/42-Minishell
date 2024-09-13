/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:11:20 by sabras            #+#    #+#             */
/*   Updated: 2024/09/13 21:27:53 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*insert_value(t_data *data, t_parse *p, char *input);
static char	*insert_code(t_data *data, t_parse *p);
static char	*insert_home(t_data *data, t_parse *p);
static char	*get_variable(char *input);

char	*handle_variables(t_data *data, char *input, int heredoc)
{
	t_parse	p;

	if ((!ft_strchr(input, '$') && !ft_strchr(input, '~')) || heredoc == 2)
		return (input);
	p = init_parse(data, input);
	while (input[p.i])
	{
		if (input[p.i] == '$' && check_key(input[p.i + 1])
			&& (p.quote != '\'' || heredoc))
			p.parsed = insert_value(data, &p, input + p.i + 1);
		else if (input[p.i] == '$' && input[p.i + 1] == '?'
			&& (p.quote != '\'' || heredoc))
			p.parsed = insert_code(data, &p);
		else if (input[p.i] == '~' && check_tilde(input[p.i + 1])
			&& (!p.quote && !heredoc))
			p.parsed = insert_home(data, &p);
		else
			p.parsed[p.j++] = input[p.i];
		p.quote = toggle_quote(input[p.i++], p.quote);
	}
	p.parsed[p.j] = '\0';
	return (free(input), p.parsed);
}

static char	*insert_value(t_data *data, t_parse *p, char *input)
{
	char	*variable;
	char	*value;
	int		diff;

	variable = get_variable(input);
	if (!variable)
		return (free(p->parsed), throw_error(data, "malloc failure"), NULL);
	value = ft_getenv(variable, data->env);
	diff = (ft_strlen(variable) + 1) - ft_strlen(value);
	if (diff < 0)
	{
		p->size += -diff;
		p->parsed = ft_realloc(p->parsed, p->size);
		if (!p->parsed)
			return (free(variable), throw_error(data, "malloc failure"), NULL);
	}
	if (value)
		ft_strcpy(p->parsed + p->j, value);
	p->i += ft_strlen(variable);
	p->j += ft_strlen(value);
	return (free(variable), p->parsed);
}

static char	*insert_code(t_data *data, t_parse *p)
{
	char	*code;
	int		diff;

	code = ft_itoa(data->exit_code);
	if (!code)
		return (free(p->parsed), throw_error(data, "malloc failure"), NULL);
	diff = 1 - ft_strlen(code);
	if (diff < 0)
	{
		p->size += -diff;
		p->parsed = ft_realloc(p->parsed, p->size);
		if (!p->parsed)
			return (free(code), throw_error(data, "malloc failure"), NULL);
	}
	ft_strcpy(p->parsed + p->j, code);
	p->i += 1;
	p->j += ft_strlen(code);
	return (free(code), p->parsed);
}

static char	*insert_home(t_data *data, t_parse *p)
{
	char	*home;
	int		diff;

	home = ft_getenv("HOME", data->env);
	if (!home)
		home = data->home;
	diff = 1 - ft_strlen(home);
	if (diff < 0)
	{
		p->size += -diff;
		p->parsed = ft_realloc(p->parsed, p->size);
		if (!p->parsed)
			throw_error(data, "malloc failure");
	}
	if (home)
		ft_strcpy(p->parsed + p->j, home);
	p->j += ft_strlen(home);
	return (p->parsed);
}

static char	*get_variable(char *input)
{
	char	*variable;
	int		i;
	int		j;

	i = 0;
	while (input[i] && check_key(input[i]))
		i++;
	variable = malloc((i + 1) * sizeof(char));
	if (!variable)
		return (NULL);
	j = -1;
	while (++j < i)
		variable[j] = input[j];
	variable[j] = '\0';
	return (variable);
}
