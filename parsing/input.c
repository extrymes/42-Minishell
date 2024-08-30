/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 19:56:48 by sabras            #+#    #+#             */
/*   Updated: 2024/08/30 23:15:42 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_input(t_entry *entry, char **env)
{
	char	*word;
	int		i;

	i = 0;
	while (entry->input[i])
	{
		i += count_spaces(&entry->input[i]);
		word = get_word(&entry->input[i]);
		i += ft_strlen(word);
		find_cmd(entry, word, env);
	}
	return (1);
}

int	find_cmd(t_entry *entry, char *word, char **env)
{
	t_cmd	*cmd;
	char	*cmd_path;

	cmd_path = get_cmd_path(word, env);
	if (cmd_path)
	{
		cmd = init_cmd(word, cmd_path);
		if (!cmd)
			return (0);
		add_cmd(entry, cmd);
	}
	return (1);
}

char	*get_word(char *str)
{
	char	*word;
	int		word_len;
	int		i;

	word_len = count_word_len(str);
	word = malloc((word_len + 1) * sizeof(char));
	if (!word)
		return (print_error("malloc failure"), NULL);
	i = 0;
	while (i < word_len)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	*get_cmd_path(char *word, char **env)
{
	char	*path;
	char	**locations;
	char	*joined;
	int		i;

	path = ft_getenv("PATH", env);
	if (!path)
		return (print_error("path not found"), NULL);
	locations = ft_split(path, ':');
	if (!locations)
		return (print_error("malloc failure"), NULL);
	i = 0;
	while (locations[i])
	{
		joined = strjoin_free(ft_strjoin(locations[i], "/"), word, 0);
		if (!joined)
			return (free(locations), print_error("malloc failure"), NULL);
		if (access(joined, F_OK) == 0)
			return (free(locations), joined);
		free(joined);
		i++;
	}
	return (free(locations), NULL);
}
