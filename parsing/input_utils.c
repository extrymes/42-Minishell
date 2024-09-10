/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 20:57:35 by sabras            #+#    #+#             */
/*   Updated: 2024/09/10 15:12:45 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_variable(char *content);

char	*insert_value(t_data *data, t_parse *p)
{
	char	*variable;
	char	*value;
	int		diff;

	variable = get_variable(p->input + p->i + 1);
	if (!variable)
		return (clear_parse(p), throw_error(data, "malloc failure"), NULL);
	value = ft_getenv(variable, data->env);
	diff = (ft_strlen(variable) + 1) - ft_strlen(value);
	if (diff < 0)
	{
		p->size += -diff;
		p->parsed = ft_realloc(p->parsed, p->size);
		if (!p->parsed)
			return (clear_parse(p), throw_error(data, "malloc failure"), NULL);
	}
	if (value)
		ft_strcpy(p->parsed + p->j, value);
	p->i += ft_strlen(variable);
	p->j += ft_strlen(value);
	return (free(variable), p->parsed);
}

char	*insert_code(t_data *data, t_parse *p)
{
	char	*code;
	int		diff;

	code = ft_itoa(data->exit_code);
	if (!code)
		return (clear_parse(p), throw_error(data, "malloc failure"), NULL);
	diff = 1 - ft_strlen(code);
	if (diff < 0)
	{
		p->size += -diff;
		p->parsed = ft_realloc(p->parsed, p->size);
		if (!p->parsed)
			return (clear_parse(p), throw_error(data, "malloc failure"), NULL);
	}
	ft_strcpy(p->parsed + p->j, code);
	p->i += 1;
	p->j += ft_strlen(code);
	return (p->parsed);
}

char	*insert_home(t_data *data, t_parse *p)
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
			return (clear_parse(p), throw_error(data, "malloc failure"), NULL);
	}
	if (home)
		ft_strcpy(p->parsed + p->j, home);
	p->j += ft_strlen(home);
	return (p->parsed);
}

static char	*get_variable(char *content)
{
	char	*variable;
	int		i;
	int		j;

	i = 0;
	while (content[i] && check_key(content[i]))
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
