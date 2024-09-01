/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 19:56:48 by sabras            #+#    #+#             */
/*   Updated: 2024/08/31 11:20:28 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_input(t_data *data, t_entry *entry)
{
	char	*word;
	int		i;

	i = 0;
	while (entry->input[i])
	{
		i += count_spaces(&entry->input[i]);
		word = get_word(data, &entry->input[i]);
		i += ft_strlen(word);
		find_cmd(data, word);
	}
}

int	find_cmd(t_data *data, char *word)
{
	t_cmd	*cmd;
	char	*cmd_path;

	cmd_path = get_cmd_path(data, word);
	if (cmd_path)
	{
		cmd = init_cmd(word, cmd_path, data);
		add_cmd(&data->entry, cmd);
	}
	return (1);
}

char	*get_word(t_data *data, char *str)
{
	char	*word;
	int		word_len;
	int		i;

	word_len = count_word_len(str);
	word = malloc((word_len + 1) * sizeof(char));
	if (!word)
		return (throw_error("malloc failure", data), NULL);
	i = 0;
	while (i < word_len)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	*get_cmd_path(t_data *data, char *word)
{
	char	*path;
	char	**locations;
	char	*joined;
	int		i;

	path = ft_getenv("PATH", data->env);
	if (!path)
		return (throw_error("path not found", data), NULL);
	locations = ft_split(path, ':');
	if (!locations)
		return (throw_error("malloc failure", data), NULL);
	i = 0;
	while (locations[i])
	{
		joined = strjoin_free(ft_strjoin(locations[i], "/"), word, 0);
		if (!joined)
			return (free(locations), throw_error("malloc failure", data), NULL);
		if (access(joined, F_OK) == 0)
			return (free(locations), joined);
		free(joined);
		i++;
	}
	return (free(locations), NULL);
}
