/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:59:47 by msimao            #+#    #+#             */
/*   Updated: 2024/09/10 12:12:55 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*find_home(t_cmd *cmd, char **env)
{
	char	*home;

	home = ft_getenv("HOME", env);
	if (!home)
		return (cmd_error(cmd->name, NULL, "HOME not set"), NULL);
	home = ft_strdup(home);
	return (home);
}

static char	*find_old(t_data *data)
{
	int		i;
	char	*path;

	i = 0;
	path = NULL;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], "OLDPWD=", 7) == 0)
			path = ft_strdup(data->env[i]);
		i++;
	}
	return (path);
}

static void	set_pwd(t_data *data)
{
	int	i;

	free(data->pwd);
	i = is_var_exists(data->env, "PWD=");
	if (i != 0)
	{
		free(data->env[i]);
		data->env[i] = strjoin_free("PWD=", getcwd(NULL, 0), 1);
		if (!data->env[i])
			return ;
	}
	else
	{
		while (data->env[i])
			i++;
		data->env = ft_realloc2(data->env, sizeof(char *) * i, \
		sizeof(char *) * (i + 2));
		if (!data->env)
			return ;
		data->env[i] = strjoin_free("PWD=", getcwd(NULL, 0), 1);
		if (!data->env[i])
			return ;
		data->env[i + 1] = NULL;
	}
	data->pwd = getcwd(NULL, 0);
}

static void	set_old(t_data *data)
{
	int	i;

	i = is_var_exists(data->env, "OLDPWD=");
	if (i != 0)
	{
		free(data->env[i]);
		data->env[i] = ft_strjoin("OLDPWD=", data->pwd);
		if (!data->env[i])
			return ;
	}
	else
	{
		while (data->env[i])
			i++;
		data->env = ft_realloc2(data->env, sizeof(char *) * i, \
		sizeof(char *) * (i + 2));
		if (!data->env)
			return ;
		data->env[i] = ft_strjoin("OLDPWD=", data->pwd);
		if (!data->env[i])
			return ;
		data->env[i + 1] = NULL;
	}
}

void	ft_cd(t_cmd *cmd, t_data *data)
{
	char	*path;

	if (cmd->arg_count == 0)
		path = find_home(cmd, data->env);
	else if (ft_strncmp(cmd->arg_lst->data, "-", 1) == 0)
		path = find_old(data);
	else
		path = ft_strdup(cmd->arg_lst->data);
	if (!path)
		return ;
	if (chdir(path) == -1)
		return (cmd_error(cmd->name, path, "No such file or directory"));
	set_pwd(data);
	set_old(data);
	free(path);
}
