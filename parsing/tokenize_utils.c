/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 11:20:32 by sabras            #+#    #+#             */
/*   Updated: 2024/09/06 17:54:23 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*insert_value(t_parse *parse, char **env, int *i, int *j)
{
	char	*variable;
	char	*value;
	int		diff;

	variable = get_variable(parse->content + *i + 1);
	if (!variable)
		return (free(parse->parsed), NULL);
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
	return (free(variable), parse->parsed);
}

char	*insert_home(t_parse *parse, char **env, int *j)
{
	char	*home;
	int		diff;

	home = ft_getenv("HOME", env);
	diff = 1 - ft_strlen(home);
	if (diff < 0)
	{
		parse->size += -diff;
		parse->parsed = ft_realloc(parse->parsed, parse->size);
	}
	if (home)
		ft_strcpy(parse->parsed + *j, home);
	*j += ft_strlen(home);
	return (parse->parsed);
}

char	*get_variable(char *content)
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

void	clear_parse(t_parse *parse)
{
	if (parse->content)
	{
		free(parse->content);
		parse->content = NULL;
	}
	if (parse->parsed)
	{
		free(parse->parsed);
		parse->parsed = NULL;
	}
}
