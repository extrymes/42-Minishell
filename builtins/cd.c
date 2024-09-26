/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:59:47 by msimao            #+#    #+#             */
/*   Updated: 2024/09/26 08:33:59 by sabras           ###   ########.fr       */
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
	char	*path;

	path = ft_getenv("OLDPWD", data->env);
	if (!path)
		return (NULL);
	path = ft_strdup(path);
	return (path);
}

static void	set_pwd(t_data *data, char *path)
{
	int	i;

	set_var(data, path);
	i = is_var_exists(data->env, "PWD=");
	if (i != -1)
	{
		free(data->env[i]);
		data->env[i] = ft_strjoin("PWD=", data->pwd);
		if (!data->env[i])
			return ;
	}
	else
	{
		i = 0;
		while (data->env[i])
			i++;
		data->env = ft_realloc2(data->env, sizeof(char *) * i, \
		sizeof(char *) * (i + 2));
		if (!data->env)
			return ;
		data->env[i] = ft_strjoin("PWD=", data->pwd);
		if (!data->env[i])
			return ;
		data->env[i + 1] = NULL;
	}
}

static void	set_old(t_data *data)
{
	int	i;

	i = is_var_exists(data->env, "OLDPWD=");
	if (i != -1)
	{
		free(data->env[i]);
		data->env[i] = ft_strjoin("OLDPWD=", data->pwd);
		if (!data->env[i])
			return ;
	}
	else
	{
		i = 0;
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

	if (cmd->arg_count > 1)
		return (data->exit_code = 1,
			cmd_error(cmd->name, NULL, "too many arguments"));
	if (cmd->arg_count == 0)
		path = find_home(cmd, data->env);
	else if (ft_strncmp(cmd->arg_lst->data, "-", 1) == 0)
		path = find_old(data);
	else
		path = ft_strdup(cmd->arg_lst->data);
	if (ft_strlen(path) == 0)
		return ;
	if (chdir(path) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		return (data->exit_code = 1, perror(path), free(path));
	}
	set_old(data);
	set_pwd(data, path);
	free(path);
	data->exit_code = 0;
}
