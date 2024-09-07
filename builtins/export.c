/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:09:32 by msimao            #+#    #+#             */
/*   Updated: 2024/09/06 15:19:04 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	add_var(t_arg *arg, t_data *data);
static void	modif_var(t_arg *arg, t_data *data);
static void	print_env(char **envp);
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

	i = is_var_exists(data->env, arg->data);
	free(data->env[i]);
	data->env[i] = ft_strdup(arg->data);
	if (!data->env[i])
		return ;
}

static void	print_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(envp[i++], STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
}

void	ft_export(t_cmd *cmd, t_data *data)
{
	char	**envp;
	t_arg	*tmp;

	tmp = cmd->arg_lst;
	if (data->entry->cmd_count != 1)
		return ;
	if (cmd->arg_count == 0)
	{
		envp = sort_env(data);
		if (!envp)
			return ;
		print_env(envp);
		free_split(envp);
		return ;
	}
	while (tmp && ft_strchr(tmp->data, '='))
	{
		if (is_var_exists(data->env, tmp->data) == 0)
			add_var(tmp, data);
		else
			modif_var(tmp, data);
		tmp = tmp->next;
	}
}
