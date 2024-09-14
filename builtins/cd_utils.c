/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:05:44 by sabras            #+#    #+#             */
/*   Updated: 2024/09/14 15:06:04 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_var(t_data *data, char *path)
{
	char	*tmp;

	tmp = ft_strdup(data->pwd);
	free(data->pwd);
	data->pwd = getcwd(NULL, 0);
	if (!data->pwd)
	{
		ft_putstr_fd("cd: error retrieving current directory: ", 2);
		ft_putstr_fd("getcwd: cannot access parent directories: ", 2);
		ft_putstr_fd("No such file or directory\n", 2);
		data->pwd = ft_strjoin(tmp, "/");
		data->pwd = strjoin_free(data->pwd, path, 0);
	}
	free(tmp);
}
