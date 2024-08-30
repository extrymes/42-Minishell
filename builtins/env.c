/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimao <msimao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:52:41 by msimao            #+#    #+#             */
/*   Updated: 2024/08/29 15:15:14 by msimao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_env(t_cmd *cmd, char **envp)
{
	int	i;

	i = 0;
	while(envp[i])
		ft_putstr_fd(envp[i++], 1);
		ft_putstr_fd("\n", 1);
	return ;
}
