/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:08:55 by msimao            #+#    #+#             */
/*   Updated: 2024/09/12 15:15:01 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	**new_env(t_arg *arg, char **env)
{
	char	**envp;
	int		i;
	int		j;

	i = 0;
	while (env[i])
		i++;
	envp = malloc(sizeof(char *) * i);
	if (!envp)
		return (NULL);
	i = -1;
	j = -1;
	while (env[++i])
	{
		if (ft_strncmp(arg->data, env[i], (ft_strlen(arg->data) - 1)) == 0)
			continue ;
		envp[++j] = ft_strdup(env[i]);
		if (!envp[j])
			return (free_split(envp), NULL);
	}
	return (envp[j + 1] = NULL, envp);
}

void	*ft_unset(t_cmd *cmd, t_data *data)
{
	char	**envp;
	t_arg	*tmp;

	if (cmd->arg_count <= 0)
		return (data->exit_code = 0, NULL);
	tmp = cmd->arg_lst;
	while (tmp)
	{
		tmp->data = strjoin_free(tmp->data, "=", 0);
		if (is_var_exists(data->env, tmp->data) == 0)
		{
			tmp = tmp->next;
			continue ;
		}
		envp = new_env(tmp, data->env);
		if (!envp)
			return (NULL);
		free_split(data->env);
		read_env(data, envp);
		free_split(envp);
		tmp = tmp->next;
	}
	return (data->exit_code = 0, NULL);
}
