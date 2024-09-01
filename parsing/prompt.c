/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 10:28:37 by sabras            #+#    #+#             */
/*   Updated: 2024/08/31 11:02:57 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*handle_home_pwd(t_data *data, int *allocated);
static char	*pwd_join(char *s1, char *s2, int to_free);

char	*create_prompt(t_data *data)
{
	char	*prompt;
	char	*pwd;
	int		allocated;

	allocated = 0;
	pwd = handle_home_pwd(data, &allocated);
	prompt = pwd_join(pwd_join(pwd_join(data->user,
					"@minishell:", -1), pwd, 0), "$ ", 0);
	if (allocated)
		free(pwd);
	if (!prompt)
		return (throw_error("prompt create failure", data), NULL);
	return (prompt);
}

static char	*handle_home_pwd(t_data *data, int *allocated)
{
	char	*home;
	char	*pwd;
	int		home_len;

	home = ft_getenv("HOME", data->env);
	pwd = data->pwd;
	home_len = ft_strlen(home);
	if (pwd && home_len > 0)
	{
		if (!ft_strncmp(home, pwd, home_len) && pwd[home_len] == '/')
		{
			pwd = ft_strjoin("~", pwd + home_len);
			if (!pwd)
				return (throw_error("pwd handling error", data), NULL);
			*allocated = 1;
		}
	}
	return (pwd);
}

static char	*pwd_join(char *s1, char *s2, int to_free)
{
	char	*joined;

	joined = NULL;
	if (s1 && s2)
		joined = strjoin_free(s1, s2, to_free);
	else if (!s1 && s2)
		joined = strjoin_free("", s2, to_free);
	else if (!s2 && s1)
		joined = strjoin_free(s1, "", to_free);
	if (!joined)
		return (NULL);
	return (joined);
}
