/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 10:28:37 by sabras            #+#    #+#             */
/*   Updated: 2024/09/06 15:59:54 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*handle_home_pwd(t_data *data, int *allocated);

char	*create_prompt(t_data *data)
{
	char	*prompt;
	char	*user;
	char	*pwd;
	int		allocated;

	allocated = 0;
	user = data->user;
	pwd = handle_home_pwd(data, &allocated);
	prompt = strjoin_free(strjoin_free(strjoin_free(CYAN "", ft_strjoin(user,
						"@minishell:"), 1), pwd, 0), "$ " RESET, 0);
	if (allocated)
		free(pwd);
	if (!prompt)
		return (throw_error("malloc failure", data), NULL);
	return (prompt);
}

static char	*handle_home_pwd(t_data *data, int *allocated)
{
	char	*home;
	char	*pwd;
	int		home_len;

	home = ft_getenv("HOME", data->env);
	pwd = ft_getenv("PWD", data->env);
	if (!pwd)
		pwd = data->pwd;
	home_len = ft_strlen(home);
	if (home_len > 0)
	{
		if (!ft_strcmp(home, pwd) && home_len > 1)
			return ("~");
		if (!ft_strncmp(home, pwd, home_len) && pwd[home_len] == '/')
		{
			pwd = ft_strjoin("~", pwd + home_len);
			if (!pwd)
				return (throw_error("malloc error", data), NULL);
			*allocated = 1;
		}
	}
	return (pwd);
}
