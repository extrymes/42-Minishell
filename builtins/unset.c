/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:08:55 by msimao            #+#    #+#             */
/*   Updated: 2024/09/18 09:14:53 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	compare(char *s1, char *s2)
{
	char	*str;

	if (!ft_strchr(s2, '='))
		str = ft_strjoin(s2, "=");
	else
		str = ft_strdup(s2);
	if (ft_strncmp(s1, str, ft_strlen(s1)) == 0)
		return (free(str), 1);
	return (free(str), 0);
}

static char	**new_env(t_arg *arg, char **env)
{
	char	**envp;
	int		i;
	int		j;

	i = 0;
	while (env[i])
		i++;
	envp = malloc(sizeof(char *) * (i + 1));
	if (!envp)
		return (NULL);
	i = -1;
	j = -1;
	while (env[++i])
	{
		if (compare(arg->data, env[i]) == 1)
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
		if (!tmp->data)
			return (NULL);
		if (is_var_exists(data->env, tmp->data) == -1)
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
