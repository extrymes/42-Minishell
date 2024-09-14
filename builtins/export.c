/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:09:32 by msimao            #+#    #+#             */
/*   Updated: 2024/09/14 11:28:44 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	add_var(t_arg *arg, t_data *data);
static void	modif_var(t_arg *arg, t_data *data);
static void	print_env(t_data *data);
static char	**sort_env(t_data *data);

static char	**sort_env(t_data *data)
{
	int		i;
	int		j;
	char	*tmp;
	char	**envp;

	envp = copy_tab(data);
	if (!envp)
		return (NULL);
	i = 0;
	while (envp[i])
		i++;
	j = 0;
	while (j + 1 < i)
	{
		if (ft_strcmp(envp[j], envp[j + 1]) > 0)
		{
			tmp = envp[j];
			envp[j] = envp[j + 1];
			envp[j + 1] = tmp;
			j = 0;
		}
		else
			j++;
	}
	return (envp);
}

static void	add_var(t_arg *arg, t_data *data)
{
	int	i;

	i = 0;
	while (data->env[i])
		i++;
	data->env = ft_realloc2(data->env, sizeof(char *) * i, \
	sizeof(char *) * (i + 2));
	if (!data->env)
		return ;
	data->env[i] = ft_strdup(arg->data);
	if (!data->env[i])
		return ;
	data->env[i + 1] = NULL;
}

static void	modif_var(t_arg *arg, t_data *data)
{
	int	i;

	if (!ft_strchr(arg->data, '='))
		return ;
	i = is_var_exists(data->env, arg->data);
	free(data->env[i]);
	data->env[i] = ft_strdup(arg->data);
	if (!data->env[i])
		return ;
}

static void	print_env(t_data *data)
{
	int		i;
	char	*str;
	char	**envp;

	i = -1;
	envp = sort_env(data);
	if (!envp)
		return ;
	while (envp[++i])
	{
		if (!ft_strchr(envp[i], '='))
		{
			print_x(envp[i], 0);
			continue ;
		}
		str = copy_to(envp[i], '=', '\0');
		if (!str)
			return ;
		str = strjoin_free(str, "=\"", 0);
		str = strjoin_free(str, copy_to(envp[i], '\0', '='), 2);
		print_x(str, 1);
		free(str);
	}
	free_split(envp);
	data->exit_code = 0;
}

void	ft_export(t_cmd *cmd, t_data *data)
{
	t_arg	*tmp;

	tmp = cmd->arg_lst;
	if (cmd->arg_count == 0)
		return (print_env(data));
	while (tmp)
	{
		if (!check_arg(tmp->data))
		{
			data->exit_code = 1;
			cmd_error(cmd->name, tmp->data, "not a valid identifier");
		}
		else
		{
			if (is_var_exists(data->env, tmp->data) == 0)
				add_var(tmp, data);
			else
				modif_var(tmp, data);
		}
		tmp = tmp->next;
	}
	if (data->exit_code != 1)
		data->exit_code = 0;
}
